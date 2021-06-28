#ifndef VISIT_H
#define VISIT_H

#include <stringabledatabaseitem.h>
#include <QDateTime>
class Visit : public StringableDatabaseItem
{
private:
    int visitId;
    int patientId;
    QDate date;
    QString description;
    QString medicines;
    int isHospital;




public:

    Visit(int patientId, QDate date, QString description, QString medicines, int isHospital):
        patientId{patientId}, date{date}, description{description}, medicines{medicines},
        isHospital{isHospital}{}

    Visit(int visitId, int patientId, QDate date, QString description, QString medicines, int isHospital):
        Visit(patientId, date, description, medicines, isHospital){
        this->visitId = visitId;
    }

    Visit(const Visit& visit) = default;
    Visit() = default;


    int getId() const override{
        return visitId;
    }

    QString toString() const override{
        return date.toString("dd-MM-yyyy");
    }


    void setVisitId(int value);

    int getPatientId() const;

    void setPatientId(int value);

    QDate getDate() const;

    void setDate(const QDate &value);

    QString getDescription() const;

    void setDescription(const QString &value);

    QString getMedicines() const;

    void setMedicines(const QString &value);

    int getIsHospital() const;

    void setIsHospital(int value);
};

#endif // VISIT_H
