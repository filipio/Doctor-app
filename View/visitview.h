#ifndef VISITVIEW_H
#define VISITVIEW_H

#include "editmenuview.h"
#include "../Controller/databasecontroller.h"
#include <QListWidgetItem>
#include <labelimage.h>
#include <QPushButton>
#include <QTextBrowser>
#include <QCheckBox>
#include <QSpacerItem>
#include <ieditablegui.h>
#include <QDateEdit>
class VisitView : public EditMenuView, public IEditableGUI
{
private:
    DatabaseController &db;
    Visit visit;
    QDateEdit *dateInput;
    QCheckBox *isHospitalInput;
    QTextEdit *descriptionInput;
    QTextEdit *medicinesInput;
    QVBoxLayout *bodyLayout;

    Q_OBJECT

public:
    VisitView(QVBoxLayout *menu, DatabaseController &db);
    ~VisitView();
    void build() override;
    void buildVisit(const Visit &visit);
    void launchEditMode() override;

    void setVisit(const Visit &value);
    void bold(QLabel *label);

signals:
    void patientClicked(int patientId);

public slots:
    void visitClickedHandler(QListWidgetItem *item);
    void goToPatientHandler(bool checked);
    void deleteHandler(bool checked);
    void saveHandler(bool checked);
    void editModeHandler(bool checked){
        launchEditMode();
    }

};

#endif // VISITVIEW_H
