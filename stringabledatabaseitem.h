#ifndef STRINGABLEDATABASEITEM_H
#define STRINGABLEDATABASEITEM_H
#include <istringable.h>
#include <idatabaseitem.h>

class StringableDatabaseItem : public IStringable, public IDatabaseItem
{
public:
    StringableDatabaseItem();
    virtual ~StringableDatabaseItem(){}
};

#endif // STRINGABLEDATABASEITEM_H
