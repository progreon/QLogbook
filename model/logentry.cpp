#include "logentry.h"

LogEntry::LogEntry(const QDate &date, const QTime &duration, EntryType logType, const QString &description)
    : _date(date)
    , _duration(duration)
    , _type(logType)
    , _description(description)
{

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

void LogEntry::setType(EntryType type)
{
    _type = type;
}

void LogEntry::setDescription(const QString &description)
{
    _description = description;
}

bool LogEntry::operator<(const LogEntry &logEntry) const
{
    return this->date() < logEntry.date();
}

//bool LogEntry::cmpLtDates(const LogEntry &entry1, const LogEntry &entry2)
//{
//    return entry1.date() < entry2.date();
//}

//bool LogEntry::cmpLtDurations(const LogEntry &entry1, const LogEntry &entry2)
//{
//    return entry1.duration() < entry2.duration();
//}

//bool LogEntry::cmpLtTypes(const LogEntry &entry1, const LogEntry &entry2)
//{
//    return entry1.type() < entry2.type();
//}

//bool LogEntry::cmpLtDescriptions(const LogEntry &entry1, const LogEntry &entry2)
//{
//    return entry1.description() < entry2.description();
//}

