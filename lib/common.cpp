#include "common.h"

#ifdef ENABLE_ICU
UnicodeString QStringToUnicodeString(const QString& source)
{
    UnicodeString target = UnicodeString::fromUTF8(source.toStdString());
    Q_ASSERT(target.charAt(0) != REPLACEMENT_CHAR);
    return target;
}

QString UnicodeStringToQString(const UnicodeString& source)
{
    std::string s;
    source.toUTF8String(s);
    return QString::fromUtf8(s.c_str());
}
#endif // ENABLE_ICU