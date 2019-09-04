#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "AnalyzeField.h"
#include "PointCalculate.h"
#include "GameTask.h"

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

/*void MainWindow::on_startButton_clicked(){
    AnalyzeField* AF;
    AF = new AnalyzeField(tile, agent, field);
    AF->setup();
    //ui->lcdNumber_red->display(PointCalculate::getAllPoints(RED));
    //ui->lcdNumber_red->display(PointCalculate::getAllPoints(BLUE));
}*/

void MainWindow::on_pushButton_createNewGame_clicked(){
    GT[gameNumberCount] = new GameTask(gameNumberCount);
    GT[gameNumberCount]->show();
    gameNumberCount++;

}

void MainWindow::on_pushButton_close_clicked(){
    qApp->closeAllWindows();
}
