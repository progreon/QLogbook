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
    QString currentOpenFile() const;
    void deleteEntry(int index);
    QString description() const {return _description;}
    const QList<LogEntry> *entries() const {return &_entries;}
    bool exportLogbookPDF(const QString &fileName);
    bool isEdited() const {return _isEdited;}
    bool isNew() const {return _isNew;}
    void loadLogbookJSON(const QString &fileName);
    void modifyEntry(int index, const LogEntry &entry);
    void saveLogbookJSON();
    void saveAsLogbookJSON(const QString &fileName);
    void setDescription(const QString &description);
    void startEmptyLogbook();
    QList<EntryType> types() const {return _types;}

private:
    QString _description;
    QList<LogEntry> _entries;
    QList<EntryType> _types;
    bool _isEdited;
    bool _isNew;
    QString _currentOpenFile;
};

#endif // LOGBOOKMODEL_H
