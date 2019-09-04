#include "GameTask.h"
#include "ui_GameTask.h"

GameTask::GameTask(int gameNumberCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameTask)
{
    gnc = gameNumberCount;
    ui->setupUi(this);
    string title = "GameTask" + to_string(gnc);
    this->setWindowTitle(QString::fromStdString(title));
}

GameTask::~GameTask()
{
    delete ui;
}

void GameTask::on_pushButton_start_clicked()
{
    AF = new AnalyzeField(gnc, tile, agent, field);
    AF->setup();
}

void GameTask::on_pushButton_reload_clicked()
{
   /*AF->drowField();*/
    AF->reload(tile,agent,field);

}
