#ifndef LOGBOOKMODEL_H
#define LOGBOOKMODEL_H

#include <QList>
#include "entrytype.h"
#include "logentry.h"

class LogbookModel
{
public:
    LogbookModel();
    ~LogbookModel();
    void addEntry(const LogEntry &entry);
    void deleteEntry(int index);
    const QList<LogEntry> *entries() const {return &_entries;}
    void modifyEntry(int index, const LogEntry &entry);
    QList<EntryType> types() const {return _types;}

private:
    QList<LogEntry> _entries;
    QList<EntryType> _types;
};

#endif // LOGBOOKMODEL_H
