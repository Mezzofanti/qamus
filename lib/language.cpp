#ifdef ENABLE_ICU
#include <unicode/locid.h>
#include <unicode/uscript.h>
#include <unicode/utypes.h>
#endif

#include <string.h>

#include "common.h"
#include "language.h"

Language::Language()
{
#ifdef ENABLE_ICU
    _transliterator = nullptr;
    _showTransliteration = true;
#endif
}

Language::Language(const Language& that)
{
#ifdef ENABLE_ICU
    _transliterator = nullptr;
#endif
    *this = that;
}

Language& Language::operator=(const Language& that)
{
    Q_ASSERT(this != &that);
    _id = that._id;
    _description = that._description;
    _iso15924 = that._iso15924;
    _iso639_2 = that._iso639_2;
#ifdef ENABLE_ICU
    _showTransliteration = that._showTransliteration;
    delete _transliterator;
    if (that._transliterator == nullptr)
    {
        _transliterator = nullptr;
    }
    else
    {
        _transliterator = that._transliterator->clone();
    }
    _iso639_2string = that._iso639_2string;
#endif
    return *this;
}


Language::Language(Language &&that):
    _id(that._id),
    _iso15924(that._iso15924),
    _iso639_2(that._iso639_2),
#ifdef ENABLE_ICU
    _iso639_2string(that._iso639_2string),
    _transliterator(that._transliterator),
    _showTransliteration(that._showTransliteration),
#endif
    _description(that._description)
{
Q_ASSERT(this != &that);
#ifdef ENABLE_ICU
    that._transliterator = nullptr;
#endif
}

Language &Language::operator=(Language&& that)
{
    std::swap(*this, that);
    return *this;
}

Language::~Language()
{
#ifdef ENABLE_ICU
    delete _transliterator;
#endif
}

const QString Language::getDescription() const
{
    return _description;
}

const QString Language::getId() const
{
    return _id;
}

const QString Language::getIso15924() const
{
    return _iso15924;
}

const QString Language::getIso639_2() const
{
    return _iso639_2;
}

const QString Language::getName() const
{
#ifdef ENABLE_ICU
    return _iso639_2string;
#else
    return _iso639_2;
#endif
}

const QString Language::getScript() const
{
    QString code;

    // if no script is set, attempt to get script from the language code
    if (_iso15924.isEmpty())
    {
        code = _iso639_2;
    }
    else
    {
        code = _iso15924;
    }

#ifdef ENABLE_ICU
    const int size = 8;
    UErrorCode error = U_ZERO_ERROR;
    UScriptCode buffer[size];

    int numCodes = uscript_getCode(code.toUtf8(), buffer, size, &error);
    if (error == U_ZERO_ERROR && numCodes > 0)
    {
        for (int i = 0; i < numCodes; ++i)
        {
            if (buffer[i] == USCRIPT_COMMON ||
                buffer[i] == USCRIPT_CODE_LIMIT ||
                buffer[i] == USCRIPT_INHERITED ||
                buffer[i] == USCRIPT_INVALID_CODE)
            {
                continue;
            }

            const char* name = uscript_getName(buffer[i]);
            if (name != nullptr)
            {
                return QString(name);
            }
        }
    }
#endif

    return code;
}


void Language::setId(const QString& id)
{
    _id = id;
}

void Language::setIso15924(const QString& iso15924)
{
    _iso15924 = iso15924;
}

void Language::setIso639_2(const QString& iso639_2)
{
    _iso639_2 = iso639_2;
#ifdef ENABLE_ICU
    std::string s;
    UnicodeString us;
    Locale locale(_iso639_2.toUtf8());
    locale.getDisplayName(us);
    us.toUTF8String(s);
    _iso639_2string = QString::fromUtf8(s.c_str());
#endif
}

void Language::setDescription(const QString& description)
{
    _description = description;
}

void Language::clear()
{
    _id.clear();
    _description.clear();
    _iso639_2.clear();
    _iso15924.clear();
#ifdef ENABLE_ICU
    delete _transliterator;
    _transliterator = nullptr;
    _showTransliteration = true;
#endif
}

#ifdef ENABLE_ICU
bool Language::showTransliteration() const
{
    return _showTransliteration;
}

void Language::setTransliterator(Transliterator* const transliterator)
{
    _transliterator = transliterator;
}


const Transliterator* Language::getTransliterator() const
{
    return _transliterator;
}
#endif