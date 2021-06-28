#ifndef NEWPATIENTVIEW_H
#define NEWPATIENTVIEW_H

#include "editmenuview.h"
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGroupBox>
#include "../Model/patient.h"
#include "../Controller/databasecontroller.h"
#include <QSpinBox>
class NewPatientView : public EditMenuView
{
private:
    DatabaseController &db;
    QLineEdit *inputName;
    QLineEdit *inputSurname;
    QLineEdit *inputNumber;
    QSpinBox *inputAge;
    QComboBox *inputGender;
    QRegExpValidator *onlyCharsValidator;



public:
    NewPatientView(QVBoxLayout *menu, DatabaseController &db);
    ~NewPatientView();

    void build() override;

public slots:
    void handleNumberEntered();
    void handleSubmit(bool checked);
};

#endif // NEWPATIENTVIEW_H
