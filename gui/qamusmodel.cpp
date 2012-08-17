#include "qamusmodel.h"

QamusModel::QamusModel(Options* const options, QObject* parent):
    QAbstractTableModel(parent),
    _options(options),
    _emptySearch(true)
{
    connect(&_qamus, SIGNAL(progress(int)), this, SIGNAL(progress(int)));
}

QamusModel::~QamusModel()
{
}

int QamusModel::columnCount(const QModelIndex&) const
{
    return columnCount();
}

int QamusModel::columnCount() const
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

int QamusModel::rowCount(const QModelIndex&) const
{
    return rowCount();
}

int QamusModel::rowCount() const
{
    return _qamus.rowCount();
}

QString QamusModel::getWord(const int col, const int row) const
{
    QMutexLocker locker(&_mutex);
    return _qamus.word(col, row);
}

QString QamusModel::getLanguage(const int col) const
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

QVariant QamusModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        if (index.column() == _qamus.columnCount())
        {
            if (_emptySearch)
            {
                return QVariant(MAX_SCORE);
            }
            else
            {
                QMutexLocker locker(&_mutex);
                return QVariant(_qamus.getScore(index.row()));
            }
        }
        else
        {
            return QVariant(getWord(index.column(), index.row()));
        }
    }
    else
    {
        return QVariant();
    }
}

QVariant QamusModel::headerData(int col, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return QVariant(getLanguage(col));
    }
    else
    {
        return QVariant();
    }
}

bool QamusModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

void QamusModel::clearSearch()
{
    _emptySearch = true;
}

bool QamusModel::loadLexicon(const QString &filename)
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

bool QamusModel::closeLexicon()
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

void QamusModel::startSearch(const int col, const QString &rawTerm)
{
    _emptySearch = false;
    _qamus.search(col, rawTerm);
#ifndef _WIN32
    if (_options->getLogToConsole())
    {
        qDebug() << "search time: " << _qamus.getSearchDuration();
    }
#endif // _WIN32
}