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
    NM = new NetworkManager(ui);
    NM->get();
    AF = new AnalyzeField(ui);
    AF->setup(&tile, teams, &field);
    AF->drow();
    PC = new PointCalculate ();
    PC->setup(&tile, teams, &field);
    PC->updatePoint();
    
    cout << "Point1 " << teams[0].tilePoint <<" "<< teams[0].areaPoint << endl;
    cout << "Point2 " << teams[1].tilePoint <<" "<< teams[1].areaPoint << endl;
    if(ui->checkBox_practice->checkState()==0){
        C = new Computer(ui);
        C->setup(&tile, teams, &field);
    }else{
        UF = new UnficationField();
        UF->setup(&tile, teams, &field);
    }

}

void MainWindow::on_pushButton_reload_clicked(){
    if(ui->checkBox_practice->checkState()==0){
        NM->get();
        NM->post();
        AF->pushReload();
        AF->drow();
        if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
           C->startAlgo(0);
        }
    }else{
        UF->start();
        AF->drow();
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
