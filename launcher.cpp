#include "launcher.h"

Launcher::Launcher(const MainWindow &window) : window{window},
    patientList(window.patientList),
    visitList(window.visitList, nullptr, false),
    dbController(),
    newPatientView(window.editMenuLayout, dbController),
    patientView(window.editMenuLayout, dbController),
    newVisitView(window.editMenuLayout, dbController),
    visitView(window.editMenuLayout, dbController)
{
}

void Launcher::launch()
{


    QVector<Patient> patients = dbController.getPatients();
    for(int i=0; i<patients.count(); i++){
        patientList.insertItem(patients[i]);
    }
    QVector<Visit> visits = dbController.getVisits();
    for(int i=0; i<visits.count(); i++){
        visitList.insertItem(VisitItem(visits[i], dbController));
    }


    QObject::connect(&visitView, &VisitView::patientClicked, &patientView, [this](int id){
        patientView.buildPatient(dbController.getPatient(id));
    });

    QObject::connect(window.newPatientButton, &QPushButton::clicked,
                     &newPatientView, [&](bool checked){newPatientView.build();});

    QObject::connect(window.newVisitButton, &QPushButton::clicked, &newVisitView, [this](bool checked){
        newVisitView.build();
    });


    auto visitUpdatedHandler = [this](QVector<Visit> visits){
        visitList.cleanList();
        for(int i=0; i<visits.count(); i++){
            visitList.insertItem(VisitItem(visits[i], dbController));
        }
    };

    auto patientUpdatedHandler = [this](QVector<Patient> patients){
        patientList.cleanList();
        for(int i=0; i<patients.count(); i++){
            patientList.insertItem(patients[i]);
        }
    };

    auto goToLastVisitHandler = [this](int patientID){
        visitView.setVisit(dbController.lastVisit(patientID));
        visitView.build();
    };


    QObject::connect(&dbController, &DatabaseController::patientsUpdated, &patientList, patientUpdatedHandler);
    QObject::connect(&dbController, &DatabaseController::visitUpdated, &visitList, visitUpdatedHandler);

    QObject::connect(&patientView, &PatientView::lastVisit, &visitView, goToLastVisitHandler);

    QObject::connect(window.patientList, &QListWidget::itemClicked, &patientView, &PatientView::patientClickedHandler);
    QObject::connect(window.visitList, &QListWidget::itemClicked, &visitView, &VisitView::visitClickedHandler);

    QObject::connect(&dbController, &DatabaseController::patientAdded, &patientView, &PatientView::buildPatient);
    QObject::connect(&dbController, &DatabaseController::visitAdded, &visitView, &VisitView::buildVisit);

}
