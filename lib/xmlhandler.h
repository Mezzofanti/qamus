#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#ifdef ENABLE_ICU
#include <unicode/translit.h>
#endif

#include <QXmlDefaultHandler>
#include <stack>
#include <map>


class XmlHandler: public QXmlDefaultHandler
{
public:
    enum XMLTAG { author, code, description, entry, id, import, input,
                  language, lex, meta, name, null, qamus, script, source, transliteration };

public:
    XmlHandler();
    virtual ~XmlHandler();

#ifdef ENABLE_ICU
    Transliterator* createTransliterator(const QString &id, const QString &source);
#endif

protected:
    int _invalidTagDepth;
    static bool checkBoolString(const QString& string, const bool defaultValue = false);
    bool getXmlTag(const QString& tagString, XMLTAG& tagType);
    virtual bool fatalError(const QXmlParseException&);
    std::stack<XMLTAG> _tagStack;
    std::map<QString, XMLTAG> _validTags;
};

#endif // XMLHANDLER_H