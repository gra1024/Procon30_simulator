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
    splitTurn();
}

/* ### アルゴリズムの選択 ### */
void Computer::startAlgo(int algoNumber){
    copyAgent();
    if (algoNumber > 0 && algoNumber <= 16) {
        algo(1);
    }else if (algoNumber > 16 && algoNumber <= 32) {
        algo(2);
    }else if(algoNumber == 33){
        algo(1);
    }else if(algoNumber == 34){
        algo(2);
    }else{
        qDebug() << "ERROR --Don't select Algolithm--";
    }
}

/* ### アルゴリズムを動作させる準備 ### */
void Computer::algo(int num){
    partSelect();
    nextPos.myTeam = field->myTeam;
    previousMoveData.clear();
    previousMoveData3.clear();
    setPreviousMoveData();
    for(unsigned int i=0; i < teams[nextPos.myTeam].agents.size(); ++i){//エージェントの数だけループ
        provPoint.clear();
        nextPos.agentNum = i; //エージェントの番号
        moveData.x = teams[nextPos.myTeam].agents[nextPos.agentNum].x;//エージェントの位置の代入
        moveData.y = teams[nextPos.myTeam].agents[nextPos.agentNum].y;//
        moveData.accumulationPoint = 0;
        moveData.removeCheck = -1;
        if(num == 1){
            greedy(correctionSplit[partCount].loopTimes, moveData);
        }else{
            resetCopyTile();
            greedy2(correctionSplit[partCount].loopTimes, moveData, copyTileData);
        }
        chooseBestResult();
    }

    /* 必要なくなったデータの削除 */
    if(first==1){
        for(unsigned int i=0;i<teams[nextPos.myTeam].agents.size();i++){
            //cout<<"erace_"<<i<<"->"<<previousMoveData2.at(0).x<<","<<previousMoveData2.at(0).y<<","<<previousMoveData2.at(0).moveAngle<<endl;
            previousMoveData2.erase(previousMoveData2.begin());
        }
    }
    first = 1;
}

/* ### 貪欲法アルゴリズム(tileの得点を見て動くパターン) ### */
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
            //ポイントの代入
            point = tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point;

            //ループ補正（乗算）
            point *= correctionSplit[partCount].loop[static_cast<unsigned>(loopCount - 1)];

            //stay補正（減算）
            if(currentMoveData.moveAngle == 4){
                currentMoveData.accumulationPoint -= correctionSplit[partCount].stay;
            }

            //すでに獲得しているに進んだ場合の補正（減算）
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color == field->TeamColorNumber[0]){
                point -= correctionSplit[partCount].myTeamColorTile;
            }

            //味方のエージェントとの距離が近い場合の補正（減算）
            currentMoveData.accumulationPoint -= distance(moveData);

            //ルートの総合ポイントへの加算
            currentMoveData.accumulationPoint += point;

            /* 最初のループのみに行う処理 */
            if(loopCount == correctionSplit[partCount].loopTimes){
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

                if(conflict == 1){
                    previousMoveData2.at(nextPos.agentNum).conflictNum++;//競合回数を数える
                    //cout<<"agentNum_"<<nextPos.agentNum<<",currentConflict->"<<previousMoveData2.at(nextPos.agentNum).conflictNum<<endl;
                    if(previousMoveData2.at(nextPos.agentNum).conflictNum==2){
                        currentMoveData.accumulationPoint += -999;
                        previousMoveData2.at(nextPos.agentNum).conflictNum = 0;
                    }
                }

                /* 味方のエージェントとなるべく被らないようにするための補正（現在いるマスに行動を選択したときの補正（減算）） */
                for(unsigned int i = 0; i < previousMoveData3.size(); ++i){
                    if(currentMoveData.x == previousMoveData3[i].x && currentMoveData.y == previousMoveData3[i].y){
                        //補正値：選択したタイルのマス-10 ただし0以上に大きくはならない
                        if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point >= 10){
                            currentMoveData.accumulationPoint += -1;
                        }else{
                            currentMoveData.accumulationPoint += tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point - 10;
                        }
                    }
                }

                /* 敵のエージェントとなるべく被らないようにするための補正（現在いるマスに行動を選択したときの補正（減算）） */
                for(unsigned int i = 0; i < teams[1].agents.size(); ++i){
                    if(currentMoveData.x == teams[1].agents[i].x && currentMoveData.y == teams[1].agents[i].y){
                        //補正値：選択したタイルのマス-10 ただし0以上に大きくはならない
                        if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point >= 10){
                            currentMoveData.accumulationPoint += -1;
                        }else{
                            currentMoveData.accumulationPoint += tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point - 10;
                        }
                    }
                }
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

/* ### 貪欲法アルゴリズム（ポイントの得点差で動くパターン）（メインアルゴリズム） ### */
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
    double baseEnemyTilePoint = static_cast<double>(PC->getTilePoints(field->TeamColorNumber[1]));
    double baseEnemyAreaPoint = static_cast<double>(PC->getAreaPoints(field->TeamColorNumber[1]));

    int conflict=0;
    double tilePoint;
    double areaPoint;
    double allPoint;
    double enemyTilePoint;
    double enemyAreaPoint;

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

            /* 点数の加算・補正*/
            //タイルポイントとエリアポイントの加算
            PC->setupOnlyTile(&currentTileData);
            tilePoint = PC->getTilePoints(field->TeamColorNumber[0]) - baseTilePoint;
            areaPoint = PC->getAreaPoints(field->TeamColorNumber[0]) - baseAreaPoint;

            //敵が失ったポイントの補正（加算）
            enemyTilePoint = baseEnemyTilePoint - PC->getTilePoints(field->TeamColorNumber[1]);
            enemyAreaPoint = baseEnemyAreaPoint - PC->getAreaPoints(field->TeamColorNumber[1]);

            //タイルポイントとエリアポイントの補正(乗算)
            tilePoint *= correctionSplit[partCount].tile;
            areaPoint *= correctionSplit[partCount].area;
            enemyTilePoint *= correctionSplit[partCount].tile;
            enemyAreaPoint *= correctionSplit[partCount].area;
            allPoint = tilePoint + areaPoint + enemyTilePoint + enemyAreaPoint;

            //ループ補正（乗算）
            allPoint *= correctionSplit[partCount].loop[static_cast<unsigned>(loopCount - 1)];

            //stay補正（減算）
            if(currentMoveData.moveAngle == 4){
                allPoint -= correctionSplit[partCount].stay;
            }

            //すでに獲得しているに進んだ場合の補正（減算）
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color == field->TeamColorNumber[0]){
                allPoint -= correctionSplit[partCount].myTeamColorTile;
            }

            //味方のエージェントとの距離が近い場合の補正（減算）
            allPoint -= distance(moveData);

            /* 最初のループ限定の処理 */
            if(loopCount == correctionSplit[partCount].loopTimes){
                /* 最終的に進む方向の代入 */
                currentMoveData.moveAngle = j;
                /* 味方のエージェントの選択位置を被らせないための処理　*/
                for(unsigned int i = 0; i < previousMoveData.size(); ++i){
                    if(currentMoveData.x == previousMoveData[i].x && currentMoveData.y == previousMoveData[i].y){
                        allPoint += -999;
                    }
                }
                /*currentMoveData.accumulationPointを補正*/
                if(first == 1)conflict = conflictMove(currentMoveData.x,currentMoveData.y,nextPos.agentNum,j);
                if(conflict == 1){
                    previousMoveData2.at(nextPos.agentNum).conflictNum++;//競合回数を数える
                    //cout<<"agentNum_"<<nextPos.agentNum<<",currentConflict->"<<previousMoveData2.at(nextPos.agentNum).conflictNum<<endl;
                    if(previousMoveData2.at(nextPos.agentNum).conflictNum==1){
                        allPoint += -999;
                        previousMoveData2.at(nextPos.agentNum).conflictNum = 0;
                    }
                }
                /* 味方のエージェントとなるべく被らないようにするための補正（現在いるマスに行動を選択したときの補正（減算）） */
                for(unsigned int i = 0; i < previousMoveData3.size(); ++i){
                    if(currentMoveData.x == previousMoveData3[i].x && currentMoveData.y == previousMoveData3[i].y){
                        //補正値：選択したタイルのマス-10 ただし0以上に大きくはならない
                        if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point >= 10){
                            allPoint += -1;
                        }else{
                            allPoint += tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point - 10;
                        }
                    }
                }

                /* 敵のエージェントとなるべく被らないようにするための補正（現在いるマスに行動を選択したときの補正（減算）） */
                for(unsigned int i = 0; i < teams[1].agents.size(); ++i){
                    if(currentMoveData.x == teams[1].agents[i].x && currentMoveData.y == teams[1].agents[i].y){
                        //補正値：選択したタイルのマス-10 ただし0以上に大きくはならない
                        if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point >= 10){
                            allPoint += -1;
                        }else{
                            allPoint += tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).point - 10;
                        }
                    }
                }
            }
            currentMoveData.accumulationPoint += allPoint;
            //cout <<"allPoint" <<  allPoint << endl;

            /* 進む方向が敵色タイルだった場合 */
            if(tile->at(static_cast<unsigned>(currentMoveData.y) - 1).at(static_cast<unsigned>(currentMoveData.x) - 1).color== field->TeamColorNumber[1]){
                //xyを元に戻す
                currentMoveData.x = copyCurrentMoveData.x;
                currentMoveData.y = copyCurrentMoveData.y;
            }

            /* 再起or候補の決定 */
            if(loopCount == 1){//最終ループなら
                if(currentMoveData.moveAngle == 4) currentMoveData.accumulationPoint += correctionSplit[partCount].stay;//stay補正
                ProvisionalPoint provProvPoint;
                provProvPoint.totalPoint = currentMoveData.accumulationPoint;
                provProvPoint.moveAngle = currentMoveData.moveAngle;
                provPoint.push_back(provProvPoint);
            }else{
                /* 選んだマスに起こす行動がremoveだった場合の処理 */
                greedy2(loopCount - 1, currentMoveData, currentTileData);
            }
        }
    }
}

/* ### 最善手を選択 ### */
void Computer::chooseBestResult(){
    double maxPoint = -999;
    int moveAngle = 4;

    /* 最善手を選ぶ */
    for(unsigned int i = 0; i < provPoint.size(); ++i){
        //cout << "[" << provPoint[i].moveAngle << " " << provPoint[i].totalPoint << "]";
        if(field->turn % 2 == 0){
            if(maxPoint <= provPoint[i].totalPoint){
                maxPoint = provPoint[i].totalPoint;
                moveAngle = provPoint[i].moveAngle;
            }
        }else{
            if(maxPoint < provPoint[i].totalPoint){
                maxPoint = provPoint[i].totalPoint;
                moveAngle = provPoint[i].moveAngle;
            }
        }

    }
    //cout << endl;

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
    preData.color = tile->at(static_cast<unsigned>(y) - 1).at(static_cast<unsigned>(x) - 1).color;
    if(first==0)preData.conflictNum = 0;
    else if(first==1)preData.conflictNum = previousMoveData2.at(nextPos.agentNum).conflictNum;
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

    if(angle!=4){//停留を選んでいない場合
        if(x == previousMoveData2.at(agentNum).x){
            if(y == previousMoveData2.at(agentNum).y){//前回の移動先と被っているなら
                if(teams[myTeam].areaPoint + teams[myTeam].tilePoint <= teams[enemyTeam].areaPoint + teams[enemyTeam].tilePoint){//総合得点が負けているなら
                    if(previousMoveData2.at(agentNum).type!=2){ //前回の移動タイプが除去でないなら
                        return 1;
                    }
                    else if(previousMoveData2.at(agentNum).type==2){//前回の移動タイプが除去なら
                        if(previousMoveData2.at(agentNum).color==tile->at(static_cast<unsigned>(y)-1).at(static_cast<unsigned>(x)-1).color){//前回の除去で色が変わっていないなら
                            return 1;
                        }
                    }
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

/* ### 変数copyTileの初期化 ### */
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

/* ### エージェント同士の距離が近くなりすぎないように補正をかける ### */
double Computer::distance(MoveData currentMoveData){
    int disX, disY, dis;
    double penalty = 0;
    for(unsigned int i=0;i<teams[nextPos.myTeam].agents.size();++i){
        if(!(nextPos.agentNum == i)){
            /* 各エージェントとの距離の差を計算 */
            disX = abs(currentMoveData.x - teams[nextPos.myTeam].agents[i].x);
            disY = abs(currentMoveData.y - teams[nextPos.myTeam].agents[i].y);
            if(disX > disY){
                dis = disX;
            } else {
                dis = disY;
            }

            /* 距離が5より大きい場合の処理は5と同じ　*/
            if (dis > 5) dis = 5;

            /* ペナルティの加算 */
            penalty += correctionSplit[partCount].distance[dis];

        }
    }
    return penalty;
}

/* ### 補正リストの読み込み ### */
int Computer::decodeCorrection(int num){
    string path = "..//data//CorrectionList//correction";
    path += to_string(num);
    path += ".json";
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        cout << "ERROR --don't Read file of correction--" << endl;
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
            correctionSplit[i].loop.push_back(arrSplit.at(i).toObject().value("loop").toArray().at(j).toDouble());
        }
        correctionSplit[i].stay = arrSplit.at(i).toObject().value("stay").toDouble();
        correctionSplit[i].myTeamColorTile = arrSplit.at(i).toObject().value("myTeamColorTile").toDouble();
        for(int j=0; j < 6; ++j){
            correctionSplit[i].distance[j] = arrSplit.at(i).toObject().value("distance").toArray().at(j).toDouble();
        }
        correctionSplit[i].tile = arrSplit.at(i).toObject().value("tile").toDouble();
        correctionSplit[i].area = arrSplit.at(i).toObject().value("area").toDouble();
    }

    for(int i=0; i<3; ++i){
        correctionSplit[i+4].loopTimes = arrLast.at(i).toObject().value("loopTimes").toInt();
        for(int j=0; j < correctionSplit[i].loopTimes; ++j){
            correctionSplit[i+4].loop.push_back(arrLast.at(i).toObject().value("loop").toArray().at(j).toDouble());
        }
        correctionSplit[i+4].stay = arrLast.at(i).toObject().value("stay").toDouble();
        correctionSplit[i+4].myTeamColorTile = arrLast.at(i).toObject().value("myTeamColorTile").toDouble();
        for(int j=0; j < 6; ++j){
            correctionSplit[i+4].distance[j] = arrSplit.at(i).toObject().value("distance").toArray().at(j).toDouble();
        }
        correctionSplit[i+4].tile = arrLast.at(i).toObject().value("tile").toDouble();
        correctionSplit[i+4].area = arrLast.at(i).toObject().value("area").toDouble();
    }
    file.close();
    return 0;
}

/* ### 補正のパターンをターンによって変える ### */
void Computer::splitTurn(){
    part[0] = field->maxTurn / 4;
    part[1] = field->maxTurn / 2;
    part[2] = field->maxTurn * 3 / 4;
    part[3] = field->maxTurn - 3;
    part[4] = field->maxTurn - 2;
    part[5] = field->maxTurn - 1;
    part[6] = field->maxTurn;
    if(part[2] > part[3]){
        part[2] = field->maxTurn - 4;
    }
    if(part[1] > part[2]){
        part[1] = field->maxTurn - 5;
    }
    if(part[0] > part[1]){
        part[0] = field->maxTurn - 6;
    }

    /* 出力 */
    /*cout << "part " ;
    for (int i=0; i<7; i++) {
        cout << part[i] << " " ;
    }
    cout << endl;
    cout << partCount << endl;
    */
}

/* ### 補正のパターンを変える ### */
void Computer::partSelect(){
    //cout << field->turn << " " << part[partCount] << " " << partCount << " ";
    if(partAfterTurnOver == 0 && field->turn > part[partCount]){
        partCount++;
    }
    
    if(partAfterTurnOver == 0 && partCount == 7){
        partAfterTurnOver = 1;
        partCount = 0;
    }
    //cout << "partCount " << partCount << endl;
}

void Computer::setPreviousMoveData(){
    for (unsigned int i=0; i < teams[0].agents.size(); ++i) {
        MoveData preData;
        preData.x = teams[0].agents[i].x;
        preData.y = teams[0].agents[i].y;
        previousMoveData3.push_back(preData);
    }
}
