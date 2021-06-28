#ifndef NEWVISITVIEW_H
#define NEWVISITVIEW_H

#include "editmenuview.h"
#include "../Controller/databasecontroller.h"
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
class NewVisitView : public EditMenuView
{
private:
    DatabaseController&db;
    QComboBox *patientInput;
    QDateEdit *dateInput;
    QCheckBox *isHospitalInput;
    QTextEdit *descriptionInput;
    QTextEdit *medicinesInput;



public:
    NewVisitView(QVBoxLayout *menu, DatabaseController &db);
    ~NewVisitView();

    void build() override;
    void handleSubmit(bool checked);
};

#endif // NEWVISITVIEW_H
