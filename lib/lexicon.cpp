#include "common.h"
#include "lexicon.h"

Lexicon::Lexicon()
{
}

Lexicon::~Lexicon()
{
    _entries.clear();
}

void Lexicon::addLanguage(Language& language)
{
    _languages.push_back(language);
}


int Lexicon::getCols() const
{
    return _languages.size();
}


int Lexicon::getRows() const
{
    return _entries.size();
}

void Lexicon::setName(const QString name)
{
    _name = name;
}

void Lexicon::setAuthor(const QString author)
{
    _author = author;
}

void Lexicon::setDescription(const QString description)
{
    _description = description;
}

const Language& Lexicon::getLanguage(const int col) const
{
    return _languages.at(col);
}

QString Lexicon::getWord(const int col, const int row) const
{
#ifdef ENABLE_ICU
    if (_languages.at(col).showTransliteration())
    {
        return _entries.at(row).getTransliteration(col);
    }
    else
#endif
    {
        return _entries.at(row).getWord(col);
    }
}

Lexeme& Lexicon::getLexeme(const int col, const int row)
{
    return _entries.at(row).getLexeme(col);
}

bool Lexicon::editLexeme(const int col, const int row, const QString& word)
{
    if (col < (int)_languages.size() && row < (int)_entries.size())
    {
        _entries.at(row).getLexeme(col).set(word);
        return true;
    }
    else
    {
        return false;
    }
}

bool Lexicon::close()
{
    if (!_name.isEmpty() || !_description.isEmpty() || !_author.isEmpty() || _languages.size() != 0 || _entries.size() != 0)
     {
        _name.clear();
        _description.clear();
        _author.clear();
        _languages.clear();
        _entries.clear();
        return true;
    }
    else
    {
        return false;
    }
}

void Lexicon::addEntry(const Entry& entry)
{
    if (_languages.size() != entry.getLexemeCount())
    {
        qWarning() << "unable to load entry: " << entry.toString();
        return;
    }

    _entries.push_back(entry);
}


void Lexicon::applyTransliterations()
{
#ifdef ENABLE_ICU

    for (int col = 0; col < getCols(); ++col)
    {
        auto transliterator = getLanguage(col).getTransliterator();
        if (transliterator != nullptr)
        {
            for (int row = 0; row < getRows(); ++row)
            {
                Lexeme* lexeme = &getLexeme(col, row);
                lexeme->set(lexeme->get(), transliterator);
            }
        }
    }
#endif
}