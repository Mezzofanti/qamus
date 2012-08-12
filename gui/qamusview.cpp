#include "qamusview.h"

QamusView::QamusView(Options* const options, QObject* parent):
    QAbstractTableModel(parent),
    _options(options)
{
    connect(&_qamus, SIGNAL(progress(int)), this, SIGNAL(progress(int)));
}

QamusView::~QamusView()
{
}

int QamusView::columnCount(const QModelIndex&) const
{
    return columnCount();
}

int QamusView::columnCount() const
{
    int cols = _qamus.columnCount();
    if (cols == 0)
    {
        return 0;
    }
    else
    {
        return cols + 1;
    }
}

int QamusView::rowCount(const QModelIndex&) const
{
    return rowCount();
}

int QamusView::rowCount() const
{
    return _qamus.rowCount();
}

QVariant QamusView::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        QMutexLocker locker(&_mutex);
        if (index.column() == _qamus.columnCount())
        {
            return QVariant(_qamus.getScore(index.row()));
        }
        else
        {
            return QVariant(_qamus.word(index.column(), index.row()));
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant QamusView::headerData(int col, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        QMutexLocker locker(&_mutex);
        if (col == _qamus.columnCount())
        {
            return tr("Score");
        }
        else
        {
            return _qamus.getLanguage(col);
        }
    }
    else
    {
        return QVariant();
    }
}

bool QamusView::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::DisplayRole)
    {
        QMutexLocker locker(&_mutex);
        bool result = _qamus.setWord(index.column(), index.row(), value.toString());
        if (result)
        {
            emit dataChanged(index, index);
        }

        return result;
    }
    else
    {
        return false;
    }
}

bool QamusView::loadLexicon(const QString &filename)
{
    _mutex.lock();
    bool result = _qamus.loadLexicon(filename);
    _mutex.unlock();

    if (result)
    {
        reset();
    }

    return result;
}

bool QamusView::closeLexicon()
{
    _mutex.lock();
    bool result = _qamus.closeLexicon();
    _mutex.unlock();

    if (result)
    {
        reset();
    }

    return result;
}

void QamusView::startSearch(const int col, const QString &rawTerm)
{
    _qamus.search(col, rawTerm);
#ifndef _WIN32
    if (_options->getLogToConsole())
    {
        qDebug() << "search time: " << _qamus.getSearchDuration();
    }
#endif // _WIN32
}


