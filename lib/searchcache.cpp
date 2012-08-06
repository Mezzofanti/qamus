#include "common.h"
#include "searchcache.h"

SearchCache::SearchCache(const QString& rawTerm, const QString& term, const int col, const int size)
{
    _rawTerm = rawTerm;
    _term = term;
    _col = col;
    _new = true;
    _startTime = QDateTime::currentDateTimeUtc();
    setActive(size);
}

SearchCache::SearchCache(const QString &rawTerm, const QString &term, SearchCache *baseCache)
{
    _rawTerm = rawTerm;
    _term = term;
    _col = baseCache->_col;
    _scores = baseCache->_scores;
    _new = false;
    _startTime = QDateTime::currentDateTimeUtc();
}

SearchCache::~SearchCache()
{
}

QDateTime SearchCache::getTime() const
{
    return _startTime;
}

void SearchCache::searchFinished()
{
    _endTime = QDateTime::currentDateTimeUtc();
}

short SearchCache::at(const int row) const
{
    return _scores.at(row);
}

void SearchCache::set(const int row, const char score)
{
    _scores.at(row) = score;
}


void SearchCache::setActive(const int size)
{
    int oldSize = _scores.size();
    if (oldSize < size)
    {
        _scores.resize(size);
        for (int i = oldSize; i < size; ++i)
        {
            _scores.at(i) = INV_SCORE;
        }
    }
}

int SearchCache::size() const
{
    return (int)_scores.size();
}

int SearchCache::getCol() const
{
    return _col;
}

char SearchCache::getScore(int row) const
{
    return _scores.at(row);
}

bool SearchCache::getNew() const
{
    return _new;
}

QString SearchCache::getTerm() const
{
    return _term;
}

QString SearchCache::getRawTerm() const
{
    return _rawTerm;
}

qint64 SearchCache::getDuration() const
{
    return _startTime.msecsTo(_endTime);
}