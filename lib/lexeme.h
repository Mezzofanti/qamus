#ifndef LEXEME_H
#define LEXEME_H

#include <QString>

#ifdef ENABLE_ICU
#include <unicode/translit.h>
#endif

/* Lexeme
 * Represents a lexical entry for a single language. This can include a
 * transliteration of the entry.
 *
 * Both the QString value (used by GUI) and the char* value (used by tre
 * regex library) are stored. There is a minimal overhead for this duplication.
 *
 * A transliteration for the lexeme can be stored here.
 */
class Lexeme
{
public:
    Lexeme();
    Lexeme(const Lexeme& that);
    Lexeme& operator=(const Lexeme& that);
    ~Lexeme();
    void clear();
    const QString& get() const;
    const QString& getTransliteration() const;
#ifdef ENABLE_TRE
    const char* getUtf8() const;
    void setUtf8(QString term);
#endif
#ifdef ENABLE_ICU
    void set(const QString& trans, const Transliterator* transliterator = nullptr);
#else
    void set(const QString& value);
#endif

private:
    QString _value; // base value read from dictionary
#ifdef ENABLE_ICU
    QString _transliteration; // transliterated value
#endif
#ifdef ENABLE_TRE
    char* _utf8value = nullptr; // converted name
#endif
};

#endif // LEXEME_H