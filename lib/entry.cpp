#include "entry.h"

Entry::Entry(const int size):
    _lexemes(size)
{
}

Entry::Entry(const Entry& that)
{
    *this = that;
}

Entry& Entry::operator=(const Entry& that)
{
    Q_ASSERT(this != &that);
    _lexemes = that._lexemes;
    return *this;
}

Entry::~Entry()
{
    _lexemes.clear();
    _metadata.clear();
}

QString Entry::getWord(const int col) const
{
    return _lexemes.at(col).get();
}

QString Entry::getTransliteration(const int col) const
{
    return _lexemes.at(col).getTransliteration();
}

void Entry::setLexeme(const int i, const Lexeme& lexeme)
{
    _lexemes.at(i) = lexeme;
}

Lexeme& Entry::getLexeme(const int i)
{
    return _lexemes.at(i);
}

void Entry::setMetadata(const QString id, const QString data)
{
    _metadata.insert(std::make_pair(id, data));
}