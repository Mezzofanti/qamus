#ifndef ENTRY_H
#define ENTRY_H

#include <map>
#include <vector>

#include "lexeme.h"

/* Entry
 * Contains all the data for each language of a single dictionary entry.
 *
 * Metadata for this entry can also be stored here.
 */
class Entry
{
public:
    Entry(const int size);
    Entry(const Entry& that);
    Entry& operator=(const Entry& that);
    ~Entry();
    QString getWord(const int col) const;
    QString getTransliteration(const int col) const;
    size_t getLexemeCount() const;
    void setLexeme(const int i, const Lexeme& lexeme);
    Lexeme& getLexeme(const int i);
    void setMetadata(const QString id, const QString data);
    QString toString() const;

private:
    std::vector<Lexeme> _lexemes;
    std::map<QString, QString> _metadata;
};

#endif // ENTRY_H