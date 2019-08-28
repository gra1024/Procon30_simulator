#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    /*
    vector<vector<Tile>> tile = {
                                 {{2,0},{2,0},{2,0},{2,0}},
                                 {{2,0},{2,1},{2,0},{2,1}},
                                 {{2,1},{2,0},{2,1},{2,0}},
                                 {{2,0},{2,1},{2,0},{2,0}}
                                };//得点計算debug用*/
    vector<vector<Agent>> agent;

    Field field;
    //VSの再現(そのまま)
    FieldInformation FieldInformaitionTurn0;
    Team Myteam;
    Team Enemyteam;
    Agent_actions We_first_agent_actions;
    Agent_actions We_second_agent_actions;
    Agent_actions Enemy_first_agent_actions;
    Agent_actions Enemy_second_agent_actions;


private slots:
    void on_Button_Start_1_clicked();
    void on_reloadButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
