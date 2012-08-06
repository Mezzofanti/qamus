#include "common.h"
#include "qamusproxy.h"

QamusProxy::QamusProxy(QObject* parent): QSortFilterProxyModel(parent)
{
}

bool QamusProxy::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, sourceModel()->columnCount() - 1, source_parent);
    if (sourceModel()->data(index).toInt() == MIN_SCORE)
    {
        return false;
    }

    return true;
}
