#ifndef QAMUS_H
#define QAMUS_H

#include <list>
#include <QObject>

#ifdef ENABLE_ICU
#include <unicode/translit.h>
#endif

#ifdef ENABLE_TRE
#include <tre/tre.h>
#endif

#include "lexicon.h"
#include "searchcache.h"

class Qamus: public QObject
{
    Q_OBJECT
public:
    explicit Qamus();
    ~Qamus();

    int columnCount() const;
    int rowCount() const;

    QString getLanguage(int col) const;
    QString word(const int col, const int row) const;

    bool setWord(const int col, const int row, const QString &value);
    char getScore(int row) const;

    bool loadLexicon(const QString& filename);
    bool closeLexicon();
    qint64 search(const int col, QString searchTerm);

#ifdef ENABLE_ICU
    QString transliterate(QString& term);
#endif

signals:
    void progress(const int);

private:
    QString _filename;
    Lexicon _lexicon;
    SearchCache* _activeCache;
    std::list<SearchCache*> _searchCache;

#ifdef ENABLE_ICU
    Transliterator* _transliterator;
#endif

#ifdef ENABLE_TRE
    regaparams_t _treParams;
    bool doTreSearch(const regex_t& treRegexp, const char* word, int& cost);
    bool composeRegExp(char* regexp, regex_t& treRegexp);
#endif
};

#endif // QAMUS_H