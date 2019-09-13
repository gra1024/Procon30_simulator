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
}

void Computer::startAlgo(int AlgoNumber){
    switch(AlgoNumber){
    case 1:
        greedy();
        break;
    case 2:
        ;
    }
}
void Computer::greedy(){
    unsigned int i,j;
    int angle[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
    int maximum=-100,tilepoint=0,teamcolor;
    teamcolor = teams[field->myTeam].teamID;

    cout<<teams[field->myTeam].agents[0].x<<"|"<<teams[field->myTeam].agents[0].y<<endl;
    cout<<teams[field->myTeam].agents[1].x<<"|"<<teams[field->myTeam].agents[1].y<<endl;
    for(j=0;j<teams->agents.size();j++)
    {
        maximum=-100;
        for(i=0;i<8;i++)
        {
            if(static_cast<int>(teams[field->myTeam].agents[j].x)+angle[i][0]<=static_cast<int>(field->width)&&static_cast<int>(teams[field->myTeam].agents[j].y)+angle[i][1]<=static_cast<int>(field->height)&&static_cast<int>(teams[field->myTeam].agents[j].y)+angle[i][1]-1>=0&&static_cast<int>(teams[field->myTeam].agents[j].x)+angle[i][0]-1>=0)
            {

                if(tile->at(static_cast<unsigned>(teams[field->myTeam].agents[j].y+angle[i][1]-1)).at(static_cast<unsigned>(teams[field->myTeam].agents[j].x+angle[i][0])-1).color==teamcolor)
                    tilepoint=-1;
                else
                    tilepoint=tile->at(static_cast<unsigned>(teams[field->myTeam].agents[j].y+angle[i][1])-1).at(static_cast<unsigned>(teams[field->myTeam].agents[j].x+angle[i][0])-1).point;
                tilepoint+=eightangle(angle,angle[i][0],angle[i][1],j,3);//3手先

                if(tilepoint>maximum)
                {
                    maximum=tilepoint;
                    teams[field->myTeam].agents[j].actions.dx=angle[i][0];
                    teams[field->myTeam].agents[j].actions.dy=angle[i][1];
                    if(tile->at(static_cast<unsigned>(teams[0].agents[j].y)+static_cast<unsigned>(teams[field->myTeam].agents[j].actions.dy)-1).at(static_cast<unsigned>(teams[field->myTeam].agents[j].x)+static_cast<unsigned>(teams[field->myTeam].agents[j].actions.dx)-1).color==teamcolor||tile->at(static_cast<unsigned>(teams[field->myTeam].agents[j].y)+static_cast<unsigned>(teams[field->myTeam].agents[j].actions.dy)-1).at(static_cast<unsigned>(teams[field->myTeam].agents[j].x)+static_cast<unsigned>(teams[field->myTeam].agents[j].actions.dx)-1).color==WHITE)
                        teams[field->myTeam].agents[j].actions.type=1;
                    else
                        teams[field->myTeam].agents[j].actions.type=2;
                }
            }
        }
    }
}

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
        if(static_cast<int>(teams[field->myTeam].agents[AgentNumber].x)+angle[i][0]<=static_cast<int>(field->width)&&static_cast<int>(teams[field->myTeam].agents[AgentNumber].y)+angle[i][1]<=static_cast<int>(field->height)&&static_cast<int>(teams[field->myTeam].agents[AgentNumber].y)+angle[i][1]-1>=0&&static_cast<int>(teams[field->myTeam].agents[AgentNumber].x)+angle[i][0]-1>=0)
        {
            if((tile->at(static_cast<unsigned>(teams[field->myTeam].agents[AgentNumber].y)-1+static_cast<unsigned>(angle[i][1])).at(static_cast<unsigned>(teams[field->myTeam].agents[AgentNumber].x)-1+static_cast<unsigned>(angle[i][0])).color==teamcolor)||(angle[i][0]-Ax!=Ax&&angle[i][1]-Ay!=Ay))
                tilepoint=-1;
            else
                tilepoint=tile->at(static_cast<unsigned>(teams[field->myTeam].agents[AgentNumber].y)-1+static_cast<unsigned>(angle[i][1])).at(static_cast<unsigned>(teams[field->myTeam].agents[AgentNumber].x)-1+static_cast<unsigned>(angle[i][0])).point;
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
