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

using namespace std;

extern QSettings config;

/* ### Define ### */
#define RED 0
#define BLUE 1
#define WHITE -1

#define CONFIG_PATH_OF_FIELD_TXT config.value("PATH_OF_FIELD_TXT").toString()
#define CONFIG_PATH_OF_AGENT_TXT config.value("PATH_OF_AGENT_TXT").toString()

/* ### struct ### */
struct Pos{
    int x;
    int y;
};

struct Tile{
    int point;
    int color;
};

struct Agent{
    int x;
    int y;
};

struct Field{
    int width;  //横
    int height; //縦
    int turn;
    int playerColor[2] = {RED,BLUE};
};

#endif // CONFIG_H
