#ifndef GAMETASK_H
#define GAMETASK_H

#include <QWidget>

#include <QMainWindow>
#include "AnalyzeField.h"
#include "Config.h"

namespace Ui {
class GameTask;
}

class GameTask : public QWidget
{
    Q_OBJECT

public:
    explicit GameTask(int gameNumberCount, QWidget *parent = nullptr);
    ~GameTask();
    vector<vector<Tile>> tile;
    vector<vector<Agent>> agent;
    Field field;
    AnalyzeField* AF;

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_reload_clicked();

private:
    Ui::GameTask *ui;
    int gnc; //gameNumberCount
};

#endif // GAMETASK_H
