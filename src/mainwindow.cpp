#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Field.h"

extern QSettings config;

extern Field *game;

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

void MainWindow::on_pushButton_clicked()
{
    game = new Field();
}

void MainWindow::on_pushButton_2_clicked()
{
    delete game;
}
