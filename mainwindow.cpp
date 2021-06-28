#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listitem.h"
#include <iostream>
#include <QDebug>
#include <QLabel>
#include <QFormLayout>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setupUi(this);
}
