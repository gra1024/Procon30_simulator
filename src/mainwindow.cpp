#include "MainWindow.h"
#include "ui_MainWindow.h"

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

void MainWindow::on_pushButton_start_clicked(){
    AF = new AnalyzeField(ui);
    AF->setup(&tile, teams, &field);
    C = new Computer(ui);
    C->setup(&tile, teams, &field);
    if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
           C->startAlgo(1);
       }
    AF->drowNextPosition();
}

void MainWindow::on_pushButton_reload_clicked(){
    AF->pushReload();
    manager = new NetworkManager();
    manager->get();
    if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
           C->startAlgo(1);
       }
}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
