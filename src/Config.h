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

/* ### struct ### */
struct Pos{
    int x;
    int y;
};

struct Tile{
    int x;
    int y;
    int point;
    int color;
};

struct Agent{
    int x;
    int y;
    int color;
    int number;
};

struct Field{
    int width;  //横
    int height; //縦
    int turn;
};

#endif // CONFIG_H
