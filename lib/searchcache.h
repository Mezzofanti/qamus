#ifndef SEARCHCACHE_H
#define SEARCHCACHE_H

#include <QDateTime>
#include <vector>

/* SearchCache
 * Contains the results of a search.
 */
class SearchCache
{
public:
    SearchCache(const QString& rawTerm, const QString& term, const int col, const int size);
    SearchCache(const QString& rawTerm, const QString& term, SearchCache* baseCache);
    ~SearchCache();
    QDateTime getTime() const;
    void searchFinished();
    short at(const int row) const;
    void set(const int row, const char score);
    void setActive(const int size);
    int size() const;
    int getCol() const;
    char getScore(int row) const;
    bool getNew() const;
    QString getTerm() const;
    QString getRawTerm() const;
    qint64 getDuration() const;

private:
    std::vector<char> _scores;
    QDateTime _startTime;
    QDateTime _endTime;
    int _col;
    QString _rawTerm;
    QString _term;
    bool _new;
};

#endif // SEARCHCACHE_H
