#ifndef POINTCALCULATE_H
#define POINTCALCULATE_H

#include "Config.h"
#include "mainwindow.h"

class PointCalculate
{
public:
    PointCalculate();

    MainWindow *mainWindow;
    //color...赤0、青1のようにしてforで処理を繰り返し、コンパクトにする
    Pos makePos(int x,int y);
    int getTilePoints(int color);//タイルポイント計算関数
    int getAreaPoints(int color);//領域ポイント計算関数...データの初期化
    int checkArea(Pos checkPos);//領域ポイント計算関数...各マスの領域判定

    vector<vector<bool>> areaData;
    vector<vector<bool>> checkedData;

    //以下の定義はのちに削除する

    int height=10;//仮の縦幅
    int width=10;//仮の横幅
    int setField(int height,int width);//仮のフィールドを形成する

};
#endif // POINTCALCULATE_H
