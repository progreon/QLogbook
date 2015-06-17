#ifndef ENTRYTYPE_H
#define ENTRYTYPE_H

#include <QString>

class EntryType
{
public:
    EntryType(int id, const QString &name);
    ~EntryType();
    int id() const {return _id;}
    void setName(const QString &name);
    QString name() const {return _name;}

private:
    int _id;
    QString _name;
};

#endif // ENTRYTYPE_H
