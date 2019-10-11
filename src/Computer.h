#ifndef COMPUTER_H
#define COMPUTER_H

#include "Config.h"
#include "PointCalculate.h"
#include "ui_MainWindow.h"

using namespace std;

struct NextPos{
    unsigned int agentNum;
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
    int type;
    int removeCheck;
    int color;
    int conflictNum = 0;
};

struct Correction{//補正
    int loopTimes;
    vector<double> loop;
    double stay;
    double myTeamColorTile;
    double distance[6];
    double tile;
    double area;
};

class Computer
{
public:
    explicit Computer();
    ~Computer();
    void setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field, int num);
    void startAlgo(int AlgoNumber);

private:
    void algo(int num);
    void greedy(int loopCount, MoveData currentMoveData);
    void greedy2(int loopCount, MoveData currentMoveData, vector<vector<Tile>> currentTileData);
    void chooseBestResult();
    int outLange(int x, int y);
    void copyAgent();
    void resetCopyTile();
    int conflictMove(int x, int y, unsigned int agentNum, int angle);
    double distance(MoveData currentMoveData);
    int decodeCorrection(int num);
    void splitTurn();
    void partSelect();

    Ui::MainWindow *uiMainWindow;
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    int first = 0;

    int angle[9][2] = { // x,y
        { -1, -1},{  0, -1},{  1, -1},
        { -1,  0},{  0,  0},{  1,  0},
        { -1,  1},{  0,  1},{  1,  1}
    };

    Teams provisionalTeams;
    NextPos nextPos;
    Correction correction;
    Correction correctionSplit[7];
    vector<ProvisionalPoint> provPoint;
    MoveData moveData;
    PointCalculate* PC = nullptr;
    vector<vector<Tile>> copyTileData;
    vector<MoveData> previousMoveData;
    vector<MoveData> previousMoveData2;
    int part[7];
    int partCount = 0;
};

#endif // COMPUTER_H
