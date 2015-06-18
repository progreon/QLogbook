#include "logtablemodel.h"

LogTableModel::LogTableModel(LogbookModel *model)
    : _model(model)
{

}

LogTableModel::~LogTableModel()
{

}

void LogTableModel::refreshTable()
{
    this->endResetModel();
}

int LogTableModel::rowCount(const QModelIndex &parent) const
{
    return _model->entries()->count();
}

int LogTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant LogTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (role == Qt::DisplayRole) {
        LogEntry entry = _model->entries()->at(index.row());
        switch (index.column()) {
        case 0:
            value = entry.date().toString("dd/MM/yyyy");
            break;
        case 1:
            value = entry.duration().toString("H'h'mm'm'");
            break;
        case 2:
            value = entry.type().name();
            break;
        case 3:
            value = entry.description();
            break;
        default:
            value = QString("ERROR");
            break;
        }
    }
    return value;
}

QVariant LogTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value;
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            value = QString("Datum");
            break;
        case 1:
            value = QString("Duur");
            break;
        case 2:
            value = QString("Type");
            break;
        case 3:
            value = QString("Beschrijving");
            break;
        default:
            value = QString("ERROR");
            break;
        }
    } else if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        value = section + 1;
    }
    return value;
}
