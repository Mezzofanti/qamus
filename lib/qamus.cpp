#include <cmath>
#include <QDir>
#include <QDateTime>

#include "qamus.h"
#include "common.h"
#include "qlxxmlhandler.h"

Qamus::Qamus()
{
    _activeCache = nullptr;

#ifdef ENABLE_ICU
    _transliterator = nullptr;
#endif

#ifdef ENABLE_TRE
    int maxCost = 6;
    _treParams.cost_del = 1;
    _treParams.cost_ins = 1;
    _treParams.cost_subst = 2;
    _treParams.max_cost = maxCost;
    _treParams.max_del = maxCost;
    _treParams.max_err = maxCost;
    _treParams.max_ins = maxCost;
    _treParams.max_subst = maxCost;
#endif
}

Qamus::~Qamus()
{
    for (auto it = _searchCache.begin(); it != _searchCache.end(); ++it)
    {
        delete *it;
    }
    _searchCache.clear();
}

int Qamus::columnCount() const
{
    return _lexicon.getCols();
}

int Qamus::rowCount() const
{
    if (_activeCache == nullptr)
    {
        return _lexicon.getRows();
    }
    return _lexicon.getRows();
}

QString Qamus::getLanguage(int col) const
{
    return _lexicon.getLanguage(col).getName();
}

QString Qamus::word(const int col, const int row) const
{
    Q_ASSERT(_activeCache == nullptr || row < _activeCache->size());

    return _lexicon.getWord(col, row);
}


bool Qamus::setWord(const int col, const int row, const QString& value)
{
    return _lexicon.editLexeme(col, row, value);
}

char Qamus::getScore(int row) const
{
    Q_ASSERT(_activeCache == nullptr || row < _activeCache->size());

    if (_activeCache == nullptr)
    {
        return MAX_SCORE;
    }
    else
    {
        return _activeCache->at(row);
    }
}

bool Qamus::loadLexicon(const QString& filename)
{
    closeLexicon();
    QFileInfo fileInfo(filename);
    if (!fileInfo.isFile())
    {
        return false;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    DictXmlHandler* dictHandler = new QlxXmlHandler();
    QXmlInputSource source(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(dictHandler);
    reader.setErrorHandler(dictHandler);
    bool result = reader.parse(source);
    file.close();

    if (result)
    {
        _lexicon.setName(dictHandler->getName());
        _lexicon.setAuthor(dictHandler->getAuthor());
        _lexicon.setDescription(dictHandler->getDescription());

        std::vector<Language> languages = dictHandler->getLanguages();
        for (auto it = languages.begin(); it != languages.end(); ++it)
        {
            _lexicon.addLanguage(*it);
        }

        for(int i = 0; i < dictHandler->getEntryCount(); ++i)
        {
            _lexicon.addEntry(dictHandler->getEntry(i));
        }

#ifdef ENABLE_ICU
        _transliterator = dictHandler->getTransliterator();
        _lexicon.applyTransliterations();
#endif

        _filename = filename;
    }

    delete dictHandler;
    return result;
}

bool Qamus::closeLexicon()
{
    _filename.clear();
    return _lexicon.close();
}

void Qamus::search(const int col, QString searchTerm)
{
    _activeCache = nullptr;
    if (searchTerm.isEmpty())
    {
        return;
    }

#ifdef ENABLE_ICU
    if (_transliterator)
    {
        searchTerm = transliterate(searchTerm);
    }
#endif
    searchTerm = searchTerm;/*applyRules(searchTerm);*/

    SearchCache* baseCache = nullptr;
    for (auto it = _searchCache.begin(); it != _searchCache.end(); ++it)
    {
        SearchCache* searchCache  = *it;
        if (searchCache->getCol() == col && searchCache->getTerm() == searchTerm)
        {
            _activeCache = searchCache;
            _activeCache->setActive(_lexicon.getRows());
            return;
        }
        else if (searchTerm.length() > searchCache->getRawTerm().length() &&
                (searchTerm.startsWith(searchCache->getRawTerm()) || searchCache->getRawTerm().startsWith(searchTerm)))
        {
            baseCache = searchCache;
            break;
        }
    }

    if (baseCache == nullptr)
    {
        _activeCache = new SearchCache(searchTerm, searchTerm, col, _lexicon.getRows());
    }
    else
    {
        _activeCache = new SearchCache(searchTerm, searchTerm, baseCache);
    }
    _searchCache.push_front(_activeCache);

#ifdef ENABLE_TRE
    char* term = searchTerm.toUtf8().data();
    regex_t treRegexp;
    if (!composeRegExp(term, treRegexp))
    {
        return;
    }
#endif

    int rows = rowCount();
    for (int row = 0; row < rows; ++row)
    {
        if (_activeCache->getNew() || _activeCache->getScore(row) > 0)
        {
#ifdef ENABLE_TRE
            const char* word = _lexicon.getLexeme(col, row).getUtf8();
            int cost;
            if (doTreSearch(treRegexp, word, cost))
            {
                if (cost == 0)
                {
                    _activeCache->set(row, MAX_SCORE);
                }
                else
                {
                    _activeCache->set(row, MAX_SCORE / (cost+1));
                }
            }
            else
            {
                _activeCache->set(row, MIN_SCORE);
            }
#else
            QString word = _lexicon.getLexeme(col, row).get();
            if (word.contains(searchTerm))
            {
                _activeCache->set(row, MAX_SCORE);
            }
            else
            {
                _activeCache->set(row, MIN_SCORE);
            }
#endif
        }

        if (row % 100 == 0)
        {
            emit progress(row / 100);
        }
    }

    _activeCache->searchFinished();
}

qint64 Qamus::getSearchDuration() const
{
    return _activeCache->getDuration();
}

#ifdef ENABLE_ICU
QString Qamus::transliterate(QString &term)
{
    UnicodeString us = UnicodeString::fromUTF8(term.toStdString());
    _transliterator->transliterate(us);
    std::string s;
    us.toUTF8String(s);
    return QString::fromUtf8(s.c_str());
 }
#endif

#ifdef ENABLE_TRE
bool Qamus::composeRegExp(char* regexp, regex_t& treRegexp)
{
    int result = tre_regcomp(&treRegexp, regexp, REG_EXTENDED|REG_ICASE|REG_NOSUB);
    if (result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Qamus::doTreSearch(const regex_t& treRegexp, const char* word, int& cost)
{
    regmatch_t pmatch;
    regamatch_t amatch;
    amatch.nmatch = 0;
    amatch.cost = 0;
    amatch.pmatch = &pmatch;

    int result = tre_regaexec(&treRegexp, word, &amatch, _treParams, 0);
    cost = amatch.cost;

    if (result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif
