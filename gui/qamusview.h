#ifndef QAMUSVIEW_H
#define QAMUSVIEW_H

#include <QAbstractTableModel>
#include <QMutex>

#include "options.h"
#include "qamus.h"

class QamusView : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QamusView(Options *const options, QObject* parent = 0);
    ~QamusView();

    int columnCount(const QModelIndex& parent) const;
    int columnCount() const;
    int rowCount(const QModelIndex& parent) const;
    int rowCount() const;

    QString getWord(const int col, const int row) const;
    QString getLanguage(const int col) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    void clearSearch();

    bool loadLexicon(const QString& filename);
    bool closeLexicon();
    void startSearch(const int col, const QString&rawTerm);

signals:
    void progress(const int);

private:
    Options* _options;
    Qamus _qamus;
    bool _emptySearch;
    mutable QMutex _mutex;
};

#endif // QAMUSVIEW_H
