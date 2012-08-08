#include "common.h"
#include "xmlhandler.h"

XmlHandler::XmlHandler(): QXmlDefaultHandler() {}

bool XmlHandler::fatalError(const QXmlParseException& e)
{
    qDebug() << e.message() << " line:" << e.lineNumber() << " column:" << e.columnNumber();
    return false;
}

XmlHandler::~XmlHandler()
{
}

#ifdef ENABLE_ICU
Transliterator* XmlHandler::createTransliterator(const QString& id, const QString& source)
{
    UnicodeString usId = UnicodeString::fromUTF8(id.toStdString());
    UnicodeString usRules = UnicodeString::fromUTF8(source.toStdString());
    UParseError parseError;
    UErrorCode status;
    Transliterator* transliterator = Transliterator::createFromRules(usId, usRules, UTRANS_FORWARD, parseError, status);
    if (U_FAILURE(status))
    {
        Q_ASSERT(transliterator == nullptr);
        qWarning() << "unable to load transliterator: " << u_errorName(status);
    }
    else
    {
        Q_ASSERT(transliterator != nullptr);
    }

    return transliterator;
}
#endif

bool XmlHandler::checkBoolString(const QString& string, const bool defaultValue)
{
    if (defaultValue == true)
    {
        if (string == "0")
            return false;
        if (string == "no")
            return false;
        if (string == "false")
            return false;
    }
    else
    {
        if (string == "1")
            return true;
        if (string == "yes")
            return true;
        if (string == "true")
            return true;
    }

    return defaultValue;
}

/*
 Get the code for a tag string (limited to those found in Qamus XML files).
 */
bool XmlHandler::getXmlTag(const QString& tagString, XMLTAG& tagType)
{
    auto iter = _validTags.find(tagString.toLower());
    if (iter == _validTags.end())
    {
        return false;
    }

    tagType = iter->second;
    return true;
}
