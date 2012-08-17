#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QMutex>
#include <QThread>

#include "qamusmodel.h"

class SearchWorker : public QThread
{
    Q_OBJECT
public:
    explicit SearchWorker(QamusModel* qamusView, const int col, const QString term, QObject* parent);
    void run();

signals:
    void searchFinished(SearchWorker*);

private:
    int _col;
    QamusModel* _qamusView;
    QString _term;
    mutable QMutex _mutex;
};

#endif // SEARCHWORKER_H