#ifndef EDITMENUVIEW_H
#define EDITMENUVIEW_H

#include <QFormLayout>
#include <QObject>
#include <QWidget>
#include <QGroupBox>
class EditMenuView : public QObject
{
    Q_OBJECT
protected:
    QVBoxLayout *menu = nullptr;
    QWidget *mainWidget;
    void clean(QLayout *layout,bool deleteWidgets = true){
        while (layout->count() > 0)
        {
            QLayoutItem* item = layout->takeAt(0);
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout())
                clean(childLayout, deleteWidgets);
            delete item;
        }

    }

public:
    EditMenuView(QVBoxLayout *menu);
    virtual ~EditMenuView(){}
    virtual void build() = 0;
};

#endif // EDITMENUVIEW_H
