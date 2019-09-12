#ifndef POINTCALCULATE_H
#define POINTCALCULATE_H

#include "Config.h"

class PointCalculate
{
public:
    explicit PointCalculate();
    void setup(vector<vector<Tile>> *tile, Teams *teams, Field *field);
    Pos makePos(int x,int y);
    int getTilePoints(int color);//タイルポイントを返す
    int getAreaPoints(int color);//領域ポイント計算関数...領域ポイントを返す
    int getAllPoints(int color);
    int checkArea(Pos checkPos,int color);//領域ポイント計算関数...各マスの領域判定
    void updatePoint();


    vector<vector<bool>> areaData;
    vector<vector<int>> checkedData;

    void debug();//動作確認用

private:
    vector<vector<Tile>> *tile;
    Teams *teams;
    Field *field;

};
#endif // POINTCALCULATE_H
