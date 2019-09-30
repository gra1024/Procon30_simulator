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
}

/* ### アルゴリズムの選択 ### */
void Computer::startAlgo(int AlgoNumber){
    copy();
    switch(AlgoNumber){
    case 0:
        greedy2();
        break;
    case 1:
        ;
    }
}

/* ### メインアルゴリズム１ ### */
/*
void Computer::greedy(){

    unsigned int i,j;
    int angle[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    int maximum=-100,tilepoint=0,teamcolor;
    teamcolor = teams[0].teamID;

    for(j=0;j<teams[0].agents.size();j++)
    {
        for(i=0;i<8;i++)
        {
            if(static_cast<int>(teams[0].agents[j].x)+angle[i][0]<=static_cast<int>(field->width)&&static_cast<int>(teams[0].agents[j].y)+angle[i][1]<=static_cast<int>(field->height)&&static_cast<int>(teams[0].agents[j].y)+angle[i][1]-1>=0&&static_cast<int>(teams[0].agents[j].x)+angle[i][0]-1>=0)
            {

                if(tile->at(teams[0].agents[j].y+static_cast<unsigned>(angle[i][1])-1).at(teams[0].agents[j].x+static_cast<unsigned>(angle[i][0])-1).color==teamcolor)
                    tilepoint=-1;
                else
                    tilepoint=tile->at(teams[0].agents[j].y+static_cast<unsigned>(angle[i][1])-1).at(teams[0].agents[j].x+static_cast<unsigned>(angle[i][0])-1).point;
                tilepoint+=eightangle(angle,angle[i][0],angle[i][1],j,3);//3手先

                if(tilepoint>maximum)
                {
                    maximum=tilepoint;
                    //action->dx=-1+angle[i][0];
                    //action->dy=-1+angle[i][1];
                    if(tile->at(teams[0].agents[j].y+static_cast<unsigned>(action->dy)).at(teams[0].agents[j].x+static_cast<unsigned>(action->dx)).color==teamcolor||tile->at(teams[0].agents[j].y+static_cast<unsigned>(action->dy)).at(teams[0].agents[j].x+static_cast<unsigned>(action->dx)).color==WHITE)
                        //action->type=1;
                    else{
                        //action->type=2;
                    }
                }
            }
        }
    }

}
*/

/* ### メインアルゴリズム２ ### */
void Computer::greedy2(){

    //int color = field->TeamColorNumber[0];
    int myTeam = field->myTeam;
    int maxPoint;
    int position;
    unsigned int x, y;
    for(unsigned int i=0; i < teams[myTeam].agents.size(); ++i){
        maxPoint = -999;
        position = 0;
        for(int j=0; j<9; ++j){
            result[j][0]=0;
            result[j][1]=0;
        }
        for(int j=0; j<9; ++j){
            provisionalTeams.agents[i].x = teams[myTeam].agents[i].x;
            provisionalTeams.agents[i].y = teams[myTeam].agents[i].y;
            provisionalTeams.agents[i].x += angle[j][0];
            provisionalTeams.agents[i].y += angle[j][1];
            if(outLange(provisionalTeams.agents[i].x, provisionalTeams.agents[i].y)){
                result[j][0] = 1;
            }else{
                if(tile->at(static_cast<unsigned>(provisionalTeams.agents[i].y)-1 )
                        .at(static_cast<unsigned>(provisionalTeams.agents[i].x)-1 ).color == field->TeamColorNumber[0]){
                    ;
                }
                else{
                    result[j][1] += tile->at(static_cast<unsigned>(provisionalTeams.agents[i].y) - 1)
                            .at(static_cast<unsigned>(provisionalTeams.agents[i].x) - 1).point;
                }
                //再帰関数
                result[j][1]+=resurgence(provisionalTeams.agents[i].x,provisionalTeams.agents[i].y,i,3);
            }
        }
        for(int j=0; j<9; ++j){
            //最も点数の高いところ
            if(result[j][0] != 1){
                if(result[j][1] > maxPoint){
                    maxPoint = result[j][1];
                    position = j;
                }
                else if(result[j][1] == maxPoint){
                    if(tile->at(static_cast<unsigned>(teams[myTeam].agents[i].y+angle[j][1]) - 1)
                            .at(static_cast<unsigned>(teams[myTeam].agents[i].x+angle[j][0]) - 1).point>
                       tile->at(static_cast<unsigned>(teams[myTeam].agents[i].y+angle[position][1]) - 1)
                            .at(static_cast<unsigned>(teams[myTeam].agents[i].x+angle[position][0]) - 1).point){
                        position = j;
                    }
                }
            }
        }

        teams[myTeam].agents[i].actions.dx = angle[position][0];
        teams[myTeam].agents[i].actions.dy = angle[position][1];
        x = static_cast<unsigned>(teams[myTeam].agents[i].x) + static_cast<unsigned>(teams[myTeam].agents[i].actions.dx);
        y = static_cast<unsigned>(teams[myTeam].agents[i].y) + static_cast<unsigned>(teams[myTeam].agents[i].actions.dy);
        if(tile->at(y-1).at(x-1).color == field->TeamColorNumber[1]){
            teams[myTeam].agents[i].actions.type = 2; //remove
        }else{
            teams[myTeam].agents[i].actions.type = 1; //move
        }
        if(position == 4){
            teams[myTeam].agents[i].actions.type = 0; // stay
        }
                        cout << "333" << endl;
    }
}

/* ### メインアルゴリズム２再帰 ### */
int Computer::resurgence(int agentX,int agentY,unsigned int agentNumber,int frequency){
    int Color,maxPoint,effect[9][2];
    maxPoint = -999;
    for(int j=0; j<9; ++j){
        effect[j][0]=0;
        effect[j][1]=0;
    }

    Color=tile->at(static_cast<unsigned>(agentY)-1 )
            .at(static_cast<unsigned>(agentX)-1 ).color;
    //仮定の移動タイルを自陣の色に
    tile->at(static_cast<unsigned>(agentY)-1 )
                            .at(static_cast<unsigned>(agentX)-1 ).color=field->TeamColorNumber[0];

    for(int j=0; j<9; ++j){
        provisionalTeams.agents[agentNumber].x = agentX;
        provisionalTeams.agents[agentNumber].y = agentY;
        provisionalTeams.agents[agentNumber].x += angle[j][0];
        provisionalTeams.agents[agentNumber].y += angle[j][1];
        if(outLange(provisionalTeams.agents[agentNumber].x, provisionalTeams.agents[agentNumber].y)){
            effect[j][0] = 1;
        }else{
            if(tile->at(static_cast<unsigned>(provisionalTeams.agents[agentNumber].y)-1 )
                    .at(static_cast<unsigned>(provisionalTeams.agents[agentNumber].x)-1 ).color == field->TeamColorNumber[0]){
                ;
            }
            else{
                effect[j][1] += tile->at(static_cast<unsigned>(provisionalTeams.agents[agentNumber].y)-1 )
                        .at(static_cast<unsigned>(provisionalTeams.agents[agentNumber].x)-1 ).point;
            }
        if(frequency>2)
            effect[j][1]+=resurgence(provisionalTeams.agents[agentNumber].x,provisionalTeams.agents[agentNumber].y,agentNumber,frequency-1);
        }
    }
    for(int j=0; j<9; ++j){
        //最も点数の高いところ
        if(effect[j][0] != 1){
            if(effect[j][1] >= maxPoint){
                maxPoint = effect[j][1];
            }
        }
    }
    //タイルの色を元の色に
    tile->at(static_cast<unsigned>(agentY)-1 )
                            .at(static_cast<unsigned>(agentX)-1 ).color=Color;

    return maxPoint;
}

/* ### agentデータの複製 ### */
void Computer::copy(){
    int myTeam = field->myTeam;
    provisionalTeams.teamID = teams[myTeam].teamID;
    for(unsigned int i=0; i < teams[myTeam].agents.size(); ++i){
        provisionalTeams.agents[i].x = teams[myTeam].agents[i].x;
        provisionalTeams.agents[i].y = teams[myTeam].agents[i].y;
        provisionalTeams.agents[i].agentID = teams[myTeam].agents[i].agentID;
        provisionalTeams.agents[i].actions.dx = teams[myTeam].agents[i].actions.dx;
        provisionalTeams.agents[i].actions.dy = teams[myTeam].agents[i].actions.dy;
        provisionalTeams.agents[i].actions.type = teams[myTeam].agents[i].actions.type;
        provisionalTeams.agents[i].actions.apply = teams[myTeam].agents[i].actions.apply;
    }
}

/* ### agentがfield内にいるか確認 ### */
int Computer::outLange(int x, int y){
    if(x <= 0 || x > field->width || y <= 0 || y > field->height){
        return 1;
    }
    return 0;
}


/* ### メインアルゴリズム１再帰 ### */
/*
int Computer::eightangle(int angle[8][2],int Ax,int Ay,unsigned int AgentNumber,int TURN){

    unsigned int i;
    int maximum=-100,tilepoint=0;
    int teamcolor = teams[0].teamID;
    for(i=0;i<8;i++)
    {
        angle[i][0]+=Ax;
        angle[i][1]+=Ay;
    }

    for(i=0;i<8;i++)
    {
        if(static_cast<int>(teams[0].agents[AgentNumber].x)+angle[i][0]<=static_cast<int>(field->width)&&static_cast<int>(teams[0].agents[AgentNumber].y)+angle[i][1]<=static_cast<int>(field->height)&&static_cast<int>(teams[0].agents[AgentNumber].y)+angle[i][1]-1>=0&&static_cast<int>(teams[0].agents[AgentNumber].x)+angle[i][0]-1>=0)
        {
            if((tile->at(teams[0].agents[AgentNumber].y-1+static_cast<unsigned>(angle[i][1])).at(teams[0].agents[AgentNumber].x-1+static_cast<unsigned>(angle[i][0])).color==teamcolor)||(angle[i][0]-Ax!=Ax&&angle[i][1]-Ay!=Ay))
                tilepoint=-1;
            else
                tilepoint=tile->at(teams[0].agents[AgentNumber].y-1+static_cast<unsigned>(angle[i][1])).at(teams[0].agents[AgentNumber].x-1+static_cast<unsigned>(angle[i][0])).point;
            TURN--;
            if(TURN>1)
                tilepoint+=eightangle(angle,angle[i][0]-Ax,angle[i][1]-Ay,AgentNumber,TURN);
        if(tilepoint>maximum)
            maximum=tilepoint;
        }
    }

    for(i=0;i<8;i++){
        angle[i][0]-=Ax;
        angle[i][1]-=Ay;
    }
    return maximum;
}
*/
