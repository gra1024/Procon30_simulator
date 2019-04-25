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
    void setupField();

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
};

#endif // ANALYZEFIELD_H
