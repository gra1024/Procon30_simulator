#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include "Config.h"

using namespace std;

namespace Ui {
class Field;
}

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

struct GameField{
    int width;  //横
    int height; //縦
    int turn;
};

class Field : public QWidget
{
    Q_OBJECT

public:
    explicit Field(QWidget *parent = nullptr);
    ~Field();
    GameField gameField;
    Tile tile;
    Agent Agent;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Field *ui;
    
};

#endif // FIELD_H
