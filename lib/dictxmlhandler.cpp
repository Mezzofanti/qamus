#include "dictxmlhandler.h"

DictXmlHandler::DictXmlHandler():
    XmlHandler()
{
#ifdef ENABLE_ICU
    _transliterator = nullptr;
#endif
    _invalidTagDepth = 0;
}

DictXmlHandler::~DictXmlHandler()
{
    _entries.clear();
    _languages.clear();
}

const std::vector<Language>& DictXmlHandler::getLanguages() const
{
    return _languages;
}

int DictXmlHandler::getEntryCount() const
{
    return _entries.size();
}

Entry DictXmlHandler::getEntry(const int pos) const
{
    Entry entry(_languages.size());

    auto const* lexemes = &_entries.at(pos);
    int i = 0;
    for (auto it = _languages.begin(); it != _languages.end(); ++it)
    {
        auto element = lexemes->find((*it).getId());
        if (element != lexemes->end())
        {
            entry.setLexeme(i, element->second);
        }

        ++i;
    }

    auto const* metadata = &_metadataList.at(pos);
    for (auto it = metadata->begin(); it != metadata->end(); ++it)
    {
        entry.setMetadata((*it).first, (*it).second);
    }

    return entry;
}