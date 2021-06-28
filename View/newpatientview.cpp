#include "newpatientview.h"

NewPatientView::NewPatientView(QVBoxLayout *menu, DatabaseController &db)
    : EditMenuView(menu), db{db}{
}

void NewPatientView::build(){
    this->clean(this->menu);
    QFormLayout *form = new QFormLayout();
    QRegExpValidator *onlyCharsValidator = new QRegExpValidator(QRegExp("[A-Z a-z]*"));
    this->inputName = new QLineEdit();
    this->inputName->setValidator(onlyCharsValidator);
    this->inputName->setMaxLength(70);
    this->inputName->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputName->setPlaceholderText("Antek");

    this->inputSurname = new QLineEdit();
    this->inputSurname->setValidator(onlyCharsValidator);
    this->inputSurname->setMaxLength(70);
    this->inputSurname->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputSurname->setPlaceholderText("Antkowski");

    this->inputNumber = new QLineEdit();
    this->inputNumber->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    this->inputNumber->setInputMask("999999999");
    this->inputNumber->setPlaceholderText("222-999-777");

    this->inputAge = new QSpinBox();
    inputAge->setMinimum(1);
    inputAge->setMaximum(100);
    inputAge->setValue(18);

    this->inputGender = new QComboBox();
    inputGender->addItem("M");
    inputGender->addItem("F");

    form->addRow("name", inputName);
    form->addRow("surname", inputSurname);
    form->addRow("age", inputAge);
    form->addRow("number", inputNumber);
    form->addRow("gender", inputGender);

    QPushButton *submit = new QPushButton("submit");
    menu->addLayout(form);
    menu->addWidget(submit);
    QObject::connect(this->inputNumber, &QLineEdit::textChanged, this, &NewPatientView::handleNumberEntered);
    QObject::connect(submit, &QPushButton::clicked, this, &NewPatientView::handleSubmit);
}

NewPatientView:: ~NewPatientView(){
    this->clean(this->menu);
}

void NewPatientView::handleSubmit(bool checked){
    QString name = inputName->text();
    QString surname = inputSurname->text();
    QString phone = inputNumber->text();
    QString patientGender = inputGender->currentText();
    int age = inputAge->value();
    Patient patient(name, surname, phone, patientGender, age);
    db.addPatient(patient);
}

void NewPatientView::handleNumberEntered(){
    this->inputNumber->setInputMask("999-999-999");
    this->inputNumber->cursorForward(false);
    QObject::disconnect(this->inputNumber, &QLineEdit::textChanged, this, &NewPatientView::handleNumberEntered);
}
