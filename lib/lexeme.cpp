#include "lexeme.h"

/*
 * Default constructor.
 */
Lexeme::Lexeme()
{
#ifdef ENABLE_TRE
    _utf8value = nullptr;
#endif
}


/*
 * Copy constructor.
 */
Lexeme::Lexeme(const Lexeme& that)
{
    *this = that;
}


/*
 * Equals operator.
 */
Lexeme& Lexeme::operator=(const Lexeme& that)
{
    Q_ASSERT(this != &that);
    set(that._value);
    return *this;
}


/*
 * Deallocate the char array.
 */
Lexeme::~Lexeme()
{
#ifdef ENABLE_TRE
    delete[] _utf8value;
#endif
}


/*
 * Resets the lexeme.
 */
void Lexeme::clear()
{
    _value.clear();
#ifdef ENABLE_ICU
    _transliteration.clear();
#endif
#ifdef ENABLE_TRE
    delete[] _utf8value;
    _utf8value = nullptr;
#endif
}


/*
 * Returns the lexeme as a QString.
 */
const QString& Lexeme::get() const
{
    return _value;
}

/*
 * Returns the transliterated form of the lexeme.
 */
const QString& Lexeme::getTransliteration() const
{
#ifdef ENABLE_ICU
    return _transliteration;
#else
    return _value;
#endif
}


#ifdef ENABLE_TRE
/*
 * Returns the lexeme as a null-terminated char array. The pointer should not
 * be preserved as it will become invalid if the data changes.
 */
const char* Lexeme::getUtf8() const
{
    return _utf8value;
}

void Lexeme::setUtf8(QString term)
{
    delete[] _utf8value;
    if (!term.isEmpty())
    {
        QByteArray data = term.toUtf8();
        if (data.size() > 0)
        {
            _utf8value = new char[data.size() + 1];
            strcpy(_utf8value, data.data());
        }
    }
}
#endif


#ifdef ENABLE_ICU
/*
 * Sets the lexeme and creates the utf8 char array based on a transliterator if
 * one is available.
 */
void Lexeme::set(const QString& value, const Transliterator* transliterator)
{
    _value = value;
    if (transliterator == nullptr)
    {
        _transliteration = _value;
    }
    else
    {
        UnicodeString term = UnicodeString::fromUTF8(_value.toStdString());
        transliterator->transliterate(term);
        std::string s;
        term.toUTF8String(s);
        _transliteration = QString::fromUtf8(s.c_str());
    }

#ifdef ENABLE_TRE
    setUtf8(_transliteration);
#endif
}

#else

/*
 * Sets the lexeme and creates the utf8 char array.
 */
void Lexeme::set(const QString& value)
{
    _value = value;

#ifdef ENABLE_TRE
    setUtf8(_value);
#endif
}
#endif