#include "Computer.h"

Computer::Computer()
{

}

Computer::~Computer()
{

}

/* ### 初期設定 ### */
void Computer::setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field, int num){
    this->uiMainWindow = uiMainWindow;
    this->tile = tile;
    this->teams = teams;
    this->field = field;

    /* provisionalTeamsnの要素サイズを確保 */
    for(int i=0; i<2; ++i){
        provisionalTeams.teamID = 0;
        for(unsigned int j=0; j < teams[i].agents.size(); ++j){
            Agent agentLine;
            agentLine.x = 0;
            agentLine.y = 0;
            agentLine.agentID = 0;
            agentLine.actions.dx = 0;
            agentLine.actions.dy = 0;
            agentLine.actions.type = 0;
            agentLine.actions.apply = 0;
            provisionalTeams.agents.push_back(agentLine);
        }
    }

    /* copyDataの要素サイズの確保 */
    for (int i=0;i<static_cast<int>(field->height);i++) {
        vector<Tile> tileline;
        for(int j=0;j<static_cast<int>(field->width);j++){
            Tile tileData;
            tileData.point = 0;
            tileData.color = 0;
            tileline.push_back(tileData);
        }
        copyTileData.push_back(tileline);
    }

    PC = new PointCalculate ();
    PC->setup(this->tile, this->teams, this->field);

    decodeCorrection(num);
}

/* ### アルゴリズムの選択 ### */
void Computer::startAlgo(int AlgoNumber){
    copyAgent();
    switch(AlgoNumber){
    case 0:
        qDebug() << "ERROR --Don't select Algolithm--";
        break;
    case 1:
        algo(1);
        break;
    case 2:
        algo(2);
        break;
    }
}

void Computer::algo(int num){
    nextPos.myTeam = field->myTeam;
    previousMoveData.clear();
    for(unsigned int i=0; i < teams[nextPos.myTeam].agents.size(); ++i){//エージェントの数だけループ
        provPoint.clear();
        nextPos.agentNum = i; //エージェントの番号
        moveData.x = teams[nextPos.myTeam].agents[nextPos.agentNum].x;//エージェントの位置の代入
        moveData.y = teams[nextPos.myTeam].agents[nextPos.agentNum].y;//
        moveData.accumulationPoint = 0;
        moveData.removeCheck = -1;
        if(num == 1){
            greedy(correction.loopTimes, moveData);
        }else{
            resetCopyTile();
            greedy2(correction.loopTimes, moveData, copyTileData);
        }
        chooseBestResult();
    }

    /* 必要なくなったデータの削除 */
    if(field->turn>0){
        for(unsigned int i=0;i<teams[nextPos.myTeam].agents.size();i++){
            cout<<"erace_"<<i<<"->"<<previousMoveData2.at(0).x<<","<<previousMoveData2.at(0).y<<","<<previousMoveData2.at(0).moveAngle<<endl;
            previousMoveData2.erase(previousMoveData2.begin());
        }
    }
    first = 1;
}

void Computer::greedy(int loopCount, MoveData currentMoveData){
    /* currentMoveData,removeCheckのコピーを取る */
    MoveData copyCurrentMoveData;
    copyCurrentMoveData.x = currentMoveData.x;
    copyCurrentMoveData.y = currentMoveData.y;
    copyCurrentMoveData.accumulationPoint = currentMoveData.accumulationPoint;
    copyCurrentMoveData.removeCheck = currentMoveData.removeCheck;

    int conflict=0;
    double point;
    for(int j=0; j<9; ++j){
        /* currentMoveDataの初期化 */
        currentMoveData.x = copyCurrentMoveData.x;
        currentMoveData.y = copyCurrentMoveData.y;
        currentMoveData.accumulationPoint = copyCurrentMoveData.accumulationPoint;

        /* 移動方向の加算 */
        currentMoveData.x += angle[j][0];
        currentMoveData.y += angle[j][1];

        if(!(outLange(currentMoveData.x, currentMoveData.y))){ //範囲外ではなかったら
            /* 点数の加算*/
            point = tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point;
            point *= correction.loop[loopCount - 1];
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color
                    == field->TeamColorNumber[0]){
                point *= correction.myTeamColorTile; //同色補正
            }
            currentMoveData.accumulationPoint += point;
            if(currentMoveData.moveAngle == 4) currentMoveData.accumulationPoint += correction.stay;//stay補正

            /* 最初のループのみに行う処理 */
            if(loopCount == correction.loopTimes){
                /* 最終的に進む方向の代入 */
                currentMoveData.moveAngle = j;

                /* 味方のエージェントの選択位置を被らせないための処理　*/
                for(unsigned int i = 0; i < previousMoveData.size(); ++i){
                    if(currentMoveData.x == previousMoveData[i].x && currentMoveData.y == previousMoveData[i].y){
                        currentMoveData.accumulationPoint += -999;
                    }
                }
              
                /*currentMoveData.accumulationPointを補正*/
                if(first == 1)conflict = conflictMove(currentMoveData.x,currentMoveData.y,nextPos.agentNum,j);
                if(conflict == 1)currentMoveData.accumulationPoint -=999;
              
                /* agentの距離に応じて罰を付与 */
                currentMoveData.accumulationPoint -= distance(moveData);
            }

            /* 進む方向が敵色タイルだった場合 */
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color
                    == field->TeamColorNumber[1]){
                /* 直前にremoveされているタイルだったら */
                if(j == currentMoveData.removeCheck){
                    currentMoveData.removeCheck = -1;
                }else{ //ではなかったらxyを元に戻して進行方向にチェック
                    currentMoveData.x = copyCurrentMoveData.x;
                    currentMoveData.y = copyCurrentMoveData.y;
                    currentMoveData.removeCheck = j;
                }
            }

            /* 再起or候補の決定 */
            if(loopCount == 1){
                ProvisionalPoint provProvPoint;
                provProvPoint.totalPoint = currentMoveData.accumulationPoint;
                provProvPoint.moveAngle = currentMoveData.moveAngle;
                provPoint.push_back(provProvPoint);
            }else{
                /* 選んだマスに起こす行動がremoveだった場合の処理 */
                greedy(loopCount - 1, currentMoveData);
            }
        }
    }
}

void Computer::greedy2(int loopCount, MoveData currentMoveData, vector<vector<Tile>> currentTileData){
    /* currentMoveDataとcurrentTileDataのコピーを取る */
    MoveData copyCurrentMoveData;
    copyCurrentMoveData.x = currentMoveData.x;
    copyCurrentMoveData.y = currentMoveData.y;
    copyCurrentMoveData.accumulationPoint = currentMoveData.accumulationPoint;
    vector<vector<Tile>> copyCurrentTileData;
    for (unsigned int i=0;i<static_cast<unsigned>(field->height);i++) {
        vector<Tile> tileline;
        for(unsigned int j=0;j<static_cast<unsigned>(field->width);j++){
            Tile tileData;
            tileData.color = currentTileData.at(i).at(j).color;
            tileline.push_back(tileData);
        }
        copyCurrentTileData.push_back(tileline);
    }
    /* 基準となるタイルポイントとエリアポイントの設定*/
    PC->setupOnlyTile(&currentTileData);
    double baseTilePoint = static_cast<double>(PC->getTilePoints(field->TeamColorNumber[0]));
    double baseAreaPoint = static_cast<double>(PC->getAreaPoints(field->TeamColorNumber[0]));

    int conflict=0;
    double point;
    double tilePoint;
    double areaPoint;
    for(int j=0; j<9; ++j){
        /* currentMoveDataの初期化 */
        currentMoveData.x = copyCurrentMoveData.x;
        currentMoveData.y = copyCurrentMoveData.y;
        currentMoveData.accumulationPoint = copyCurrentMoveData.accumulationPoint;

        /* currentTileDataの初期化 */
        for (unsigned int i=0;i<static_cast<unsigned>(currentTileData.size());i++) {
            for(unsigned int j=0;j<static_cast<unsigned>(currentTileData.at(i).size());j++){
                currentTileData.at(i).at(j).color = copyCurrentTileData.at(i).at(j).color;
            }
        }

        /* 移動方向の加算 */
        currentMoveData.x += angle[j][0];
        currentMoveData.y += angle[j][1];

        if(!(outLange(currentMoveData.x, currentMoveData.y))){ //範囲外ではなかったら

            /* 移動先のタイルの色を変更 */
            if(currentTileData.at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color == field->TeamColorNumber[1]){ //相手のマスの場合
                currentTileData.at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color = 0;
            }else if (currentTileData.at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color == 0) { //誰の所有権でもない場合
                currentTileData.at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color = field->TeamColorNumber[0];
            }

            /* 点数の加算*/
            PC->setupOnlyTile(&currentTileData);
            tilePoint = PC->getTilePoints(field->TeamColorNumber[0]) - baseTilePoint;
            areaPoint = PC->getAreaPoints(field->TeamColorNumber[0]) - baseAreaPoint;
            tilePoint *= correction.tile;
            areaPoint *= correction.area;
            point = tilePoint + areaPoint;

            /* 点数の補正 */
            point *= correction.loop[loopCount - 1];
            currentMoveData.accumulationPoint += point;
            if(currentMoveData.moveAngle == 4) currentMoveData.accumulationPoint += correction.stay;//stay補正

            /* 最初のループ限定の処理 */
            if(loopCount == correction.loopTimes){
                /* 最終的に進む方向の代入 */
                currentMoveData.moveAngle = j;

                /* 味方のエージェントの選択位置を被らせないための処理　*/
                for(unsigned int i = 0; i < previousMoveData.size(); ++i){
                    if(currentMoveData.x == previousMoveData[i].x && currentMoveData.y == previousMoveData[i].y){
                        currentMoveData.accumulationPoint += -999;
                    }
                }

                /*currentMoveData.accumulationPointを補正*/
                if(first == 1)conflict = conflictMove(currentMoveData.x,currentMoveData.y,nextPos.agentNum,j);
                if(conflict == 1)currentMoveData.accumulationPoint -=999;

            }

            /* 進む方向が敵色タイルだった場合 */
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color== field->TeamColorNumber[1]){
                //xyを元に戻す
                currentMoveData.x = copyCurrentMoveData.x;
                currentMoveData.y = copyCurrentMoveData.y;
            }

            /* 再起or候補の決定 */
            if(loopCount == 1){//最終ループなら
                if(currentMoveData.moveAngle == 4) currentMoveData.accumulationPoint += correction.stay;//stay補正
                ProvisionalPoint provProvPoint;
                provProvPoint.totalPoint = currentMoveData.accumulationPoint;
                provProvPoint.moveAngle = currentMoveData.moveAngle;
                provPoint.push_back(provProvPoint);
                cout << currentMoveData.moveAngle <<  " point " << currentMoveData.accumulationPoint << endl;
            }else{
                /* 選んだマスに起こす行動がremoveだった場合の処理 */
                greedy2(loopCount - 1, currentMoveData, currentTileData);
            }
        }
    }
}

void Computer::chooseBestResult(){
    double maxPoint = -999;
    int moveAngle = 4;

    /* 最善手を選ぶ */
    for(unsigned int i = 0; i < provPoint.size(); ++i){
        if(maxPoint < provPoint[i].totalPoint){
            maxPoint = provPoint[i].totalPoint;
            moveAngle = provPoint[i].moveAngle;
        }
    }


    /* 選んだ最善手の代入 */
    teams[nextPos.myTeam].agents[nextPos.agentNum].actions.dx = angle[moveAngle][0];//dxの代入
    teams[nextPos.myTeam].agents[nextPos.agentNum].actions.dy = angle[moveAngle][1];//dy
    int x = teams[nextPos.myTeam].agents[nextPos.agentNum].x;
    x += teams[nextPos.myTeam].agents[nextPos.agentNum].actions.dx;
    int y = teams[nextPos.myTeam].agents[nextPos.agentNum].y;
    y += teams[nextPos.myTeam].agents[nextPos.agentNum].actions.dy;
    if(tile->at(static_cast<unsigned>(y-1)).at(static_cast<unsigned>(x-1)).color == field->TeamColorNumber[1]){
        teams[nextPos.myTeam].agents[nextPos.agentNum].actions.type = 2; //remove
    }else{
        teams[nextPos.myTeam].agents[nextPos.agentNum].actions.type = 1; //move
    }
    if(moveAngle == 4){
        teams[nextPos.myTeam].agents[nextPos.agentNum].actions.type = 0; // stay
    }

    /* previousMoveDataへの代入 */
    MoveData preData;
    preData.x = x;
    preData.y = y;
    preData.moveAngle = moveAngle;
    preData.type = teams[nextPos.myTeam].agents[nextPos.agentNum].actions.type;
    previousMoveData.push_back(preData);
    previousMoveData2.push_back(preData);

    if(preData.type == 2){
        preData.x = teams[nextPos.myTeam].agents[nextPos.agentNum].x;
        preData.y = teams[nextPos.myTeam].agents[nextPos.agentNum].y;
        previousMoveData.push_back(preData);
    }

}

/* ### エージェントの移動先が敵と競合しているかの判定 ### */
int Computer::conflictMove(int x,int y,unsigned int agentNum, int angle){
    int myTeam = field->myTeam;
    int enemyTeam;
    if(myTeam ==1)enemyTeam =0;
    else enemyTeam = 1;

    if(x == previousMoveData2.at(agentNum).x){
        if(y == previousMoveData2.at(agentNum).y){//前回の移動先と被っている
            if(angle!=4&&previousMoveData2.at(agentNum).type!=2){ //停留する時を除く+前回のmoveTypeが除去だった場合を除く
                cout<<"po"<<endl;
                if(teams[myTeam].areaPoint + teams[myTeam].tilePoint <= teams[enemyTeam].areaPoint + teams[enemyTeam].tilePoint){
                    cout<<"hoge"<<endl;
                    cout<<"team:"<<myTeam<<" agentNum:"<<agentNum<<endl;
                    cout<<"current_x,y:"<<x<<","<<y<<endl;
                    cout<<"previous_x,y:"<<previousMoveData2.at(agentNum).x<<","<<previousMoveData2.at(agentNum).y<<endl;
                    return 1;//敵エージェントとの競合
                    /* 負けていた場合return1 */
                }
            }
        }
    }
    return 0;
}

/* ### agentデータの複製 ### */
void Computer::copyAgent(){
    provisionalTeams.teamID = teams[field->myTeam].teamID;
    for(unsigned int i=0; i < teams[field->myTeam].agents.size(); ++i){
        provisionalTeams.agents[i].x = teams[field->myTeam].agents[i].x;
        provisionalTeams.agents[i].y = teams[field->myTeam].agents[i].y;
        provisionalTeams.agents[i].agentID = teams[field->myTeam].agents[i].agentID;
        provisionalTeams.agents[i].actions.dx = teams[field->myTeam].agents[i].actions.dx;
        provisionalTeams.agents[i].actions.dy = teams[field->myTeam].agents[i].actions.dy;
        provisionalTeams.agents[i].actions.type = teams[field->myTeam].agents[i].actions.type;
        provisionalTeams.agents[i].actions.apply = teams[field->myTeam].agents[i].actions.apply;
    }
}

void Computer::resetCopyTile(){
    for (unsigned int i=0;i<static_cast<unsigned>(field->height);i++) {
        for(unsigned int j=0;j<static_cast<unsigned>(field->width);j++){
            copyTileData.at(i).at(j).color = tile->at(i).at(j).color;
            copyTileData.at(i).at(j).point = tile->at(i).at(j).point;
        }
    }
}

/* ### agentがfield内にいるか確認 ### */
int Computer::outLange(int x, int y){
    if(x <= 0 || x > field->width || y <= 0 || y > field->height){
        return 1;
    }
    return 0;
}

int Computer::distance(MoveData currentMoveData){
    int disX=0,disY=0,penalty=0;
    for(unsigned int i=0;i<teams[nextPos.myTeam].agents.size();++i){
       disX=currentMoveData.x-teams[nextPos.myTeam].agents[i].x;
       if(disX<0)
           disX*=-1;
       disY=currentMoveData.y-teams[nextPos.myTeam].agents[i].y;
       if(disY<0)
           disY*=-1;

    if(disX>disY)
    penalty=disX;
    else
        penalty=disY;
    if(penalty>correction.agentDistance)
        penalty=0;
    else{
        penalty=field->width+field->height-penalty;
        break;
    }
    }
    penalty*=correction.distance;

    return penalty;
}

int Computer::decodeCorrection(int num){
    string path;
    if(num == 1) path = "abc";
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        return 1;
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();

    QJsonArray arrSplit = obj["split"].toArray();
    QJsonArray arrLast = obj["last"].toArray();

    for(int i=0; i<4; ++i){
        correctionSplit[i].loopTimes = arrSplit.at(i).toObject().value("loopTimes").toInt();
        for(int j=0; j < correctionSplit[i].loopTimes; ++j){
            correctionSplit[i].loop[j] = arrSplit.at(i).toObject().value("loop").toArray().at(j).toInt();
        }
        correctionSplit[i].stay = arrSplit.at(i).toObject().value("stay").toInt();
        correctionSplit[i].myTeamColorTile = arrSplit.at(i).toObject().value("myTeamColorTile").toInt();
        correctionSplit[i].agentDistance = arrSplit.at(i).toObject().value("agentDistance").toInt();
        correctionSplit[i].distance = arrSplit.at(i).toObject().value("distance").toInt();
        correctionSplit[i].tile = arrSplit.at(i).toObject().value("tile").toInt();
        correctionSplit[i].area = arrSplit.at(i).toObject().value("area").toInt();
    }

    for(int i=0; i<3; ++i){
        correctionLast[i].loopTimes = arrLast.at(i).toObject().value("loopTimes").toInt();
        for(int j=0; j < correctionLast[i].loopTimes; ++j){
            correctionLast[i].loop[j] = arrLast.at(i).toObject().value("loop").toArray().at(j).toInt();
        }
        correctionLast[i].stay = arrLast.at(i).toObject().value("stay").toInt();
        correctionLast[i].myTeamColorTile = arrLast.at(i).toObject().value("myTeamColorTile").toInt();
        correctionLast[i].agentDistance = arrLast.at(i).toObject().value("agentDistance").toInt();
        correctionLast[i].distance = arrLast.at(i).toObject().value("distance").toInt();
        correctionLast[i].tile = arrLast.at(i).toObject().value("tile").toInt();
        correctionLast[i].area = arrLast.at(i).toObject().value("area").toInt();
    }

    file.close();
    return 0;
}
