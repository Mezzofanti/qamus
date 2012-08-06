#ifndef DICTXMLHANDLER_H
#define DICTXMLHANDLER_H

#include <map>
#include <vector>

#include "xmlhandler.h"
#include "entry.h"
#include "language.h"

class Lexicon;


class DictXmlHandler: public XmlHandler
{
public:
    DictXmlHandler();
    virtual ~DictXmlHandler();
    const std::vector<Language>& getLanguages() const;
    int getEntryCount() const;
    Entry getEntry(const int pos) const;

#ifdef ENABLE_ICU
    Transliterator* getTransliterator() { return _transliterator; }
#endif

    const QString& getName() const { return _name; }
    const QString& getAuthor() const { return _author; }
    const QString& getDescription() const { return _description; }

protected:
    QString _name;
    QString _author;
    QString _description;

#ifdef ENABLE_ICU
    Transliterator* _transliterator;
#endif

    std::vector<Language> _languages;
    std::vector<std::map<QString, Lexeme> > _entries;
    std::vector<std::map<QString, QString> > _metadataList;
};

#endif // DICTXMLHANDLER_H
