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
    unsigned int turn;
    int playerColor[2] = {RED,BLUE};
};

#endif // CONFIG_H
