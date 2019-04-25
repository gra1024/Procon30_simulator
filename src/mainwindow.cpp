#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AnalyzeField.h"
#include "PointCalculate.h"

extern QSettings config;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AnalyzeField* AF;
    AF = new AnalyzeField(tile, agent, field);
    AF->setupField();
}

MainWindow::~MainWindow()
{
    delete ui;
}
