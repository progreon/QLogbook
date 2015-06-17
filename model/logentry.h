#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QDate>
#include <QTime>
#include <QList>

class LogEntry
{
public:
    LogEntry(const QDate &date, const QTime &duration, int logType, const QString &description);
    ~LogEntry();
    QDate date() const {return _date;}
    QString description() const {return _description;}
    QTime duration() const {return _duration;}
    QString type() const {return logTypes.at(_type);}
    QList<QString> types() const {return logTypes;}
    void setDate(const QDate &date);
    void setDuration(const QTime &duration);
    void setType(int typeID);
    void setDescription(const QString &description);
    bool operator<(const LogEntry &logEntry) const;
//    static bool cmpLtDates(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpLtDurations(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpLtTypes(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpLtDescriptions(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpGtDates(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpGtDurations(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpGtTypes(const LogEntry &entry1, const LogEntry &entry2);
//    static bool cmpGtDescriptions(const LogEntry &entry1, const LogEntry &entry2);

private:
    QDate _date;
    QTime _duration;
    int _type;
    QString _description;
    QList<QString> logTypes;
};

#endif // LOGENTRY_H
