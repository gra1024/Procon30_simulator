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

    //QJson形式の配列を作成。フィールド情報にあるpointsをコピー？
    QJsonArray Field_points = QFieldfileobj.value("points").toArray();
    QJsonArray Field_color=QFieldfileobj.value("tiled").toArray();





    /*
    for(int i=0;i<20;i++)for(int j=0;j<20;j++) {
    FieldInformaitionTurn0.points[i][j]=Field_points.at(0).toDouble();
    qDebug()<<FieldInformaitionTurn0.points[i][j];
}*/

    //FieldInformaitionTurn0.points = Field_points.p
    QJsonArray TileArray = QFieldfileobj.value("tiled").toArray();
    QJsonArray teamsArray=QFieldfileobj.value("teams").toArray();
    //QJsonValue teamsArrayfirst=teamsArray.at(0);
    QJsonValue teamsArrayfirst=teamsArray.at(0);
    //qDebug()<<teamsArray;

    //qDebug()<<teamsArrayfirst;
    QJsonValue teamsArraysecode=teamsArray.at(1);
    //qDebug()<<teamsArray.at(0);

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

    QJsonArray color_line[20];
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {
     color_line[i]=Field_color.at(i).toArray();
    }
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {for(int j=0;j<FieldInformaitionTurn0.width;j++){
     FieldInformaitionTurn0.tiled[i][j]=color_line[i].at(j).toDouble();
     std::cout<<FieldInformaitionTurn0.tiled[i][j];
    }    }

    FieldInformaitionTurn0.turn= QFieldfileobj.value("turn").toDouble();


    //↑おそらくjson形式の構造体に数値が入ってる
    Myteam.teamID=QFieldfileobj.value("teamID").toDouble();



    /*QJSON形式をこちらで定義した変数に合わせて入れる(visual studioの形式を再現。行動情報)*/


    /*ファイルの読み込み エージェント(ID5)行動情報*/
    QFile ID5_Movefile("行動情報_ID5.json");
    ID5_Movefile.open(QFile::ReadOnly);
    QTextStream ID5_MovefileText (&ID5_Movefile);

    /*ID5_Movefile　から取り出した textstream をQtクラスのJSON形式に変換*/
    QJsonDocument ID5_MovefileDoc = QJsonDocument::fromJson(ID5_MovefileText.readAll().toUtf8());
    QJsonObject QID5_Movefileobj = QFieldfileDoc.object();
    QStringList QID5_Movefilekeys =QFieldfileobj.keys();

    /*ファイルの読み込み エージェント(ID6)行動情報 */
    QFile ID6_Movefile("行動情報_ID6.json");
    ID6_Movefile.open(QFile::ReadOnly);
    QTextStream ID6_MovefileText (&ID6_Movefile);

    /*ID6_Movefile　から取り出した textstream をQtクラスのJSON形式に変換*/
    QJsonDocument ID6_MovefileDoc = QJsonDocument::fromJson(ID5_MovefileText.readAll().toUtf8());
    QJsonObject QID6_Movefileobj = QFieldfileDoc.object();
    QStringList QID6_Movefilekeys =QFieldfileobj.keys();
/*
    qDebug()<<field.width;
    qDebug()<<field.height;
    qDebug()<<field.startedAtUnixTime;
    qDebug()<<field.turn;

    cout<<"width "<<field.width<<endl<<
          "height "<<field.height<<endl<<
          "startedAtUnixTime "<<field.startedAtUnixTime<<endl<<
          "turn "<<field.turn<<endl;
*/

    QByteArray data = Fieldfile.readAll();
/*
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QString jsonStr=jsonDoc.toJson(QJsonDocument::Compact);
    qDebug()<<jsonStr;
*/

Fieldfile.close();
ID5_Movefile.close();
ID6_Movefile.close();
}
