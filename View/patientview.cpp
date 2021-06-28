#include "patientview.h"

void PatientView::setPatient(const Patient &value)
{
    patient = value;
}

void PatientView::bold(QLabel *label)
{
    label->setStyleSheet("font-size : 20px; font-weight : bold");
}

PatientView::PatientView(QVBoxLayout *menu, DatabaseController &db) : EditMenuView(menu), db{db}
{

}

void PatientView::build(){
    clean(this->menu);
        LabelImage *qLblImg = new LabelImage();
        qLblImg->setFrameStyle(QFrame::Raised | QFrame::Box);
        qLblImg->setAlignment(Qt::AlignCenter);
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
        QGridLayout *grid = new QGridLayout();
        grid->addWidget(qLblImg, 1, 1, Qt::AlignCenter);
        grid->setRowStretch(1, 1);
        grid->setColumnStretch(1, 1);
        menu->addLayout(grid, 1);

        dataLayout = new QVBoxLayout();
        QLabel *patientNameLabel = new QLabel(patient.getName());
        patientNameLabel->setAlignment(Qt::AlignCenter);
        bold(patientNameLabel);
        QLabel *patientSurnameLabel = new QLabel(patient.getSurname());
        patientSurnameLabel->setAlignment(Qt::AlignCenter);
        bold(patientSurnameLabel);
        QLabel *patientPhoneLabel = new QLabel(patient.getPhoneNumber());
        patientPhoneLabel->setAlignment(Qt::AlignCenter);
        bold(patientPhoneLabel);
        QLabel *ageLabel = new QLabel("age " + QString::number(patient.getAge()));
        ageLabel->setAlignment(Qt::AlignCenter);
        bold(ageLabel);

        QPushButton *editModeButton = new QPushButton("Edit");
        QObject::connect(editModeButton, &QPushButton::clicked, this, &PatientView::editModeHandler);

        dataLayout->addWidget(patientNameLabel);
        dataLayout->addWidget(patientSurnameLabel);
        dataLayout->addWidget(ageLabel);
        dataLayout->addWidget(patientPhoneLabel);

        if(db.anyVisit(patient.getId())){
            QPushButton *lastVisitButton = new QPushButton("Last visit");
            QObject::connect(lastVisitButton, &QPushButton::clicked, this, &PatientView::lastVisitHandler);
            dataLayout->addWidget(lastVisitButton);
        }

        dataLayout->addWidget(editModeButton);
        menu->addLayout(dataLayout, 2);

}

void PatientView::launchEditMode()
{
    clean(this->dataLayout);
    QRegExpValidator *onlyCharsValidator = new QRegExpValidator(QRegExp("[A-Z a-z]*"));
    this->inputName = new QLineEdit();
    this->inputName->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputName->setText(patient.getName());
    this->inputName->setValidator(onlyCharsValidator);
    this->inputName->setMaxLength(70);

    this->inputSurname = new QLineEdit();
    this->inputSurname->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputSurname->setText(patient.getSurname());
    this->inputSurname->setValidator(onlyCharsValidator);
    this->inputSurname->setMaxLength(70);

    this->inputNumber = new QLineEdit();
    this->inputNumber->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputNumber->setInputMask("999-999-999");
    this->inputNumber->setText(patient.getPhoneNumber());

    this->inputAge = new QSpinBox();
    inputAge->setMinimum(1);
    inputAge->setMaximum(100);
    inputAge->setValue(patient.getAge());

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *deleteButton = new QPushButton("delete");
    QObject::connect(deleteButton,&QPushButton::clicked, this, &PatientView::deleteHandler);
    QPushButton *saveButton = new QPushButton("save");
    QObject::connect(saveButton,&QPushButton::clicked, this, &PatientView::saveHandler);
    QSpacerItem *buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *layoutSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addItem(buttonSpacer);
    buttonLayout->addWidget(saveButton);

    dataLayout->addWidget(new QLabel("name"));
    dataLayout->addWidget(inputName);
    dataLayout->addWidget(new QLabel("surnname"));
    dataLayout->addWidget(inputSurname);
    dataLayout->addWidget(new QLabel("number"));
    dataLayout->addWidget(inputNumber);
    dataLayout->addWidget(new QLabel("age"));
    dataLayout->addWidget(inputAge);
    dataLayout->addItem(layoutSpacer);
    menu->addLayout(buttonLayout);

}

void PatientView::buildPatient(const Patient &patient)
{
    setPatient(patient);
    build();
}


void PatientView::deleteHandler(bool checked)
{
    db.removePatient(patient.getId());
    this->clean(menu);
}

void PatientView::patientClickedHandler(QListWidgetItem *item)
{
    QVariant v = item->data(Qt::UserRole);
    int id = v.value<int>();
    buildPatient(db.getPatient(id));
}

void PatientView::saveHandler(bool checked){
    patient.setName(inputName->text());
    patient.setSurname(inputSurname->text());
    patient.setPhoneNumber(inputNumber->text());
    patient.setAge(inputAge->value());
    db.updatePatient(patient);
    build();
}

void PatientView::lastVisitHandler(bool checked)
{
    emit lastVisit(patient.getId());
}



PatientView :: ~PatientView(){
    clean(this->menu);
}
