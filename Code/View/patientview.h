#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include "editmenuview.h"
#include "../Controller/databasecontroller.h"
#include <QListWidgetItem>
#include <labelimage.h>
#include <ieditablegui.h>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
class PatientView : public EditMenuView, public IEditableGUI
{
private:
    DatabaseController &db;
    QLineEdit *inputName;
    QLineEdit *inputSurname;
    QLineEdit *inputNumber;
    QSpinBox *inputAge;
    QVBoxLayout *dataLayout;
    Patient patient;

    void bold(QLabel *label);

    Q_OBJECT

public:
    PatientView(QVBoxLayout *menu, DatabaseController &db);
    ~PatientView();
    void build() override;
    void launchEditMode() override;


    void setPatient(const Patient &value);

signals:
    void lastVisit(int id);

public slots:
    void buildPatient(const Patient& patient);
    void deleteHandler(bool checked);
    void patientClickedHandler(QListWidgetItem * item);
    void saveHandler(bool checked);
    void lastVisitHandler(bool checked);
    void editModeHandler(bool checked){
        launchEditMode();
    }
};

#endif // PATIENTVIEW_H
