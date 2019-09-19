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

/* ### Network Library ### */

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QUrl>

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
#define WHITE 0

#define CONFIG_PATH_OF_FILE_INPUT_FIELD_BY_PLAYER config.value("PATH_OF_FILE_INPUT_FIELD_BY_PLAYER").toString().toStdString()
#define CONFIG_PATH_OF_FILE_INPUT_ACTIONS_1_BY_GAMEMASTER config.value("PATH_OF_FILE_INPUT_ACTIONS_1_BY_GAMEMASTER").toString().toStdString()
#define CONFIG_PATH_OF_FILE_INPUT_ACTIONS_2_BY_GAMEMASTER config.value("PATH_OF_FILE_INPUT_ACTIONS_2_BY_GAMEMASTER").toString().toStdString()
#define CONFIG_PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER config.value("PATH_OF_FILE_OUTPUT_ACTIONS_BY_PLAYER").toString().toStdString()
#define CONFIG_PATH_OF_FILE_OUTPUT_FIELD_BY_GAMEMASTER config.value("PATH_OF_FILE_OUTPUT_FIELD_BY_GAMEMASTER").toString().toStdString()
#define CONFIG_MAGNIFICATION_OF_FIELD config.value("MAGNIFICATION_OF_FIELD").toInt()

/* ### struct ### */
struct Pos{
    int agentID;
    int x;
    int y;
}; //行動情報から取り出した情報を代入する。

struct Tile{
    int point;
    int color;
};

struct Actions{
    int type;
    int dx;
    int dy;
    int apply;
};

struct Agent{
    int agentID;
    int x;
    int y;
    Actions actions;
};

struct Teams{
    int teamID;
    vector<Agent> agents;
    int tilePoint;
    int areaPoint;
};

struct Field{
    int width;  //横
    int height; //縦
    int startedAtUnixTime;
    int turn;
    int playerColor[2] = {};
    int TeamColorNumber[2]={};//[自軍のteamID][敵軍のteamID]
    int myTeam;
};

struct Network{
    QJsonObject matchReply;
    QByteArray actionData;
};

#endif // CONFIG_H
