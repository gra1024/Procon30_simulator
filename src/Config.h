#ifndef CONFIG_H
#define CONFIG_H

/* ### C++ Standard Library ### */
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <exception>
#include <stdlib.h>
#include <sstream>
#include <iterator>


/* ### Qt Library ### */
#include <QFile>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QTextStream>
#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QDir>

/* ### JSON reader ### */
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QDebug>
#include <QDate>
#include <QIODevice>

using namespace std;

extern QSettings config;

/* ### Define ### */
#define RED 0
#define BLUE 1
#define WHITE -1

#define CONFIG_PATH_OF_FIELD_TXT config.value("PATH_OF_FIELD_TXT").toString()
#define CONFIG_PATH_OF_AGENT_TXT config.value("PATH_OF_AGENT_TXT").toString()
#define CONFIG_MAGNIFICATION_OF_FIELD config.value("MAGNIFICATION_OF_FIELD").toInt()

/* ### struct ### */
struct Pos{
    unsigned int x;
    unsigned int y;
};

struct Tile{

    //unsigned int tiled[20][20];  teamidによる座標の色識別？


    int point;
    int color;
};

struct Agent{
    unsigned int x;
    unsigned int y;
};

struct Field{
    unsigned int width;  //横
    unsigned int height; //縦
    unsigned int turn; //経過ターン

    unsigned int startedAtUnixTime; //謎



    int playerColor[2] = {RED,BLUE};
};


//JSONファイルからそのまま
//フィールド情報_turn0.json
struct FieldInformation{
    unsigned int width;  //横
    unsigned int height; //縦

    unsigned int points[20][20];
    unsigned int startedAtunixTime;

    unsigned int turn;
    unsigned int tiled[20][20];
};
struct Agents{
    unsigned int agentID  ;
    unsigned int x;
    unsigned int y;
};
struct Team{
    unsigned int teamID;

    struct Agents first_agents;
    struct Agents second_agents;

    unsigned int tilePoint;
    unsigned int areaPoint;
};

//構造体を二個宣言すればいいため省略
/*
struct Teams{
    struct Team myteam;
    struct Team enemyteam;
};*/

struct Actions{};

//行動情報_ID5.json
struct Agent_actions{
    unsigned int agentID;
    unsigned char type[10];
    unsigned int dx;
    unsigned int dy;
};

//構造体を二個宣言すればいいため省略
/*
struct actions{
    struct Agent_actions firstagents;
    struct Agent_actions secondagents;
}
*/



#endif // CONFIG_H
