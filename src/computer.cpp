#include "Computer.h"

Computer::Computer(Ui::MainWindow *uiMainWindow):
        uiMainWindow(uiMainWindow)
{

}

Computer::~Computer()
{

}

void Computer::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field){
    this->tile = tile;
    this->teams = teams;
    this->field = field;
}
