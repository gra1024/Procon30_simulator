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
    QFile file("フィールド情報_turn0.json");
    file.open(QFile::ReadOnly);
    QTextStream in (&file);

    QByteArray data = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QString jsonStr=jsonDoc.toJson(QJsonDocument::Compact);
    qDebug()<<jsonStr;

file.close();
}
