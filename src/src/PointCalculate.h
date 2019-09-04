#ifndef POINTCALCULATE_H
#define POINTCALCULATE_H

#include "Config.h"
#include "MainWindow.h"

class PointCalculate
{
public:
    PointCalculate(vector<vector<Tile>>& tile,vector<vector<Agent>>& agent,Field& field);

    MainWindow *mainWindow;
    Pos makePos(int x,int y);
    int getTilePoints(int color);//タイルポイントを返す
    int getAreaPoints(int color);//領域ポイント計算関数...領域ポイントを返す
    int getAllPoints(int color);
    int checkArea(Pos checkPos,int color);//領域ポイント計算関数...各マスの領域判定


    vector<vector<bool>> areaData;
    vector<vector<int>> checkedData;

    //以下の定義はのちに削除する
    int height =4;//仮の縦幅
    int width =4;//仮の横幅
    void debug();//動作確認用

private:
    vector<vector<Tile>>& tile;
    vector<vector<Agent>>& agent;
    Field& field;

};
#endif // POINTCALCULATE_H
