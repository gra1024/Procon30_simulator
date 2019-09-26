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
#define CONFIG_TOKEN config.value("TOKEN").toString().toStdString()
#define CONFIG_URL config.value("URL").toString()
#define CONFIG_MAGNIFICATION_OF_FIELD config.value("MAGNIFICATION_OF_FIELD").toInt()

/* ### struct ### */
/* ### 座標関係 ### */
struct Pos{
    int agentID; //各エージェントのID
    int x; //x座標
    int y; //y座標
}; //行動情報から取り出した情報を代入する。

/* ### タイル関係 ### */
struct Tile{
    int point; //タイルの得点
    int color; //タイルの色
};

/* ### 行動情報関係 ### */
struct Actions{
    int type; //行動の種類
    int dx; //行動のx方向の向き
    int dy; //行動のy方向の向き
    int apply; //行動の適応状況
};

/* ### エージェント関係 ### */
struct Agent{
    int agentID; //エージェントのID
    int x; //x座標
    int y; //y座標
    Actions actions; //行動情報
};

/* ### チーム関係 ### */
struct Teams{
    int teamID; //各チームのID
    vector<Agent> agents; //エージェント情報
    int tilePoint; //タイルポイント
    int areaPoint; //領域ポイント
};

/* ### フィールド関係 ### */
struct Field{
    int width;  //横幅
    int height; //縦幅
    int startedAtUnixTime; //試合が始まったUnix時間
    int turn; //ターン
    int playerColor[2] = {}; //[自軍の色][敵軍の色]
    int TeamColorNumber[2]={};//[自軍のteamID][敵軍のteamID]
    int myTeam; //チームの識別
};

/* ### ネットワーク関係 ### */
struct Network{
    QJsonObject matchReply;
    QByteArray actionData;
};

#endif // CONFIG_H
