#include "common.h"
#include "qlxxmlhandler.h"

QlxXmlHandler::QlxXmlHandler():
    DictXmlHandler()
{
    _validTags =
    {
        { "author",         XMLTAG::author},
        { "code",           XMLTAG::code},
        { "description",    XMLTAG::description},
        { "entry",          XMLTAG::entry},
        { "import",         XMLTAG::import},
        { "input",          XMLTAG::input},
        { "language",       XMLTAG::language},
        { "lex",            XMLTAG::lex},
        { "lexeme",         XMLTAG::lex},
        { "meta",           XMLTAG::meta},
        { "name",           XMLTAG::name},
        { "qamus",          XMLTAG::qamus},
        { "script",         XMLTAG::script},
#ifdef ENABLE_ICU
        { "transform",      XMLTAG::transliteration},
        { "transliteration",XMLTAG::transliteration}
#endif
    };
}

QlxXmlHandler::~QlxXmlHandler()
{
}


bool QlxXmlHandler::startDocument()
{
    return true;
}


bool QlxXmlHandler::startElement(const QString&, const QString&, const QString& tagString, const QXmlAttributes& attributes)
{
    XMLTAG currentTag;

    if (!getXmlTag(tagString, currentTag))
    {
        ++_invalidTagDepth;
        qWarning() << "ignoring invalid XML tag: " << tagString;
    }

    if (_invalidTagDepth == 0)
    {
    switch (currentTag)
    {
    case author:
        if (_tagStack.top() == qamus)
        {
           _author.clear();
        }
        break;

    case code:
        if (_tagStack.top() != language)
        {
            return false;
        }
        break;

    case description:
        if (_tagStack.top() == qamus)
        {
            _description.clear();
        }
        break;

    case entry:
        _entry.clear();
        _metadata.clear();
        break;


    case import:
        if (_tagStack.top() != transliteration)
        {
            return false;
        }
        break;

    case input:
        if (_tagStack.top() != qamus)
        {
            return false;
        }
        break;

    case language:
        _languageId = attributes.value("id");
        if (_languageId.isEmpty())
        {
            return false;
        }
        else
        {
            _language.setId(_languageId);
        }
        break;

    case lex:
        if (_tagStack.top() != entry)
        {
            return false;
        }
        _lexeme.clear();
        _languageId = attributes.value("id");
        if (_languageId.isEmpty())
        {
            return false;
        }
        break;

    case meta:
        if (_tagStack.top() != entry)
        {
            return false;
        }
        _metaId = attributes.value("id");
        break;

    case name:
        if (_tagStack.top() == qamus)
        {
            _name.clear();
        }
        else if (_tagStack.top() != language)
        {
            return false;
        }
        break;

    case qamus:
        if (_tagStack.size() != 0)
        {
            return false;
        }
        break;

    case script:
        if (_tagStack.top() != language)
        {
            return false;
        }
        break;

    case transliteration:
        if (_tagStack.top() == input)
        {
            // nothing to do
        }
        else if (_tagStack.top() == language)
        {
            if (!attributes.value("source").isEmpty())
            {
                _transcriptionLanguages.insert(std::make_pair(attributes.value("source"), _languageId));
            }
        }
        else
        {
            return false;
        }
        break;

    default:
        ++_invalidTagDepth;
        break;
    }
    }

    _tagStack.push(currentTag);
    return true;
}


/*
 Deal with the data between tags. The data is stored to be inserted into the data structure after the close tag for this word.
 */
bool QlxXmlHandler::characters(const QString& data)
{
    if (_invalidTagDepth > 0)
    {
        return true;
    }

    XMLTAG currentTag = _tagStack.top();
    _tagStack.pop();

    switch (currentTag)
    {
    case author:
        _author = data;
        break;

    case code:
        if (_tagStack.top() == language)
        {
            _language.setIso639_2(data);
        }
        else
        {
            return false;
        }
        break;

    case description:
        _description = data;
        break;

    case entry:
        break;

    case language:
        break;

    case lex:
        _lexeme.set(data);
        break;

    case meta:
        _metadata.insert(std::make_pair(_metaId, data));
        break;

    case name:
        if (_tagStack.top() == qamus)
        {
            _name = data;
        }
        else if (_tagStack.top() == language)
        {
            _language.setDescription(data);
        }
        else
        {
            return false;
        }
        break;

    case script:
        if (_tagStack.top() == language)
        {
            _language.setIso15924(data);
        }
        else
        {
            return false;
        }
        break;

    case transliteration:
#ifdef ENABLE_ICU
        if (_tagStack.top() == input)
        {
            _transliterator = createTransliterator("input", data);
        }
        else if (_tagStack.top() == language)
        {
            _language.setTransliterator(createTransliterator(_languageId, data));
        }
        else
        {
            return false;
        }
#endif
        break;

    default:
        break;
    }

    _tagStack.push(currentTag);

    return true;
}



/*
 When a fields element closes, then set up the data structure with headers.
 When a word element closes, then we must put the collected data into the rule model data strucutre.
 */
bool QlxXmlHandler::endElement(const QString&, const QString&, const QString& tagString)
{
    XMLTAG currentTag;
    XMLTAG topTag = _tagStack.top();
    _tagStack.pop();

    if (getXmlTag(tagString, currentTag))
    {
         if (topTag != currentTag)
         {
             return false;
         }
    }
    else
    {
        --_invalidTagDepth;
        return true;
    }

    if (_invalidTagDepth > 0)
    {
        return true;
    }

    switch (currentTag)
    {
    case author:
    case code:
    case description:
    case import:
    case input:
    case meta:
    case name:
    case qamus:
    case script:
    case transliteration:
        break;

    case language:
        _languages.push_back(std::move(_language));
        _language.clear();
        break;

    case entry:
        _entries.push_back(_entry);
        _metadataList.push_back(_metadata);
        break;

    case lex:
        _entry.insert(std::make_pair(_languageId, _lexeme));
        break;

    default:
        --_invalidTagDepth;
        break;
    }

    return true;
}


/*
 When parsing has finished, find the languages which were marked as being
 transliterations of another language, and copy the contents of the source
 entries to the target entries.
 */
bool QlxXmlHandler::endDocument()
{
    for (auto langIt = _transcriptionLanguages.begin(); langIt != _transcriptionLanguages.end(); ++langIt)
    {
        QString source = (*langIt).first;
        QString target = (*langIt).second;

        for (auto it = _entries.begin(); it != _entries.end(); ++it)
        {
            auto entry = *it;
            auto lexemeIt = entry.find(source);
            if (lexemeIt != entry.end())
            {
                Lexeme lexeme = (*lexemeIt).second;
                entry.insert(std::make_pair(target, lexeme));
                *it = entry;
            }
        }
    }

    return true;
}
