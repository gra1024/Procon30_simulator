#ifndef COMPUTER_H
#define COMPUTER_H

#include "Config.h"

#include "ui_MainWindow.h"

using namespace std;

class Computer
{
public:
    explicit Computer();
    ~Computer();
    void setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field);

    //Actions *action;
    void startAlgo(int AlgoNumber);

private:
    Ui::MainWindow *uiMainWindow;
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    Agent *agent;
    //void greedy();
    void greedy2();
    //int eightangle(int angle[8][2],int Ax,int Ay,unsigned int Anumber,int TURN);

    int angle[9][2] = { // x,y
        { -1, -1},{  0, -1},{  1, -1},
        { -1,  0},{  0,  0},{  1,  0},
        { -1,  1},{  0,  1},{  1,  1}
    };
    int result[9][2] = {}; // path or fail,point
    Teams provisionalTeams;
    int outLange(int x, int y);
    void copy();
};

#endif // COMPUTER_H
