#include "PointCalculate.h"

PointCalculate::PointCalculate()
{
    this->mainWindow=mainWindow;
    setField(height,width);
}

Pos PointCalculate::makePos(int x,int y){
    Pos p;
    p.x=x;
    p.y=y;
    return p;
}

int PointCalculate::getTilePoints(int color){
    int tilePoint=0;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            if(mainWindow->tile[y][x].color==color)tilePoint+=mainWindow->tile[y][x].point;//現在見るべき色のタイルのみを計算に入れる
        }
    }
    return tilePoint;//REDで呼ばれたらREDのタイルポイントを返す、BLUEも同様
}

int PointCalculate::getAreaPoints(int color){
    //領域データの設定
    areaData.clear();
    checkedData.clear();
    for(int y=0;y<height;y++){//配列用意の順番的にxからループを始める
        vector<bool> tmpData;
        for(int x=0;x<width;x++){
            tmpData.push_back(false);
        }
        areaData.push_back(tmpData);
        checkedData.push_back(tmpData);
    }

    for(int y=1;y<height-1;y++){//フィールドの端のマスは領域ポイントを取らないためループから省く
        for(int x=1;x<width-1;x++){//横に見ていく、全部見たら次の列、という形
            if(mainWindow->tile[y][x].color!=color){
                Pos checkPos=makePos(x,y);
                checkArea(checkPos);//自タイルが置かれていないなら検証を行う
            }
        }
    }
}

int PointCalculate::checkArea(Pos checkPos){

}

int PointCalculate::setField(int height,int width){
    mainWindow->tile.clear();
    for(int y=0;y<height;y++){//配列用意の順番的にxからループを始める
        vector<tile> tmpData;
        for(int x=0;x<width;x++){
            tmpData.color=WHITE;
            tmpData.point=0;
        }
        mainWindow->tile.push_back(tmpData);
    }
}

//#endif // POINTCALCULATE_H
