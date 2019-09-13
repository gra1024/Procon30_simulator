#ifndef COMPUTER_H
#define COMPUTER_H

#include "Config.h"
#include "ui_MainWindow.h"

using namespace std;

class Computer
{
public:
    explicit Computer(Ui::MainWindow *uiMainWindow);
    ~Computer();
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field);
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    Actions *action;
    void startAlgo(int AlgoNumber);

private:
    Ui::MainWindow *uiMainWindow;
    void greedy();
    int eightangle(int angle[8][2],int Ax,int Ay,unsigned int Anumber,int TURN);
};

#endif // COMPUTER_H
