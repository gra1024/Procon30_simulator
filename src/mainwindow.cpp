#include "MainWindow.h"
#include "ui_mainwindow.h"

//#include "AnalyzeField.h"
//#include "PointCalculate.h"

extern QSettings config;

//PointCalculate *pointCalculate;

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

void MainWindow::on_pushButton_createNewGame_clicked(){
    AF = new AnalyzeField();
    AF->setup();
}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
