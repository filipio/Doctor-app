#include "databasecontroller.h"

DatabaseController::DatabaseController(QObject *parent) : QObject(parent)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Qt/projects/C++/first_app/patients.db"); // provide appropriate path here
    if(!db.open()){
        qWarning() << "error occured when opening the database " << db.lastError();
    }
}

Patient DatabaseController::getPatient(int id){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("SELECT * FROM Patients WHERE PatientID = :id");
    query.bindValue(":id", id);
    if(!query.exec()){
        qWarning() << "error occured when getting patient from db";
        throw std::logic_error("cannot get patient from db");
    }
    else{
        query.next();
        return Patient(query.value(0).toInt(),
                       query.value(1).toString(),
                       query.value(2).toString(),
                       query.value(3).toString(),
                       query.value(4).toString(),
                       query.value(5).toInt());
    }

}


QVector<Patient> DatabaseController::getPatients(){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    QVector<Patient> result;
    if(!query.exec("SELECT * FROM Patients ORDER BY PatientSurname, PatientName")){
        qWarning() << "error occured when getting patients from db";
    }
    else{
        while(query.next()){
            result.append(Patient(query.value(0).toInt(),
                                  query.value(1).toString(),
                                  query.value(2).toString(),
                                  query.value(3).toString(),
                                  query.value(4).toString(),
                                  query.value(5).toInt()));
        }
    }
    return result;
}

void DatabaseController::addPatient(const Patient &patient){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("INSERT INTO Patients (PatientName, PatientSurname, PhoneNumber, Sex, Age)"
" VALUES (:name, :surname, :phone, :gender, :age)");
    query.bindValue(":name", patient.getName());
    query.bindValue(":surname", patient.getSurname());
    query.bindValue(":phone", patient.getPhoneNumber());
    query.bindValue(":gender", patient.getGender());
    query.bindValue(":age", patient.getAge());
    if(!query.exec()){
        qWarning() << "error occured when adding data to db" << query.lastError();
    }
    else{
        Patient emitPatient(patient);
        query.exec("SELECT last_insert_rowid()");
        query.next();
        emitPatient.setId(query.value(0).toInt());
        emit patientsUpdated(getPatients());
        emit patientAdded(patient);
    }
}

void DatabaseController::removePatient(int id)
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("DELETE FROM Patients WHERE PatientID = :p_id");
    query.bindValue(":p_id", id);
    if(!query.exec()){
        qWarning() << "error occured when removing patient " << id << "from db : " << query.lastError();
    }
    else{
        emit patientsUpdated(getPatients());
        emit visitUpdated(getVisits());
    }
}

void DatabaseController::updatePatient(const Patient &patient){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("UPDATE Patients "
    "SET PatientName = :p_name, PatientSurname = :p_surname, PhoneNumber = :p_phone, Sex = :p_gender, Age = :p_age WHERE PatientID = :p_id");
    query.bindValue(":p_name", patient.getName());
    query.bindValue(":p_surname", patient.getSurname());
    query.bindValue(":p_phone", patient.getPhoneNumber());
    query.bindValue(":p_gender", patient.getGender());
    query.bindValue(":p_age", patient.getAge());
    query.bindValue(":p_id", patient.getId());
    if(!query.exec()){
        qWarning() << "error occured when updating patient with id " << patient.getId() <<" " << query.lastError();
    }
    else{
        emit patientsUpdated(getPatients());
        emit visitUpdated(getVisits());
    }

}

bool DatabaseController::anyVisit(int patientId)
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("SELECT * FROM Visits WHERE PatientID = :p_id");
    query.bindValue(":p_id", patientId);
    if(!query.exec()){
        qWarning() << "error occured when finding visits from p_id " << patientId << " " << query.lastError();
    }
    else{
        if(query.next()){
            return true;
        }
        return false;
    }
}

void DatabaseController::removeVisit(int id){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("DELETE FROM Visits WHERE VisitID = :v_id");
    query.bindValue(":v_id", id);
    if(!query.exec()){
        qWarning() << "error occured when removing visit with id " << id << query.lastError();
    }
    else{
        emit visitUpdated(getVisits());
    }
}

void DatabaseController::updateVisit(const Visit &visit){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("UPDATE Visits "
"SET date = :v_date, Description = :v_desc, Medicines = :v_med, isHospital = :v_hosp WHERE VisitID = :v_id");
    query.bindValue(":v_date", visit.getDate().toString("yyyy-MM-dd"));
    query.bindValue(":v_desc", visit.getDescription());
    query.bindValue(":v_med", visit.getMedicines());
    query.bindValue(":v_hosp", visit.getIsHospital());
    query.bindValue(":v_id", visit.getId());
    if(!query.exec()){
        qWarning() << "error occured when updating visit with id " << visit.getId() << " " << query.lastError();
    }
    else{
        emit visitUpdated(getVisits());
    }
}

Visit DatabaseController::lastVisit(int patientId)
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("SELECT VisitID FROM Visits WHERE PatientID = :p_id ORDER BY date desc LIMIT 1");
    query.bindValue(":p_id", patientId);
    if(!query.exec()){
        qWarning() << "error occured when getting last visit of patient : " << patientId << " " << query.lastError();
    }
    else{
        query.next();
        return getVisit(query.value(0).toInt());
    }
}

void DatabaseController::load()
{
    emit visitUpdated(getVisits());
    emit patientsUpdated(getPatients());
}

void DatabaseController::addVisit(const Visit &visit){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("INSERT INTO Visits (PatientID, date, Description, Medicines, isHospital)"
"VALUES (:p_id, :date, :desc, :med, :hosp)");
    query.bindValue(":p_id", visit.getPatientId());
    query.bindValue(":date", visit.getDate().toString("yyyy-MM-dd"));
    query.bindValue(":desc", visit.getDescription());
    query.bindValue(":med", visit.getMedicines());
    query.bindValue(":hosp", visit.getIsHospital());
    if(!query.exec()){
        qWarning() << "error occured when adding new visit" << query.lastError();
        emit visitUpdated(getVisits());
    }
    else{
        query.exec("SELECT last_insert_rowid()");
        query.next();
        Visit newVisit(visit);
        newVisit.setVisitId(query.value(0).toInt());
        emit visitUpdated(getVisits());
        emit visitAdded(visit);
    }
}

Visit DatabaseController::getVisit(int id){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    query.prepare("SELECT * FROM Visits WHERE VisitID = :id");
    query.bindValue(":id", id);
    if(!query.exec()){
        qWarning() << "error occured when getting visit from db " << query.lastError();
    }
    else{
        query.next();
        return Visit(query.value(0).toInt(),
                     query.value(1).toInt(),
                     query.value(2).toDate(),
                     query.value(3).toString(),
                     query.value(4).toString(),
                     query.value(5).toInt());
    }
}

QVector<Visit> DatabaseController::getVisits(){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON");
    QVector<Visit> result;
    if(!query.exec("SELECT * FROM Visits ORDER BY date desc, PatientID")){
        qWarning() << "error occured when getting visits from db " << query.lastError();
    }
    else{
        while(query.next()){

            result.append(Visit(query.value(0).toInt(),
                                query.value(1).toInt(),
                                query.value(2).toDate(),
                                query.value(3).toString(),
                                query.value(4).toString(),
                                query.value(5).toInt()));
        }
    }
    return result;
}
