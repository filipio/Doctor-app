#ifndef PATIENT_H
#define PATIENT_H
#include "QString"
#include <idatabaseitem.h>
#include <stringabledatabaseitem.h>
class Patient : public StringableDatabaseItem{
private:
    int id;
    int age;
    QString name;
    QString surname;
    QString phoneNumber;
    QString gender;

public:

    Patient(QString name, QString surname, QString phoneNumber, QString gender, int age) :
       age{age}, name{name}, surname{surname}, phoneNumber{phoneNumber}, gender{gender}{}

    Patient(int id, QString name, QString surname, QString phoneNumber, QString gender, int age) :
        Patient(name, surname, phoneNumber, gender, age){
        this->id = id;
    }

    Patient() = default;
    ~Patient(){}

    int getId() const override{
        return id;
    }

    QString toString() const override{
        return surname + " " + name;
    }

    int getAge() const
    {
        return age;
    }

    void setAge(int value)
    {
        age = value;
    }

    QString getGender() const{
        return gender;
    }

    QString getName() const{
        return name;
    }

    QString getSurname() const{
        return surname;
    }

    QString getPhoneNumber() const{
        return phoneNumber;
    }

    void setGender(QString gender){
        this->gender = gender;
    }



    void setId(int id){
        this->id = id;
    }

    void setName(QString name){
        this->name = name;
    }

    void setSurname(QString surname){
        this->surname = surname;
    }

    void setPhoneNumber(QString phoneNumber){
        this->phoneNumber = phoneNumber;
    }
};

#endif // PATIENT_H
