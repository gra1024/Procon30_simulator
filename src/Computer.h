#ifndef COMPUTER_H
#define COMPUTER_H

#include "Config.h"
#include "PointCalculate.h"
#include "ui_MainWindow.h"

using namespace std;

struct NextPos{
    unsigned int agentNum;
    int maxLoop = 3;
    int myTeam;
};

struct ProvisionalPoint{
    double totalPoint;//そのルートの評価
    int moveAngle;
};

struct MoveData{
    int x;
    int y;
    double accumulationPoint = 0;
    int moveAngle;
    int removeCheck;
};

struct Correction{//補正
    double loop[3] = {0.6, 0.8, 1.0};
    double stay = -5;
    double myTeamColorTile = 0.1;
    double agentDistance=5;
    double agentDistanceCorrection=0.8;
};

class Computer
{
public:
    explicit Computer();
    ~Computer();
    void setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field);
    void startAlgo(int AlgoNumber);

private:
    void algo(int num);
    void greedy(int loopCount, MoveData currentMoveData);
    void greedy2(int loopCount, MoveData currentMoveData, vector<vector<Tile>> currentTileData);
    void chooseBestResult();
    int outLange(int x, int y);
    void copyAgent();
    void resetCopyTile();
    int distance(MoveData currentMoveData);

    Ui::MainWindow *uiMainWindow;
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;

    int angle[9][2] = { // x,y
        { -1, -1},{  0, -1},{  1, -1},
        { -1,  0},{  0,  0},{  1,  0},
        { -1,  1},{  0,  1},{  1,  1}
    };

    Teams provisionalTeams;
    NextPos nextPos;
    Correction correction;
    vector<ProvisionalPoint> provPoint;
    MoveData moveData;
    PointCalculate* PC = nullptr;
    vector<vector<Tile>> copyTileData;

};

#endif // COMPUTER_H
