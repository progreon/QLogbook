#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include <QAbstractTableModel>
#include "logentry.h"
#include <QList>

class LogTableModel : public QAbstractTableModel
{
public:
    LogTableModel();
    ~LogTableModel();
    QList<LogEntry> entries() const {return _entries;}

private:
    QList<LogEntry> _entries;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // LOGTABLEMODEL_H
