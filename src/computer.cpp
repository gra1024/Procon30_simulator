#include "Computer.h"

Computer::Computer()
{

}

Computer::~Computer()
{

}


/* ### 初期設定 ### */
void Computer::setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field){
    this->uiMainWindow = uiMainWindow;
    this->tile = tile;
    this->teams = teams;
    this->field = field;
    //this->action = action;
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
    PC = new PointCalculate ();
    PC->setup(tile, teams, field);
    previousMoveData.clear();
}

/* ### アルゴリズムの選択 ### */
void Computer::startAlgo(int AlgoNumber){
    copyAgent();
    switch(AlgoNumber){
    case 0:
        qDebug() << "ERROR --Don't select Algolithm--";
        break;
    case 1:
        algo();
        break;
    }
}

void Computer::algo(){
    nextPos.myTeam = field->myTeam;
    for(unsigned int i=0; i < teams[nextPos.myTeam].agents.size(); ++i){//エージェントの数だけループ
        provPoint.clear();
        nextPos.agentNum = i; //エージェントの番号
        moveData.x = teams[nextPos.myTeam].agents[nextPos.agentNum].x;//エージェントの位置の代入
        moveData.y = teams[nextPos.myTeam].agents[nextPos.agentNum].y;//
        moveData.accumulationPoint = 0;
        greedy(3, moveData);
        chooseBestResult();
    }

    /* 必要なくなったデータの削除 */
    if(field->turn>0){
        for(unsigned int i=0;i<teams[nextPos.myTeam].agents.size();i++){
            cout<<"erace_"<<i<<"->"<<previousMoveData.at(0).x<<","<<previousMoveData.at(0).y<<","<<previousMoveData.at(0).moveAngle<<endl;
            previousMoveData.erase(previousMoveData.begin());
        }
    }
    field->turn++;
}

void Computer::greedy(int loopCount, MoveData currentMoveData){
    /* currentMoveDataのコピーを取る */
    MoveData copyCurrentMoveData;
    copyCurrentMoveData.x = currentMoveData.x;
    copyCurrentMoveData.y = currentMoveData.y;
    copyCurrentMoveData.accumulationPoint = currentMoveData.accumulationPoint;

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
            currentMoveData.accumulationPoint += point;

            /* 最終的に進む方向の代入 */
            if(loopCount == nextPos.maxLoop){
                currentMoveData.moveAngle = j;
                /*currentMoveData.accumulationPointを補正*/
                if(field->turn>0)conflict = conflictMove(currentMoveData.x,currentMoveData.y,nextPos.agentNum,j);
                if(conflict == 1)currentMoveData.accumulationPoint -=999;
            }

            /* 再起or候補の決定 */
            if(loopCount == 1){//最終ループなら
                if(currentMoveData.moveAngle == 4) currentMoveData.accumulationPoint += correction.stay;//stay補正
                ProvisionalPoint provProvPoint;
                provProvPoint.totalPoint = currentMoveData.accumulationPoint;
                provProvPoint.moveAngle = currentMoveData.moveAngle;
                provPoint.push_back(provProvPoint);
            }else{
                greedy(loopCount - 1, currentMoveData);
            }
        }
    }
}

void Computer::chooseBestResult(){
    double maxPoint = -999;
    int moveAngle = 4;

    /* 最善手を選ぶ */
    for(unsigned int i = 0; i < provPoint.size(); ++i){
        //cout << "Angle " << provPoint[i].moveAngle << " Point "<<  provPoint[i].totalPoint << endl;
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
    cout<<"add_"<<nextPos.agentNum<<"->"<<preData.x<<","<<preData.y<<","<<preData.moveAngle<<endl;
}

/* ### エージェントの移動先が敵と競合しているかの判定 ### */
int Computer::conflictMove(int x,int y,unsigned int agentNum, int angle){
    int myTeam = field->myTeam;
    int enemyTeam;
    if(myTeam ==1)enemyTeam =0;
    else enemyTeam = 1;

    if(x == previousMoveData.at(agentNum).x){
        if(y == previousMoveData.at(agentNum).y){//前回の移動先と被っている
            if(angle!=4&&previousMoveData.at(agentNum).type!=2){ //停留する時を除く+前回のmoveTypeが除去だった場合を除く
                cout<<"po"<<endl;
                if(teams[myTeam].areaPoint + teams[myTeam].tilePoint <= teams[enemyTeam].areaPoint + teams[enemyTeam].tilePoint){
                    cout<<"hoge"<<endl;
                    cout<<"team:"<<myTeam<<" agentNum:"<<agentNum<<endl;
                    cout<<"current_x,y:"<<x<<","<<y<<endl;
                    cout<<"previous_x,y:"<<previousMoveData.at(agentNum).x<<","<<previousMoveData.at(agentNum).y<<endl;
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

/* ### agentがfield内にいるか確認 ### */
int Computer::outLange(int x, int y){
    if(x <= 0 || x > field->width || y <= 0 || y > field->height){
        return 1;
    }
    return 0;
}
