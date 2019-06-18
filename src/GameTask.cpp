#include "GameTask.h"
#include "ui_GameTask.h"

GameTask::GameTask(int gameNumberCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameTask)
{
    this->gameNumberCount = gameNumberCount;
    ui->setupUi(this);
}

GameTask::~GameTask()
{
    delete ui;
}

void GameTask::on_pushButton_start_clicked()
{
    AF[gameNumberCount] = AnalyzeField::setup()
    //GT[gameNumberCount]->show();
    gameNumberCount++;
}
