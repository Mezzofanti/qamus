#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QString>
#include <unicode/unistr.h>

#ifdef QT_DEBUG
    #undef QT_NO_DEBUG_OUTPUT
#endif

const char  MAX_VERSION_STRING_LENGTH = 24;
const char  PROJECT_NAME[8] = "Qamus";
const char  RELEASE_NAME[16] = "çeşm";
const unsigned char MAJOR = 1;
const unsigned char MINOR = 0;
const unsigned char REVSN = 0;

const char MAX_SCORE = 100;
const char MIN_SCORE =   0;
const char INV_SCORE =  -1;

const int ERROR_NONE   =   0;
const int ERROR_MEMORY =   1;

const char16_t REPLACEMENT_CHAR = u'\uFFFD';

#ifdef ENABLE_ICU
UnicodeString QStringToUnicodeString(const QString& source);
QString UnicodeStringToQString(const UnicodeString& source);
#endif // ENABLE_ICU

#endif // COMMON_H
