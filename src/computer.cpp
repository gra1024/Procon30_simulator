#include "Computer.h"

Computer::Computer(Ui::MainWindow *uiMainWindow):
        uiMainWindow(uiMainWindow)
{

}

Computer::~Computer()
{

}


void Computer::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field,Actions *action){
    this->tile = tile;
    this->teams = teams;
    this->field = field;
    this->action = action;
}

void Computer::startAlgo(int AlgoNumber){
    switch(AlgoNumber){
    case 0:
        greedy();
        break;
    case 1:
        ;
    }

}
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
                    action->dx=-1+angle[i][0];
                    action->dy=-1+angle[i][1];
                    if(tile->at(teams[0].agents[j].y+static_cast<unsigned>(action->dy)).at(teams[0].agents[j].x+static_cast<unsigned>(action->dx)).color==teamcolor||tile->at(teams[0].agents[j].y+static_cast<unsigned>(action->dy)).at(teams[0].agents[j].x+static_cast<unsigned>(action->dx)).color==WHITE)
                        action->type=1;
                    else
                        action->type=2;
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
