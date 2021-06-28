#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QObject>
#include <QVector>
#include "../Model/patient.h"
#include <QtSql/QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include "../Model/visit.h"

class DatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);

    QVector<Patient> getPatients();
    Patient getPatient(int id);
    void addPatient(const Patient &patient);
    void removePatient(int id);
    void updatePatient(const Patient &patient);
    bool anyVisit(int patientId);

    QVector<Visit> getVisits();
    Visit getVisit(int id);
    Visit lastVisit(int patientId);
    void addVisit(const Visit &visit);
    void removeVisit(int id);
    void updateVisit(const Visit &visit);
    void load();



signals:
    void patientAdded(const Patient &patient);
    void patientsUpdated(QVector<Patient> patients);
    void visitAdded(const Visit &visit);
    void visitUpdated(QVector<Visit> visits);
};

#endif // DATABASECONTROLLER_H
