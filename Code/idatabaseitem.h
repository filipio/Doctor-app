#ifndef IDATABASEITEM_H
#define IDATABASEITEM_H


class IDatabaseItem
{

public:
    IDatabaseItem();
    virtual ~IDatabaseItem(){}
    virtual int getId() const = 0;
};

#endif // IDATABASEITEM_H
