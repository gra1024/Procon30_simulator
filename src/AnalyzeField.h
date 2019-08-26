#ifndef ANALYZEFIELD_H
#define ANALYZEFIELD_H

#include <QWidget>
#include "Config.h"

using namespace std;

namespace Ui {
class AnalyzeField;
}

class AnalyzeField : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeField(vector<vector<Tile>>& tile, vector<vector<Agent>>& agent, Field& field, QWidget *parent = nullptr);
    ~AnalyzeField();
    void setup();
    void setField();
    void setAgent();
    void setUi();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::AnalyzeField *ui;
    string LoadFieldFromTxt();
    void decodeField(string);
    string LoadAgentFromTxt();
    void decodeAgent(string);
    vector<string> split(const string &str, char sep);
    vector<vector<Tile>>& tile;
    vector<vector<Agent>>& agent;
    Field& field;
    QPainter *painter;
    void drowField();
    QPixmap *fieldPixmap;
    unsigned int mag;
};

#endif // ANALYZEFIELD_H
