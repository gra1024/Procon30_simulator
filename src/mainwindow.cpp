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
    AF->setup(&tile, teams, &field,NM->matchReply);
    AF->drow();
    PC = new PointCalculate ();
    PC->setup(&tile, teams, &field);
    PC->updatePoint();
    if(ui->checkBox_gameMaster->checkState()==0){
        C = new Computer(ui);
        C->setup(&tile, teams, &field);
    }else{
        UF = new UnficationField();
        UF->setup(&tile, teams, &field);
    }

}

void MainWindow::on_pushButton_reload_clicked(){
    if(ui->checkBox_gameMaster->checkState()==0){
        NM->get();
        AF->pushReload(NM->matchReply);
        if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
           C->startAlgo(0);
        }        
        PC->updatePoint();
        updateTeamPoints();
        AF->drow();
        AF->drowNextPosition();
        AF->encode(CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER);
        NM->post(AF->actionData);
    }else{
        UF->start();
        AF->drow();
    }
    cout << "Finish Reload" << endl;
}

void MainWindow::updateTeamPoints(){
    ui->lcdNumber_red->display(teams[0].tilePoint+teams[0].areaPoint);
    ui->lcdNumber_blue->display(teams[1].tilePoint+teams[1].areaPoint);
}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
