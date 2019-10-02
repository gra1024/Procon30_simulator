#ifndef ANALYZEFIELD_H
#define ANALYZEFIELD_H

#include <QWidget>
#include "Config.h"

#include "ui_MainWindow.h"

using namespace std;

namespace Ui {
class AnalyzeField;
}

class AnalyzeField : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeField(int uiNum, QWidget *parent = nullptr);
    ~AnalyzeField();
    void setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field, Network *network);
    void setUi();
    void pushReload();
    void drow();
    void drowNextPosition();
    string decodeAndSet(string path);
    string decodeAndUpdate(string path);
    void encode(string path);
    void inversionForSecondPlayer();


protected:
    void paintEvent(QPaintEvent *event);

private:
    void drowField();
    void swap(int *x, int *y);

    Ui::AnalyzeField *ui;
    Ui::MainWindow *uiMainWindow;
    QPainter *painter;
    QPixmap *fieldPixmap;
    int mag;
    void debug();

    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    int red,blue,colorPattern;

    Network *network;

};

#endif // ANALYZEFIELD_H
