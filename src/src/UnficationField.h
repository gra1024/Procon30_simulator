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
    void start();
    void debug();

private:
    string load(int teamNum, string path);
    void provisionalMove();
    int check();
    void move();
    void encode();
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;
    Teams provisionalTeams[2];
};

#endif // UNFICATIONFIELD_H
