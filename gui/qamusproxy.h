#ifndef QAMUSPROXY_H
#define QAMUSPROXY_H

#include <QSortFilterProxyModel>

class QamusProxy : public QSortFilterProxyModel
{
public:
    QamusProxy(QObject* parent);
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
};

#endif // QAMUSPROXY_H
