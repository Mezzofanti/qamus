#include <algorithm>

#include "searchworker.h"

SearchWorker::SearchWorker(QamusModel* qamusView, const int col, const QString term, QObject* parent) :
    QThread(parent)
{
    _qamusView = qamusView;
    _col = col;
    _term = term;
}

void SearchWorker::run()
{
    Q_ASSERT(_col >= 0 && _col < _qamusView->columnCount());
    _mutex.lock();
    _qamusView->startSearch(_col, _term);
    _mutex.unlock();
    emit searchFinished(this);
}

