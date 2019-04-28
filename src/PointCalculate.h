#ifndef POINTCALCULATE_H
#define POINTCALCULATE_H

#include "Config.h"
#include "mainwindow.h"

class PointCalculate
{
public:
    PointCalculate(vector<vector<Tile>>& tile,vector<vector<Agent>>& agent,Field& field);

    MainWindow *mainWindow;
    Pos makePos(int x,int y);
    int getTilePoints(int color);//タイルポイントを返す
    int getAreaPoints(int color);//領域ポイント計算関数...データの初期化、関数への値の受渡
    int checkArea(Pos checkPos,int color);//領域ポイント計算関数...各マスの領域判定
    int calculateAreaData();//領域ポイント計算関数...領域ポイントを返す


    vector<vector<bool>> areaData;
    vector<vector<int>> checkedData;

    //以下の定義はのちに削除する

    int height;//仮の縦幅
    int width;//仮の横幅

private:
    vector<vector<Tile>>& tile;
    vector<vector<Agent>>& agent;
    Field& field;

};
#endif // POINTCALCULATE_H
