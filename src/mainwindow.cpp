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

/* ### GUIのStartボタンが押された時、試合フィールド表示 ### */
void MainWindow::on_pushButton_start_clicked(){
    NM = new NetworkManager();
    NM->setup(ui, &network);
    NM->get();
    AF = new AnalyzeField();
    AF->setup(ui, &tile, teams, &field, &network);
    AF->drow();
    PC = new PointCalculate ();
    PC->setup(&tile, teams, &field);
    PC->updatePoint();

    // PlayerかonePlayerModeの時、Cクラスを通過
    if(ui->checkBox_gameMaster->checkState() == 0 || ui->checkBox_onePlayerMode->checkState() == 2){
        C = new Computer();
        C->setup(ui, &tile, teams, &field);
        cout << "$" << endl;
    }

    // GameMasterかonePlayermodeの時、UFクラスを通過
    if((ui->checkBox_gameMaster->checkState() == 2 && ui->checkBox_practice->checkState() == 0)
            || ui->checkBox_onePlayerMode->checkState() == 2){
        UF = new UnficationField();
        UF->setup(&tile, teams, &field);
        cout << "#"<<endl;
    }

    cout << "Finish All setup" << endl;
}

/* ### GUIのReloadボタンが押された時、試合フィールド、エージェント情報更新 ### */
void MainWindow::on_pushButton_reload_clicked(){

    // PlayerかonePlayerModeの時
    if(ui->checkBox_gameMaster->checkState() == 0 || ui->checkBox_onePlayerMode->checkState() == 2){
        NM->get();
        AF->pushReload();
        if(ui->comboBox_algolithm->currentText()=="Algolithm1"){
           C->startAlgo(0);
        }        
        PC->updatePoint();
        updateTeamPoints();
        AF->drow();
        AF->drowNextPosition();
        AF->encode(CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER);
        NM->post();
        cout << "P" << endl;
    }

    // GameMasterかonePlayermodeの時
    if((ui->checkBox_gameMaster->checkState() == 2 && ui->checkBox_practice->checkState() == 0)
            || ui->checkBox_onePlayerMode->checkState() == 2){
        UF->start();
        AF->drow();
        cout << "G" << endl;
    }

    cout << "Finish Reload" << endl;
}

/* ### GUIに表示するポイントの値変更 ### */
void MainWindow::updateTeamPoints(){
    ui->lcdNumber_red->display(teams[0].tilePoint+teams[0].areaPoint);
    ui->lcdNumber_blue->display(teams[1].tilePoint+teams[1].areaPoint);
}

/* ### GUIのウィンドウを閉じる ### */
void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
