#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AnalyzeField.h"
#include "PointCalculate.h"

extern QSettings config;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
