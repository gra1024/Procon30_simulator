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
    NM = new NetworkManager(ui);
    NM->get();
    AF->setup(&tile, teams, &field,NM->matchReply);
    C = new Computer(ui);
    C->setup(&tile, teams, &field, &action);    
}

void MainWindow::on_pushButton_reload_clicked(){
    NM = new NetworkManager(ui);
    NM->get();
    AF->pushReload(NM->matchReply);
    if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
        C->startAlgo(0);
    }
    //debug
    int type[2] = {1,1};
    int dx[2] = {1,1};
    int dy[2] = {1,-1};
    AF->encode(type,dx,dy);
    NM->post(AF->actionData);

}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
