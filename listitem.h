#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>

class ListItem : public QListWidgetItem
{
public:
    ListItem(int id);

private:
    int id;
};

#endif // LISTITEM_H
