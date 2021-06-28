#include "newvisitview.h"

NewVisitView::NewVisitView(QVBoxLayout *menu, DatabaseController &db) : EditMenuView(menu), db{db}
{
}

NewVisitView::~NewVisitView(){
    clean(this->menu);
}

void NewVisitView::build(){

    this->clean(this->menu);
    QFormLayout *form = new QFormLayout();
    patientInput = new QComboBox();
    QVector<Patient> patients = db.getPatients();
    for(int i=0; i<patients.count(); i++){
        QVariant itemData;
        itemData.setValue(patients[i].getId());
        patientInput->addItem(patients[i].toString(), itemData);
    }
    dateInput = new QDateEdit(QDate::currentDate());
    dateInput->setDisplayFormat("dd-MM-yyyy");
    isHospitalInput = new QCheckBox("");
    isHospitalInput->setCheckState(Qt::CheckState::Unchecked);
    descriptionInput = new QTextEdit();
    medicinesInput = new QTextEdit();

    QPushButton *submit = new QPushButton("submit");


    form->addRow("Patient", patientInput);
    form->addRow("Date", dateInput);
    form->addRow("Sent to hospital", isHospitalInput);
    form->addRow("Description", descriptionInput);
    form->addRow("Medicines", medicinesInput);
    menu->addLayout(form);
    menu->addWidget(submit);
    QObject::connect(submit, &QPushButton::clicked, this, &NewVisitView::handleSubmit);
}


void NewVisitView::handleSubmit(bool checked){
    int patientId = patientInput->currentData().toInt();
    QDate visitDate = dateInput->date();
    int isHospital = isHospitalInput->checkState() == Qt::Checked ? 1 : 0;
    QString description = descriptionInput->toPlainText();
    QString medicines = medicinesInput->toPlainText();
    Visit newVisit(patientId, visitDate, description, medicines, isHospital);
    db.addVisit(newVisit);
}
