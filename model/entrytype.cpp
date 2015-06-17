#include "entrytype.h"

EntryType::EntryType(int id, const QString &name)
    : _id(id)
    , _name(name)
{

}

EntryType::~EntryType()
{

}

void EntryType::setName(const QString &name)
{
    _name = name;
}

