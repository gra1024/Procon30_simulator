#ifndef UNFICATIONFIELD_H
#define UNFICATIONFIELD_H

#include "Config.h"

using namespace std;

class UnficationField
{
public:
    explicit UnficationField();
    ~UnficationField();
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field);
    string load(int teamNum, string path);
    void debug();

    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;

private:

};

#endif // UNFICATIONFIELD_H
