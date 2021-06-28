QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/Controller/databasecontroller.cpp \
    $$PWD/View/editmenuview.cpp \
    idatabaseitem.cpp \
    ieditablegui.cpp \
    istringable.cpp \
    labelimage.cpp \
    $$PWD/View/listview.cpp \
    launcher.cpp \
    main.cpp \
    mainwindow.cpp \
    $$PWD/View/newpatientview.cpp \
    $$PWD/View/newvisitview.cpp \
    $$PWD/View/patientview.cpp \
    stringabledatabaseitem.cpp \
    $$PWD/Model/visit.cpp \
    $$PWD/View/visitview.cpp

HEADERS += \
    $$PWD/Controller/databasecontroller.h \
    $$PWD/View/editmenuview.h \
    idatabaseitem.h \
    ieditablegui.h \
    istringable.h \
    labelimage.h \
    $$PWD/View/listview.h \
    launcher.h \
    mainwindow.h \
    $$PWD/View/newpatientview.h \
    $$PWD/View/newvisitview.h \
    $$PWD/Model/patient.h \
    $$PWD/View/patientview.h \
    stringabledatabaseitem.h \
    $$PWD/Model/visit.h \
    visititem.h \
    $$PWD/View/visitview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    README.txt
