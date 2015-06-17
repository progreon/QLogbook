#include "logbookmodel.h"

LogbookModel::LogbookModel()
{
    _types << EntryType(0, "Literatuur");
    _types << EntryType(1, "Implementatie");

    QString desc("Dit is een beschrijving. ");
    QString longDesc("Nu is dit een langere beschrijving. ");
    _entries << LogEntry(QDate(2015, 6, 15), QTime(0, 30), _types.at(0), desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 17), QTime(1, 30), _types.at(1), desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 16), QTime(2, 30), _types.at(0), desc);
    std::stable_sort(_entries.begin(), _entries.end());
}

LogbookModel::~LogbookModel()
{

}

void LogbookModel::addEntry(const LogEntry &entry)
{
    _entries << entry;
    std::stable_sort(_entries.begin(), _entries.end());
}

void LogbookModel::deleteEntry(int index)
{
    if (index >= 0 && index < _entries.count()) {
        _entries.removeAt(index);
    }
}

void LogbookModel::modifyEntry(int index, const LogEntry &entry)
{
    if (index >= 0 && index < _entries.count()) {
        _entries[index] = entry;
        std::stable_sort(_entries.begin(), _entries.end());
    }
}

