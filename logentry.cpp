#include "logentry.h"

LogEntry::LogEntry(const QDate &date, const QTime &duration, int logType, const QString &description)
    : _date(date)
    , _duration(duration)
    , _type(logType)
    , _description(description)
{
    logTypes << "Literatuur";
    logTypes << "Implementatie";
}

LogEntry::~LogEntry()
{

}

void LogEntry::setDate(const QDate &date)
{
    _date = date;
}

void LogEntry::setDuration(const QTime &duration)
{
    _duration = duration;
}

void LogEntry::setType(int typeID)
{
    _type = typeID;
}

void LogEntry::setDescription(const QString &description)
{
    _description = description;
}

bool LogEntry::operator<(const LogEntry &logEntry) const
{
    return this->date() < logEntry.date();
}

