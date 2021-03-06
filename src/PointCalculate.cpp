#include "PointCalculate.h"

PointCalculate::PointCalculate()
{

}

/*　### 初期設定 ###　*/
void PointCalculate::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field){
    this->tile = tile;
    this->teams = teams;
    this->field = field;
}

void PointCalculate::setupOnlyTile(vector<vector<Tile> > *tile){
    this->tile = tile;
}

/*　### 位置の構造体を作成する ###　*/
Pos PointCalculate::makePos(int x,int y){
    Pos p;
    p.x=x;
    p.y=y;
    return p;
}

/*　### 各チームのタイルポイント、領域ポイントを更新する ###　*/
void PointCalculate::updatePoint(){
    teams[0].tilePoint = getTilePoints(teams[0].teamID);
    teams[0].areaPoint = getAreaPoints(teams[0].teamID);
    teams[1].tilePoint = getTilePoints(teams[1].teamID);
    teams[1].areaPoint = getAreaPoints(teams[1].teamID);
}

/*　### 与えられた色に対応するチームのタイルポイントを計算する ###　*/
int PointCalculate::getTilePoints(int color){
    int tilePoint=0;
    for(int y=0;y<field->height;y++){
        for(int x=0;x<field->width;x++){
            if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color==color){
                tilePoint+=tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).point;
            }
        }
    }
    return tilePoint;
}

/*　### 与えられた色に対応するチームの領域ポイントを計算する ###　*/
int PointCalculate::getAreaPoints(int color){
    areaData.clear();
    checkedData.clear();
    for(int y=0;y<field->height;y++){
        vector<bool> tmpDataB;
        vector<int> tmpDataI;
        for(int x=0;x<field->width;x++){
            tmpDataB.push_back(false);
            tmpDataI.push_back(0);
        }
        areaData.push_back(tmpDataB);
        checkedData.push_back(tmpDataI);
    }

    for(int y=1;y<field->height-1;y++){//フィールドの端のマスは領域ポイントを取らないためループから省く
        for(int x=1;x<field->width-1;x++){
            if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color
                    !=color&&checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]!=-2){
                if(checkArea(makePos(static_cast<int>(x),static_cast<int>(y)),color)){
                    for(int y=0;y<field->height;y++){
                        for(int x=0;x<field->width;x++){
                            if(checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]==-1)
                                areaData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]=1;
                        }
                    }
                }
                else {
                    for(int y=0;y<field->height;y++){
                        for(int x=0;x<field->width;x++){
                            if(checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]==-1)
                                checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]=-2;
                        }
                    }
                }
            }
        }
    }

    //完成したareaDataを用いて領域ポイントを計算する
    int areaPoint=0;
    for(int y=0;y<field->height;y++){
        for(int x=0;x<field->width;x++){
            if(areaData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]==1)areaPoint
                    +=abs(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).point);//絶対値で計算
        }
    }
    return areaPoint;
}

/*　### 与えられた色に対応するチームの合計ポイントを計算する ###　*/
int PointCalculate::getAllPoints(int color){
    return getTilePoints(color)+getAreaPoints(color);
}

/*　### 与えられたマスが領域ポイントとして計算されるかどうかの判定を行う ###　*/
int PointCalculate::checkArea(Pos checkPos,int color){
    Pos looking[]={
        makePos(0,1),
        makePos(1,0),
        makePos(0,-1),
        makePos(-1,0)
    };

    for(int i=0;i<4;i++){
        if(checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]==-2){
            return 0;
        }
        else if(tile->at(static_cast<unsigned>(checkPos.y+looking[i].y)).at(static_cast<unsigned>(checkPos.x+looking[i].x)).color==color){
            checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]=1;
        }
        else if(checkPos.y+looking[i].y==field->height-1||checkPos.x+looking[i].x==field->width-1||checkPos.y+looking[i].y==0||checkPos.x+looking[i].x==0){
            return 0;
        }
        else if(checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]!=-1){
            checkedData[static_cast<unsigned>(checkPos.y)][static_cast<unsigned>(checkPos.x)]=-1;
            int result=checkArea(makePos(static_cast<int>(checkPos.x+looking[i].x),static_cast<int>(checkPos.y+looking[i].y)),color);
            if(result==0)return result;
        }
    }

    checkedData[static_cast<unsigned>(checkPos.y)][static_cast<unsigned>(checkPos.x)]=-1;
    int result=1;
    return result;
}
