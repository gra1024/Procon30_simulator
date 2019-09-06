#ifndef COMPUTER_H
#define COMPUTER_H

#include <QWidget>
#include "Config.h"

#include "ui_MainWindow.h"

using namespace std;

class Computer
{
public:
    explicit Computer(Ui::MainWindow *uiMainWindow);
    ~Computer();
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field);
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
private:
    Ui::MainWindow *uiMainWindow;

};

#endif // COMPUTER_H
