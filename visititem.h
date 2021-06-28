#ifndef VISITITEM_H
#define VISITITEM_H

#include <stringabledatabaseitem.h>
#include "Model/visit.h"
#include "Controller/databasecontroller.h"
class VisitItem : public StringableDatabaseItem
{
private:
    const Visit& visit;
    QString patientSurname;
    QString patientName;

public:
    VisitItem(const Visit& visit, DatabaseController& db) : visit{visit}{
        Patient patient = db.getPatient(visit.getPatientId());
        patientSurname = patient.getSurname();
        patientName = patient.getName();
    }
    int getId() const override{
        return visit.getId();
    }

    QString toString() const override{
        return patientSurname + " " + patientName + " " + visit.toString();
    }
};

#endif // VISITITEM_H
