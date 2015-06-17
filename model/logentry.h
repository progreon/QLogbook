#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QDate>
#include <QTime>
#include <QList>
#include "entrytype.h"

class LogEntry
{
public:
    LogEntry(const QDate &date, const QTime &duration, EntryType logType, const QString &description);
    ~LogEntry();
    QDate date() const {return _date;}
    QString description() const {return _description;}
    QTime duration() const {return _duration;}
    EntryType type() const {return _type;}
    void setDate(const QDate &date);
    void setDuration(const QTime &duration);
    void setType(EntryType type);
    void setDescription(const QString &description);
    bool operator<(const LogEntry &logEntry) const;

private:
    QDate _date;
    QTime _duration;
    EntryType _type;
    QString _description;
};

#endif // LOGENTRY_H
