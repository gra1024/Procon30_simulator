#include "MainWindow.h"
#include "ui_MainWindow.h"

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

/* ### GUIのStartボタンが押された時、試合フィールド表示 ### */
void MainWindow::on_pushButton_start_clicked(){
    NM = new NetworkManager();
    NM->setup(ui, &network);
    NM->get();

    //　Player only -> player Mode (use AF1,C1)
    //　GameMaster only -> GameMaster Mode (use AF3,UF)
    //　Player & GM -> all Mode (use AF1~3,C1~2,UF)
    //　all not check -> performance (use AF1,C1)
    //　Aを用いたらPCも用いる
    //　後で変更したいところ

    // player Mode or performance
    if((ui->checkBox_player->checkState() == 2 && ui->checkBox_gameMaster->checkState() == 0)
            || (ui->checkBox_player->checkState() == 0 && ui->checkBox_gameMaster->checkState() == 0)){
        AF = new AnalyzeField(1);
        AF->setup(ui, &tile, teams, &field, &network);
        PC = new PointCalculate ();
        PC->setup(&tile, teams, &field);
        C = new Computer();
        C->setup(ui, &tile, teams, &field, selectAlgolithm(1));
        AF->drow();
        PC->updatePoint();
        updateTeamPoints(1);
        qDebug() << "setup PlayerMode";
    }

    // GameMasterMode
    if(ui->checkBox_player->checkState() == 0 && ui->checkBox_gameMaster->checkState() == 2){
        AF3 = new AnalyzeField(3);
        AF3->setup(ui, &tile3, teams3, &field3, &network);
        PC3 = new PointCalculate ();
        PC3->setup(&tile3, teams3, &field3);
        UF = new UnficationField();
        UF->setup(&tile3, teams3, &field3);

        AF3->drow();
        PC3->updatePoint();
        updateTeamPoints(3);
        qDebug() << "setup GameMasterMode";
    }

    // AllMode
    if(ui->checkBox_player->checkState() == 2 && ui->checkBox_gameMaster->checkState() == 2){
        AF = new AnalyzeField(1);
        AF->setup(ui, &tile, teams, &field, &network);
        PC = new PointCalculate ();
        PC->setup(&tile, teams, &field);
        C = new Computer();
        C->setup(ui, &tile, teams, &field, selectAlgolithm(1));

        AF2 = new AnalyzeField(2);
        AF2->setup(ui, &tile2, teams2, &field2, &network);
        AF2->inversionForSecondPlayer();
        PC2 = new PointCalculate ();
        PC2->setup(&tile2, teams2, &field2);
        C2 = new Computer();
        C2->setup(ui, &tile2, teams2, &field2, selectAlgolithm(2));

        AF3 = new AnalyzeField(3);
        AF3->setup(ui, &tile3, teams3, &field3, &network);
        PC3 = new PointCalculate ();
        PC3->setup(&tile3, teams3, &field3);
        UF = new UnficationField();
        UF->setup(&tile3, teams3, &field3);

        AF->drow();
        AF2->drow();
        AF3->drow();
        PC->updatePoint();
        PC2->updatePoint();
        PC3->updatePoint();
        updateTeamPoints(3);
        qDebug() << "setup AllMode";
        if(ui->checkBox_autoReload->checkState() == 2)autoReload();
    }

}

/* ### GUIのReloadボタンが押された時、試合フィールド、エージェント情報更新 ### */
void MainWindow::on_pushButton_reload_clicked(){
    //　Player only -> player Mode (use AF1,C1)
    //　GameMaster only -> GameMaster Mode (use AF3,UF)
    //　Player & GM -> all Mode (use AF1~3,C1~2,UF)
    //　all not check -> 	performance (use AF1,C1)
    //　Aを用いたらPCも用いる
    //　後で変更したいところ

    // player Mode or performance
    if((ui->checkBox_player->checkState() == 2 && ui->checkBox_gameMaster->checkState() == 0)
            || (ui->checkBox_player->checkState() == 0 && ui->checkBox_gameMaster->checkState() == 0)){
        NM->get();
        AF->pushReload();
        PC->updatePoint();
        C->startAlgo(selectAlgolithm(1));
        PC->updatePoint();
        AF->encode(CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER);

        AF->drow();
        AF->drowNextPosition();
        updateTeamPoints(1);

        NM->post();
    }

    // GameMasterMode
    if(ui->checkBox_player->checkState() == 0 && ui->checkBox_gameMaster->checkState() == 2){
        UF->start();
        PC3->updatePoint();

        AF3->drow();
        updateTeamPoints(3);
    }

    // AllMode
    if(ui->checkBox_player->checkState() == 2 && ui->checkBox_gameMaster->checkState() == 2){
        AF->pushReload();
        PC->updatePoint();
        C->startAlgo(selectAlgolithm(1));
        PC->updatePoint();
        AF->encode(CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER);

        AF2->pushReload();
        PC2->updatePoint();
        C2->startAlgo(selectAlgolithm(2));
        PC2->updatePoint();
        AF2->encode(CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER2);

        UF->start();
        PC3->updatePoint();

        AF->drow();
        AF->drowNextPosition();
        AF2->drow();
        AF2->drowNextPosition();
        AF3->drow();
        updateTeamPoints(3);
    }
    qDebug() << "Finish Reload " << field.turn;
}

void MainWindow::on_pushButton_setField_clicked(){
    QString currentField = QString("%1%2%3").arg("..//data//gamedata//").arg(ui->comboBox_selectField->currentText()).arg(".json");
    QFile::remove("..//data//Field.json");
    QFile::copy(currentField,"..//data//Field.json");
    cout<<"setField>>"<<currentField.toStdString()<<endl;
    cout<<"Please set teamID>>1 or 2"<<endl;
}

/* ### GUIに表示するポイントの値変更 ### */
void MainWindow::updateTeamPoints(int num){
    if(num == 1){
        ui->lcdNumber_red->display(teams[0].tilePoint+teams[0].areaPoint);
        ui->lcdNumber_red_2->display(teams[0].tilePoint);
        ui->lcdNumber_red_3->display(teams[0].areaPoint);
        ui->lcdNumber_blue->display(teams[1].tilePoint+teams[1].areaPoint);
        ui->lcdNumber_blue_2->display(teams[1].tilePoint);
        ui->lcdNumber_blue_3->display(teams[1].areaPoint);
        ui->lcdNumber_turn->display(field.turn);
    }else if(num == 3){
        ui->lcdNumber_red->display(teams3[0].tilePoint+teams3[0].areaPoint);
        ui->lcdNumber_red_2->display(teams3[0].tilePoint);
        ui->lcdNumber_red_3->display(teams3[0].areaPoint);
        ui->lcdNumber_blue->display(teams3[1].tilePoint+teams3[1].areaPoint);
        ui->lcdNumber_blue_2->display(teams3[1].tilePoint);
        ui->lcdNumber_blue_3->display(teams3[1].areaPoint);
        if(ui->spinBox_maxTurn->value()<field3.turn){
            ui->lcdNumber_turn->setStyleSheet("background-color:green; color:red;");
        }
        ui->lcdNumber_turn->display(field3.turn);
    }
}

/* ### アルゴリズムの選択 ### */
int MainWindow::selectAlgolithm(int num){
    if(num == 1){
        if (ui->comboBox_algolithm->currentText()=="Greedy-1_Basic") return 1;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_A-1") return 2;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_A-2") return 3;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_A-3") return 4;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_A-4") return 5;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_B-1") return 6;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_B-2") return 7;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_B-3") return 8;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_C-1") return 9;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_C-2") return 10;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_D-1") return 11;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_D-2") return 12;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_E-1") return 13;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_E-2") return 14;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_F-1") return 15;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_F-2") return 16;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_Basic") return 17;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_A-1") return 18;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_A-2") return 19;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_A-3") return 20;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_A-4") return 21;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_B-1") return 22;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_B-2") return 23;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_B-3") return 24;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_C-1") return 25;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_C-2") return 26;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_D-1") return 27;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_D-2") return 28;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_E-1") return 29;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_E-2") return 30;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_F-1") return 31;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_F-2") return 32;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-1_test") return 33;
        else if (ui->comboBox_algolithm->currentText()=="Greedy-2_test") return 34;
    }else if(num == 2){
        if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_Basic") return 1;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_A-1") return 2;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_A-2") return 3;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_A-3") return 4;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_A-4") return 5;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_B-1") return 6;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_B-2") return 7;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_B-3") return 8;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_C-1") return 9;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_C-2") return 10;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_D-1") return 11;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_D-2") return 12;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_E-1") return 13;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_E-2") return 14;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_F-1") return 15;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_F-2") return 16;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_Basic") return 17;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_A-1") return 18;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_A-2") return 19;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_A-3") return 20;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_A-4") return 21;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_B-1") return 22;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_B-2") return 23;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_B-3") return 24;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_C-1") return 25;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_C-2") return 26;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_D-1") return 27;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_D-2") return 28;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_E-1") return 29;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_E-2") return 30;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_F-1") return 31;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_F-2") return 32;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-1_test") return 33;
        else if (ui->comboBox_algolithm_2->currentText()=="Greedy-2_test") return 34;
    }
    return 0;
}

/* ### 自動リロード ### */
void MainWindow::autoReload(){
    for(int i=0;i<ui->spinBox_maxTurn->value();i++)on_pushButton_reload_clicked();
}

/* ### GUIのウィンドウを閉じる ### */
void MainWindow::on_pushButton_close_clicked(){
    QFile::remove("..//data//Field.json");
    QFile::copy("..//data//FieldInput.json","..//data//Field.json");
    qApp->closeAllWindows();
}
