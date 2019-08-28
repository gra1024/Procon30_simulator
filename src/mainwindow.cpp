#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "AnalyzeField.h"
#include "PointCalculate.h"

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

void MainWindow::on_Button_Start_1_clicked(){
    AnalyzeField* AF;
    AF = new AnalyzeField(tile, agent, field);
    AF->setup();
    //ui->lcdNumber_red->display(PointCalculate::getAllPoints(RED));
    //ui->lcdNumber_red->display(PointCalculate::getAllPoints(BLUE));
}

void MainWindow::on_reloadButton_clicked(){

}

void MainWindow::on_pushButton_clicked()
{
    /*ファイルの読み込み フィールド情報 */
    QFile Fieldfile("フィールド情報_turn0.json");
    Fieldfile.open(QFile::ReadOnly);
    QTextStream FieldfileText (&Fieldfile);

    /*Fieldfile から取り出した textstream をQtクラスのJSON形式に変換 */
    QJsonDocument QFieldfileDoc = QJsonDocument::fromJson(FieldfileText.readAll().toUtf8());
    QJsonObject QFieldfileobj = QFieldfileDoc.object();
    QStringList QFieldfilekeys =QFieldfileobj.keys();

    //QJson形式の配列を作成。ファイル内にある配列を作成(一番大きい)
    QJsonArray Field_points = QFieldfileobj.value("points").toArray();
    QJsonArray Field_color=QFieldfileobj.value("tiled").toArray();
    QJsonArray Field_teams=QFieldfileobj.value("teams").toArray();

    /*QJSON形式をこちらで定義した変数に合わせて入れる(先輩たちが用意した変数)*/
    field.width= QFieldfileobj.value("width").toDouble();
    field.height= QFieldfileobj.value("height").toDouble();
    field.startedAtUnixTime= QFieldfileobj.value("startedAtUnixTime").toDouble();
    field.turn= QFieldfileobj.value("turn").toDouble();

    /*QJSON形式をこちらで定義した変数に合わせて入れる(visual studioの形式を再現。フィールド情報)*/
    FieldInformaitionTurn0.width= QFieldfileobj.value("width").toDouble();
    FieldInformaitionTurn0.height= QFieldfileobj.value("height").toDouble();
    QJsonArray points_line[20];
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {
     points_line[i]=Field_points.at(i).toArray();
    }
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {for(int j=0;j<FieldInformaitionTurn0.width;j++){
     FieldInformaitionTurn0.points[i][j]=points_line[i].at(j).toDouble();
     //std::cout<<FieldInformaitionTurn0.points[i][j];
    }    }
    FieldInformaitionTurn0.startedAtunixTime= QFieldfileobj.value("height").toDouble();
    FieldInformaitionTurn0.turn= QFieldfileobj.value("turn").toDouble();
    QJsonArray color_line[20];
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {
     color_line[i]=Field_color.at(i).toArray();
    }
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {for(int j=0;j<FieldInformaitionTurn0.width;j++){
     FieldInformaitionTurn0.tiled[i][j]=color_line[i].at(j).toDouble();
     //std::cout<<FieldInformaitionTurn0.tiled[i][j];
    }    }
    Myteam.teamID= Field_teams.at(0).toObject().value("teamID").toDouble();
    //qDebug()<<Field_teams.at(0).toObject().value("teamID").toDouble();
    QJsonArray our_team_agents=Field_teams.at(0).toObject().value("agents").toArray();
    QJsonObject our_agents[8];
    for (int i=0;i<our_team_agents.size();i++) {
     our_agents[i]=our_team_agents.at(i).toObject();
     //qDebug()<<our_agents[i];
     Myteam.first_agents.agentID=our_agents[i].value("agentID").toDouble();
     Myteam.first_agents.x=our_agents[i].value("x").toDouble();
     Myteam.first_agents.y=our_agents[i].value("y").toDouble();
    }
    Myteam.tilePoint=Field_teams.at(0).toObject().value("tilePoint").toDouble();
    Myteam.areaPoint=Field_teams.at(0).toObject().value("areaPoint").toDouble();

    Enemyteam.teamID= Field_teams.at(1).toObject().value("teamID").toDouble();
    QJsonArray enemy_team_agents=Field_teams.at(1).toObject().value("agents").toArray();
    QJsonObject enemy_agents[8];
    for (int i=0;i<enemy_team_agents.size();i++) {
     enemy_agents[i]=enemy_team_agents.at(i).toObject();
     //qDebug()<<enemy_agents[i];
     Enemyteam.first_agents.agentID=our_agents[i].value("agentID").toDouble();
     Enemyteam.first_agents.x=our_agents[i].value("x").toDouble();
     Enemyteam.first_agents.y=our_agents[i].value("y").toDouble();
    }
    Enemyteam.tilePoint=Field_teams.at(0).toObject().value("tilePoint").toDouble();
    Enemyteam.areaPoint=Field_teams.at(0).toObject().value("areaPoint").toDouble();

    //↑おそらくjson形式の構造体に数値が入ってる
    Myteam.teamID=QFieldfileobj.value("teamID").toDouble();



    /*QJSON形式をこちらで定義した変数に合わせて入れる(visual studioの形式を再現。行動情報)*/

    /*ファイルの読み込み 行動情報(ID5) */
    QFile MoveInformationID5("行動情報_ID5.json");
    MoveInformationID5.open(QFile::ReadOnly);
    QTextStream MoveInformationTextID5 (&Fieldfile);

    /*MoveInformationID5 から取り出した textstream をQtクラスのJSON形式に変換 */
    QJsonDocument QMoveInformationID5Doc = QJsonDocument::fromJson(MoveInformationTextID5.readAll().toUtf8());
    QJsonObject QMoveInformationID5obj = QMoveInformationID5Doc.object();
    QStringList QMoveInformationID5keys =QMoveInformationID5obj.keys();

    /*配列actionsを作成*/
    QJsonArray actions_array = QMoveInformationID5obj.value("actions").toArray();

    We_first_agent_actions.agentID= actions_array.at(0).toObject().value("teamID").toDouble();
    QJsonArray We_first_agent_actions_Array=actions_array.at(0).toObject().value("actions").toArray();
    QJsonObject We_first_agent[8];
    for (int i=0;i<We_first_agent_actions_Array.size();i++) {
     We_first_agent[i]=We_first_agent_actions_Array.at(i).toObject();
     //qDebug()<<our_agents[i];
     //We_first_agent_actions.type=our_agents[i].value("type").toString();
     //actionsのtypeができてない！
     qDebug()<<our_agents[i].value("type").toString();
     We_first_agent_actions.dx=our_agents[i].value("dx").toDouble();
     We_first_agent_actions.dy=our_agents[i].value("dy").toDouble();
    }

    /*ファイルの読み込み 行動情報(ID6) */
    QFile MoveInformationID6("行動情報_ID6.json");
    MoveInformationID6.open(QFile::ReadOnly);
    QTextStream MoveInformationTextID6 (&Fieldfile);

    /*MoveInformationID6 から取り出した textstream をQtクラスのJSON形式に変換 */
    QJsonDocument QMoveInformationID6Doc = QJsonDocument::fromJson(MoveInformationTextID6.readAll().toUtf8());
    QJsonObject QMoveInformationID6obj = QMoveInformationID6Doc.object();
    QStringList QMoveInformationID6keys =QMoveInformationID6obj.keys();

    /*配列actionsを作成*/
    QJsonArray actions_arrayID6 = QMoveInformationID6obj.value("actions").toArray();

    We_second_agent_actions.agentID= actions_arrayID6.at(0).toObject().value("teamID").toDouble();
    QJsonArray We_second_agent_actions_Array=actions_arrayID6.at(0).toObject().value("actions").toArray();
    QJsonObject We_second_agent[8];
    for (int i=0;i<We_second_agent_actions_Array.size();i++) {
     We_first_agent[i]=We_second_agent_actions_Array.at(i).toObject();
     //qDebug()<<our_agents[i];
     //We_first_agent_actions.type=our_agents[i].value("type").toString();
     //actionsのtypeができてない！
     qDebug()<<our_agents[i].value("type").toString();
     We_second_agent_actions.dx=our_agents[i].value("dx").toDouble();
     We_second_agent_actions.dy=our_agents[i].value("dy").toDouble();
    }


Fieldfile.close();
MoveInformationID5.close();
MoveInformationID6.close();

}
