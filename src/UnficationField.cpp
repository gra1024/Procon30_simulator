#include "UnficationField.h"

UnficationField::UnficationField()
{

}

UnficationField::~UnficationField()
{

}

void UnficationField::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field){
    this->tile = tile;
    this->teams = teams;
    this->field = field;
}

void UnficationField::start(){
    load(0,"");
    load(1,"");
    provisionalMove();
    check();
    move();
}

string UnficationField::load(int teamNum, string path){
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        return "ERROR --UnficationField::load-- ";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();

    QJsonArray arrTeams = obj["actions"].toArray();

    for(unsigned int j=0;j<static_cast<unsigned>(arrTeams.at(teamNum).toObject().size());++j){

        string str = arrTeams.at(teamNum).toObject().value("type").toString().toStdString();
        if(str=="move") teams[teamNum].agents[j].actions.type = 1;
        else if(str=="remove") teams[teamNum].agents[j].actions.type = 2;
        else if(str=="stay") teams[teamNum].agents[j].actions.type = 0;
        else teams[teamNum].agents[j].actions.type = -1;

        teams[teamNum].agents[j].actions.dx= arrTeams.at(teamNum).toObject().value("dx").toInt();
        teams[teamNum].agents[j].actions.dy= arrTeams.at(teamNum).toObject().value("dy").toInt();
        teams[teamNum].agents[j].actions.check=0;
    }
    file.close();
    return "";
}

void UnficationField::provisionalMove(){
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            provisionalTeams[i].agents[j].x+=static_cast<unsigned>(teams[i].agents[j].actions.dx);
            provisionalTeams[i].agents[j].y+=static_cast<unsigned>(teams[i].agents[j].actions.dy);
        }
    }
}

void UnficationField::check(){
    unsigned int x,y;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            x = provisionalTeams[i].agents[j].x;
            y = provisionalTeams[i].agents[j].y;
            for(unsigned int k=0;k<(teams[i].agents.size());++k){
                if(j!=k){
                    if(x==provisionalTeams[i].agents[k].x && y==provisionalTeams[i].agents[k].y){
                        teams[i].agents[j].actions.check=1;
                        break;
                    }
                }
            }
        }
    }
}

void UnficationField::move(){
    int dx,dy;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            dx = teams[i].agents[j].actions.dx;
            dy = teams[i].agents[j].actions.dy;
            if(teams[i].agents[j].actions.check==0){
                if(teams[i].agents[j].actions.type==1){
                    teams[i].agents[j].x+=static_cast<unsigned>(dx);
                    teams[i].agents[j].y+=static_cast<unsigned>(dy);//unsignedがやらかすかも
                    tile->at(teams[i].agents[j].y).at(teams[i].agents[j].x).color=teams[i].teamID;
                }else if(teams[i].agents[j].actions.type==2){
                    tile->at(teams[i].agents[j].y+static_cast<unsigned>(dy)).at(teams[i].agents[j].x+static_cast<unsigned>(dx)).color=WHITE;
                }else{

                }
                if(dx==1)provisionalTeams[i].agents[j].x++;
                else if(dx==-1)provisionalTeams[i].agents[j].x--;
                if(dy==1)provisionalTeams[i].agents[j].x++;
                else if(dy==-1)provisionalTeams[i].agents[j].y--;
            }
        }
    }
}

void UnficationField::debug(){

}
