#include "listview.h"
ListView::ListView(QListWidget *list, QObject *parent, bool ascending) :
    QObject(parent), list{list}, ascending{ascending}{}

void ListView::cleanList()
{
    this->list->clear();
}

void ListView::insertItem(const StringableDatabaseItem &item){

    QListWidgetItem *newItem = new QListWidgetItem(item.toString());
    QVariant itemData;
    itemData.setValue(item.getId());
    newItem->setData(Qt::UserRole, itemData);
    list->addItem(newItem);
}

