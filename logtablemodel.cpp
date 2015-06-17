#include "logtablemodel.h"

LogTableModel::LogTableModel()
{
    QString desc("Dit is een beschrijving. ");
    QString longDesc("Nu is dit een langere beschrijving. ");
    _entries << LogEntry(QDate(2015, 6, 15), QTime(0, 30), 0, desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 17), QTime(1, 30), 1, desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 16), QTime(2, 30), 0, desc);
    std::stable_sort(_entries.begin(), _entries.end());
}

LogTableModel::~LogTableModel()
{

}

void LogTableModel::addEntry(const LogEntry &entry)
{
    _entries << entry;
    std::stable_sort(_entries.begin(), _entries.end());
    endResetModel();
}

void LogTableModel::modifyEntry(int index, const LogEntry &entry)
{
    if (index >= 0 && index < _entries.count()) {
        _entries[index] = entry;
        std::stable_sort(_entries.begin(), _entries.end());
        //        endResetModel();
    }
}

void LogTableModel::removeEntry(int index)
{
    if (index >= 0 && index < _entries.count()) {
        _entries.removeAt(index);
        endResetModel();
    }
}

int LogTableModel::rowCount(const QModelIndex &parent) const
{
    return _entries.count();
}

int LogTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant LogTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            value = _entries.at(index.row()).date().toString("dd/MM/yyyy");
            break;
        case 1:
            value = _entries.at(index.row()).duration().toString("H'h'mm'm'");
            break;
        case 2:
            value = _entries.at(index.row()).type();
            break;
        case 3:
            value = _entries.at(index.row()).description();
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
