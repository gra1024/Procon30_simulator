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
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field, QJsonObject matchReply);
    void setUi();
    void drowField();
    void pushReload(QJsonObject matchReply);
    void drow();
    string decodeAndSet(string path);
    string decodeAndUpdate(string path);
    void encode(string path);
    void drowNextPosition();
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    int red,blue,colorPattern;
    QByteArray actionData;
    QJsonObject matchReply;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::AnalyzeField *ui;
    Ui::MainWindow *uiMainWindow;
    QPainter *painter;
    QPixmap *fieldPixmap;
    int mag;
    void debug();

};

#endif // ANALYZEFIELD_H
