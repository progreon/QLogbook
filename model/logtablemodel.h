#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "logbookmodel.h"
#include "logentry.h"

class LogTableModel : public QAbstractTableModel
{
public:
    LogTableModel(LogbookModel *model);
    ~LogTableModel();
    void refreshTable();

private:
    LogbookModel *_model;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // LOGTABLEMODEL_H
