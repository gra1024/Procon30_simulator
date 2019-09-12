#include "PointCalculate.h"

PointCalculate::PointCalculate()
{

}

void PointCalculate::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field){
    this->tile = tile;
    this->teams = teams;
    this->field = field;
}

Pos PointCalculate::makePos(int x,int y){
    Pos p;
    p.x=x;
    p.y=y;
    return p;
}

void PointCalculate::updatePoint(){
    teams[0].tilePoint = getTilePoints(teams[0].teamID);
    teams[0].areaPoint = getAreaPoints(teams[0].teamID);
    teams[1].tilePoint = getTilePoints(teams[1].teamID);
    teams[1].areaPoint = getAreaPoints(teams[1].teamID);
}

int PointCalculate::getTilePoints(int color){
    int tilePoint=0;
    for(int y=0;y<field->height;y++){
        for(int x=0;x<field->width;x++){
            if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color==color){
                tilePoint+=tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).point;//現在見るべき色のタイルのみを計算に入れる
            }
        }
    }
    return tilePoint;//REDで呼ばれたらREDのタイルポイントを返す、BLUEも同様
}

int PointCalculate::getAreaPoints(int color){
    //領域データの設定
    areaData.clear();
    checkedData.clear();
    for(int y=0;y<field->height;y++){//配列用意の順番的にxからループを始める
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
        for(int x=1;x<field->width-1;x++){//横に見ていく、全部見たら次の列、という形
            if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color
                    !=color&&checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]!=-2){//自タイルが置かれていない&&非領域エリアでないなら検証を行う
                if(checkArea(makePos(static_cast<int>(x),static_cast<int>(y)),color)){//検証結果が１...-1とチェックしたマスはareaDataへと加える
                    for(int y=0;y<field->height;y++){
                        for(int x=0;x<field->width;x++){
                            if(checkedData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]==-1)
                                areaData[static_cast<unsigned>(y)][static_cast<unsigned>(x)]=1;
                        }
                    }
                }
                else {//検証結果が０...-1とチェックしたマスは非領域エリア(-2)としてcheckedDataを更新、処理を減らすため
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

int PointCalculate::getAllPoints(int color){
    return getAreaPoints(color)+getAreaPoints(color);
}

int PointCalculate::checkArea(Pos checkPos,int color){
    cout<<"currentPos..."<<checkPos.x<<","<<checkPos.y<<endl;
    Pos looking[]={
        makePos(0,1),
        makePos(1,0),
        makePos(0,-1),
        makePos(-1,0)
    };//４近傍

    for(int i=0;i<4;i++){
        if(checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]==-2){//見ているマスが非領域エリアの場合...つながっているマスはすべて領域ポイントを取らないため、ループを抜けて次の検証に移る
            return 0;
        }
        else if(tile->at(static_cast<unsigned>(checkPos.y+looking[i].y)).at(static_cast<unsigned>(checkPos.x+looking[i].x)).color==color){
            //見ているマス上に自タイルが置かれている場合...領域の端になる可能性があるため、そのマスをチェックしておく
            checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]=1;//領域の端は１でチェック
        }
        else if(checkPos.y+looking[i].y==field->height-1||checkPos.x+looking[i].x==field->width-1||checkPos.y+looking[i].y==0||checkPos.x+looking[i].x==0){
            //見ているマスがfieldの端に接しており、自タイルが置かれていない場合...つながっているマスはすべて領域ポイントを取らないため、ループを抜けて次の検証に移る
            return 0;
        }
        else if(checkedData[static_cast<unsigned>(checkPos.y+looking[i].y)][static_cast<unsigned>(checkPos.x+looking[i].x)]!=-1){//元のマスを見ないようにする
            //見ているマスが端に接しておらず、自タイルも置かれていない場合...領域の中身になる可能性があるため、チェックして再帰、そのマスからこの関数を呼び出す
            checkedData[static_cast<unsigned>(checkPos.y)][static_cast<unsigned>(checkPos.x)]=-1;//領域の中は-1でチェック
            int result=checkArea(makePos(static_cast<int>(checkPos.x+looking[i].x),static_cast<int>(checkPos.y+looking[i].y)),color);
            //再帰中にfieldの端に接した場合...result==0,領域ポイントを取らないため、ループを抜けて次の検証に移る
            if(result==0)return result;
        }
    }
    //４近傍のチェックが正常に終了した場合...result==1,領域の端を取って終了
    checkedData[static_cast<unsigned>(checkPos.y)][static_cast<unsigned>(checkPos.x)]=-1;
    int result=1;
    return result;
}

void PointCalculate::debug(){
    //int tilePoint=getTilePoints(RED);
    //int areaPoint=getAreaPoints(RED);
    // cout<<"RED.tilePoint..."<<tilePoint<<endl;
    //cout<<"RED.areaPoint..."<<areaPoint<<endl;
    //tilePoint=getTilePoints(BLUE);
    //areaPoint=getAreaPoints(BLUE);
    //cout<<"BLUE.tilePoint..."<<tilePoint<<endl;
    //cout<<"BLUE.areaPoint..."<<areaPoint<<endl;
}
