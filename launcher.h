#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include "View/newpatientview.h"
#include "Model/patient.h"
#include "Controller/databasecontroller.h"
#include "View/listview.h"
#include <labelimage.h>
#include "View/patientview.h"
#include <QDateTime>
#include <visititem.h>
#include "View/visitview.h"
#include "View/newvisitview.h"

class Launcher
{
private:
    const MainWindow& window;
    ListView patientList;
    ListView visitList;
    DatabaseController dbController;
    NewPatientView newPatientView;
    PatientView patientView;
    NewVisitView newVisitView;
    VisitView visitView;

public:
    Launcher(const MainWindow &window);
    void launch();
};

#endif // LAUNCHER_H
