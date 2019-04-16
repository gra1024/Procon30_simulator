#ifndef POINTCALCULATE_H
#define POINTCALCULATE_H

#define RED 0
#define BLUE 1

//#include <vector>

class PointCalculate
{
public:
    PointCalculate();

    //color...赤0、青1のようにしてforで処理を繰り返し、コンパクトにする
    Pos makePos(int x,int y);
    int getTilePoints(int color);//タイルポイント計算関数
    int getAreaPoints(int color);//領域ポイント計算関数...データの初期化
    int checkArea(Pos checkPos);//領域ポイント計算関数...各マスの領域判定


    vector<vector<bool>> areaData;
    vector<vector<bool>> checkedData;

    //以下の変数はのちにmainwindowに集約する、posの定義もmainwindowのほうがいいかも

    int height=10;//仮の縦幅
    int width=10;//仮の横幅

    struct Pos{
        int x;
        int y;
    };

    struct tile{
        int x;
        int y;
        int color;
        int points;
    };

};
#endif // POINTCALCULATE_H
