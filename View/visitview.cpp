#include "visitview.h"

void VisitView::setVisit(const Visit &value)
{
    visit = value;
}

void VisitView::bold(QLabel *label)
{
    label->setStyleSheet("font-size : 16px; font-weight : bold");
}

VisitView::VisitView(QVBoxLayout *menu, DatabaseController &db) : EditMenuView(menu), db{db}
{
}

VisitView::~VisitView()
{
    this->clean(this->menu);
}

void VisitView::build()
{
    this->clean(this->menu);
    Patient patient = db.getPatient(visit.getPatientId());
        LabelImage *qLblImg = new LabelImage();
        qLblImg->setFrameStyle(QFrame::Raised | QFrame::Box);
        qLblImg->setAlignment(Qt::AlignTop);
        qLblImg->setSizePolicy(
          QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
        QPixmap qPM;
        if(patient.getGender() == "M"){
            if (qPM.load(":/resources/images/man.png")){
                qLblImg->setPixmap(qPM);
            }
            else {
              qLblImg->setText(
                QString::fromLatin1("Sorry. Cannot find file 'man.png'."));
            }
        }
        else if(patient.getGender() == "F"){
            if (qPM.load(":/resources/images/woman.png")) qLblImg->setPixmap(qPM);
            else {
              qLblImg->setText(
                QString::fromLatin1("Sorry. Cannot find file 'woman.png'."));
            }
        }

        QHBoxLayout *headerLayout = new QHBoxLayout();

        QGridLayout *headerPhotoLayout = new QGridLayout();
        headerPhotoLayout->addWidget(qLblImg, 1, 1, Qt::AlignCenter);
        headerPhotoLayout->setRowStretch(1, 1);
        headerPhotoLayout->setColumnStretch(1, 1);

        headerLayout->addLayout(headerPhotoLayout, 1);

        QVBoxLayout *headerInfoLayout = new QVBoxLayout();
        QLabel *patientNameLabel = new QLabel(patient.getName());
        bold(patientNameLabel);

        QLabel *patientSurnameLabel = new QLabel(patient.getSurname());
        bold(patientSurnameLabel);

        QPushButton *goToPatientButton = new QPushButton("Show");
        goToPatientButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        QSpacerItem *spacerTwo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        QObject::connect(goToPatientButton, &QPushButton::clicked, this, &VisitView::goToPatientHandler);
        headerInfoLayout->addItem(spacer);
        headerInfoLayout->addWidget(patientNameLabel);
        headerInfoLayout->addWidget(patientSurnameLabel);
        headerInfoLayout->addWidget(goToPatientButton);
        headerInfoLayout->addItem(spacerTwo);


        headerLayout->addLayout(headerInfoLayout, 2);

        bodyLayout = new QVBoxLayout();
        QLabel *dateLabel = new QLabel(visit.getDate().toString("dd-MM-yyyy"));
        dateLabel->setAlignment(Qt::AlignCenter);
        QLabel *hospitalLabel = new QLabel();
        hospitalLabel->setAlignment(Qt::AlignCenter);
        QString hospitalText = visit.getIsHospital() ? "sent to hospital" : "sent to home";
        hospitalLabel->setText(hospitalText);
        QTextBrowser *description = new QTextBrowser();
        description->setText(visit.getDescription());
        QTextBrowser *medicines = new QTextBrowser();
        medicines->setText(visit.getMedicines());
        QPushButton *editModeButton = new QPushButton("Edit");
        QObject::connect(editModeButton, &QPushButton::clicked, this, &VisitView::editModeHandler);
        bodyLayout->addWidget(dateLabel);
        bodyLayout->addWidget(hospitalLabel);
        QLabel *descriptionLabel = new QLabel("description");
        bold(descriptionLabel);
        QLabel *medicinesLabel = new QLabel("medicines");
        bold(medicinesLabel);
        bodyLayout->addWidget(descriptionLabel);
        bodyLayout->addWidget(description);
        bodyLayout->addWidget(medicinesLabel);
        bodyLayout->addWidget(medicines);
        bodyLayout->addWidget(editModeButton);

        menu->addLayout(headerLayout, 1);
        menu->addLayout(bodyLayout, 2);

}

void VisitView::buildVisit(const Visit &visit)
{
    setVisit(visit);
    build();
}

void VisitView::launchEditMode()
{
    clean(bodyLayout);
    dateInput = new QDateEdit(visit.getDate());
    dateInput->setDisplayFormat("dd-MM-yyyy");
    isHospitalInput = new QCheckBox("sent to hospital");
    isHospitalInput->setChecked((bool)visit.getIsHospital());
    descriptionInput = new QTextEdit(visit.getDescription());
    medicinesInput = new QTextEdit(visit.getMedicines());


    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *deleteButton = new QPushButton("delete");
    QObject::connect(deleteButton,&QPushButton::clicked, this, &VisitView::deleteHandler);
    QPushButton *saveButton = new QPushButton("save");
    QObject::connect(saveButton,&QPushButton::clicked, this, &VisitView::saveHandler);
    QSpacerItem *buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addItem(buttonSpacer);
    buttonLayout->addWidget(saveButton);

    bodyLayout->addWidget(dateInput);
    bodyLayout->addWidget(isHospitalInput);
    bodyLayout->addWidget(descriptionInput);
    bodyLayout->addWidget(medicinesInput);
    bodyLayout->addLayout(buttonLayout);

}

void VisitView::goToPatientHandler(bool checked){

    emit patientClicked(visit.getPatientId());
}

void VisitView::deleteHandler(bool checked){
    db.removeVisit(visit.getId());
    clean(menu);
}

void VisitView::saveHandler(bool checked){
    visit.setDate(dateInput->date());
    visit.setIsHospital((int)isHospitalInput->isChecked());
    visit.setDescription(descriptionInput->toPlainText());
    visit.setMedicines(medicinesInput->toPlainText());
    db.updateVisit(visit);
    build();
}


void VisitView::visitClickedHandler(QListWidgetItem *item)
{
    QVariant v = item->data(Qt::UserRole);
    int id = v.value<int>();
    buildVisit(db.getVisit(id));
}
