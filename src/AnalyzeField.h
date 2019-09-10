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
    explicit AnalyzeField(Ui::MainWindow *uiMainWindow, QWidget *parent = nullptr);
    ~AnalyzeField();
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field);
    void setUi();
    void drowField();
    void pushReload();
    string decodeAndSet();
    string decodeAndUpdate();
    void encode(int type[],int dx[],int dy[]);
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    int red,blue,colorPattern;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::AnalyzeField *ui;
    Ui::MainWindow *uiMainWindow;
    vector<string> split(const string &str, char sep);
    QPainter *painter;
    QPixmap *fieldPixmap;

    unsigned int mag;


};

#endif // ANALYZEFIELD_H
