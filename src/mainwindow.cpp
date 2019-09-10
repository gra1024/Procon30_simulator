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
    C->setup(&tile, teams, &field, &action);    
}

void MainWindow::on_pushButton_reload_clicked(){
    AF->pushReload();
    manager = new NetworkManager();
    manager->get();
    C->startAlgo(AlgoNumber);
}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
