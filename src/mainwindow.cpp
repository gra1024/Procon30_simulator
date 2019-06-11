#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AnalyzeField.h"
#include "PointCalculate.h"

extern QSettings config;

PointCalculate *pointCalculate;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* 得点計算動作確認用
    pointCalculate =new PointCalculate(tile,agent,field);
    pointCalculate->debug();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked(){
    AnalyzeField* AF;
    AF = new AnalyzeField(tile, agent, field);
    AF->setup();

}
