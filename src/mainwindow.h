#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <GameTask.h>
#include "Config.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<vector<Tile>> tile;
    vector<vector<Agent>> agent;
    Field field;
    GameTask* GT[3];

private slots:
    void on_pushButton_createNewGame_clicked();
    void on_pushButton_close_clicked();

private:
    Ui::MainWindow *ui;
    int gameNumberCount = 1;

};

#endif // MAINWINDOW_H
