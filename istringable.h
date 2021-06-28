#ifndef ISTRINGABLE_H
#define ISTRINGABLE_H
#include <QString>

class IStringable
{
public:
    IStringable();
    virtual ~IStringable(){}
    virtual QString toString() const = 0;
};

#endif // ISTRINGABLE_H
