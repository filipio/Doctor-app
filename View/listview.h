#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QObject>
#include <QListWidget>
#include "../Model/patient.h"
#include <QVector>
#include "../View/listview.h"
#include <stringabledatabaseitem.h>

class ListView : public QObject
{
private:
    QListWidget *list;
    bool ascending;

    Q_OBJECT
public:
    explicit ListView(QListWidget * list , QObject *parent = nullptr, bool ascending = true);
    void cleanList();

signals:

public slots:
    void insertItem(const StringableDatabaseItem &item);
};

#endif // LISTVIEW_H
