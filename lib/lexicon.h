#ifndef LEXICON_H
#define LEXICON_H

#include "entry.h"
#include "language.h"


class Lexicon
{
public:
    Lexicon();
    ~Lexicon();

    void addLanguage(Language& language);
    void addEntry(const Entry entry);

    int getCols() const;
    int getRows() const;

    void setName(const QString name);
    void setAuthor(const QString author);
    void setDescription(const QString description);

    const Language& getLanguage(const int col) const;
    QString getWord(const int col, const int row) const;
    Lexeme& getLexeme(const int col, const int row);
    bool editLexeme(const int col, const int row, const QString word);
    bool close();
    void applyTransliterations();

private:
    QString _name;
    QString _description;
    QString _author;
    std::vector<Language> _languages;
    std::vector<Entry> _entries;
};

#endif // LEXICON_H
