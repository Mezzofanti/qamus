#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QMutex>
#include <QThread>

#include "qamusview.h"

class SearchWorker : public QThread
{
    Q_OBJECT
public:
    explicit SearchWorker(QamusView* qamusView, const int col, const QString term, QObject* parent);
    void run();

signals:
    void searchFinished(SearchWorker*);

private:
    int _col;
    QamusView* _qamusView;
    QString _term;
    mutable QMutex _mutex;
};

#endif // SEARCHWORKER_H