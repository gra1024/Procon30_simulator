#include "Computer.h"

Computer::Computer(Ui::MainWindow *uiMainWindow):
        uiMainWindow(uiMainWindow)
{

}

Computer::~Computer()
{

}


void Computer::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field){
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

void Computer::startAlgo(int AlgoNumber){
    copy();
    switch(AlgoNumber){
    case 0:
        greedy();
        break;
    case 1:
        ;
    }

}
void Computer::greedy(){
    /*
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
    */
}

void Computer::greedy2(){
    /*
    int color = field->TeamColorNumber[0];
    int myTeam = field->myTeam;
    for(unsigned int i=0; i < teams[myTeam].agents.size(); ++i){
        for(int j=0; j<9; ++j){
            provisionalTeams.agents[i].x = teams[myTeam].agents[i].x;
            provisionalTeams.agents[i].y = teams[myTeam].agents[i].y;
            provisionalTeams.agents[i].x += angle[j][0];
            provisionalTeams.agents[i].y += angle[j][1];
            if(outLange(provisionalTeams.agents[i].x, provisionalTeams.agents[i].y)){
                result[j][0] = 1;
            }else{
                result[j][1] = tile->at(provisionalTeams.agents[i].y).at(provisionalTeams.agents[i].x).point;
            }
        }
    }
    */
}

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

int Computer::outLange(int x, int y){
    if(x <= 0 || x > field->width || y <= 0 || y > field->height){
        return 1;
    }
    return 0;
}

int Computer::eightangle(int angle[8][2],int Ax,int Ay,unsigned int AgentNumber,int TURN){
    /*
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
    */
}
