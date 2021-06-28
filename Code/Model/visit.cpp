#include "visit.h"

void Visit::setVisitId(int value)
{
    visitId = value;
}

int Visit::getPatientId() const
{
    return patientId;
}

void Visit::setPatientId(int value)
{
    patientId = value;
}

QDate Visit::getDate() const
{
    return date;
}

void Visit::setDate(const QDate &value)
{
    date = value;
}

QString Visit::getDescription() const
{
    return description;
}

void Visit::setDescription(const QString &value)
{
    description = value;
}

QString Visit::getMedicines() const
{
    return medicines;
}

void Visit::setMedicines(const QString &value)
{
    medicines = value;
}

int Visit::getIsHospital() const
{
    return isHospital;
}

void Visit::setIsHospital(int value)
{
    isHospital = value;
}

