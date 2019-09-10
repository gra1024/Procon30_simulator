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
    cout << "setup UnificationField" << endl;
}

void UnficationField::start(){
    load(0,CONFIG_PATH_OF_AGENT_TXT_1);
    load(1,CONFIG_PATH_OF_AGENT_TXT_2);
    provisionalMove();
    while(1){
        if(check()) break;

    }
    move();
    encode();
}

string UnficationField::load(int teamNum, string path){
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        cout << "ERROR --UnficationField::load-- " << endl;
        return "ERROR";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();

    QJsonArray arrTeams = obj["actions"].toArray();

    for(int j=0;j<arrTeams.size();++j){
        string str = arrTeams.at(j).toObject().value("type").toString().toStdString();
        if(str=="move") teams[teamNum].agents[static_cast<unsigned>(j)].actions.type = 1;
        else if(str=="remove") teams[teamNum].agents[static_cast<unsigned>(j)].actions.type = 2;
        else if(str=="stay") teams[teamNum].agents[static_cast<unsigned>(j)].actions.type = 0;
        else teams[teamNum].agents[static_cast<unsigned>(j)].actions.type = -1;

        teams[teamNum].agents[static_cast<unsigned>(j)].actions.dx = arrTeams.at(j).toObject().value("dx").toInt();
        teams[teamNum].agents[static_cast<unsigned>(j)].actions.dy = arrTeams.at(j).toObject().value("dy").toInt();
        teams[teamNum].agents[static_cast<unsigned>(j)].actions.apply=1;
    }
    file.close();
    debug();
    return "";
}

void UnficationField::provisionalMove(){
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            provisionalTeams[i].agents[j].x += teams[i].agents[j].actions.dx;
            provisionalTeams[i].agents[j].y+=teams[i].agents[j].actions.dy;

            if((provisionalTeams[i].agents[j].x<0 && provisionalTeams[i].agents[j].x>=field->width)
                    &&(provisionalTeams[i].agents[j].y<0 && provisionalTeams[i].agents[j].y>=field->height)){
                provisionalTeams[i].agents[j].x -= teams[i].agents[j].actions.dx;
                provisionalTeams[i].agents[j].y -= teams[i].agents[j].actions.dy;
                teams[i].agents[j].actions.apply=-1;
            }
        }
    }
}

int UnficationField::check(){
    int x,y;
    int check = 0;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){

            if(teams[i].agents[j].actions.apply!=-1){
                x = provisionalTeams[i].agents[j].x;
                y = provisionalTeams[i].agents[j].y;

                for(unsigned int k=0;k<(teams[i].agents.size());++k){

                    if(teams[i].agents[k].actions.apply!=-1){
                        if(j!=k){
                            if(x==provisionalTeams[i].agents[k].x && y==provisionalTeams[i].agents[k].y){
                                provisionalTeams[i].agents[k].x -= teams[i].agents[j].actions.dx;
                                provisionalTeams[i].agents[k].y -= teams[i].agents[j].actions.dy;
                                teams[i].agents[j].actions.apply = 0;
                                check=1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return check;
}

void UnficationField::move(){
    int dx,dy;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            dx = teams[i].agents[j].actions.dx;
            dy = teams[i].agents[j].actions.dy;
            if(teams[i].agents[j].actions.apply==1){
                if(teams[i].agents[j].actions.type==1){
                    teams[i].agents[j].x+=dx;
                    teams[i].agents[j].y+=dy;
                    tile->at(static_cast<unsigned>(teams[i].agents[j].y)).at(static_cast<unsigned>(teams[i].agents[j].x)).color
                            =teams[i].teamID;
                }else if(teams[i].agents[j].actions.type==2){
                    tile->at(static_cast<unsigned>(teams[i].agents[j].y+dy)).at(static_cast<unsigned>(teams[i].agents[j].x+dx)).color
                            =WHITE;
                }
            }
        }
    }
}

void UnficationField::encode(){
}

void UnficationField::debug(){
    cout << "///////////////////////Debug////////////////////////////" << endl;
    cout<<"turn"<<field->turn<<endl;
    cout<<"width"<<field->width<<endl;
    cout<<"height"<<field->height<<endl;
    cout<<"sut"<<field->startedAtUnixTime<<endl;
    cout<<"color"<<endl;
    for(int y=0; y<field->height; ++y){
        for(int x=0; x<field->width; ++x){
            cout<<tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color;
        }
        cout<<endl;
    }
    cout<<"point"<<endl;
    for(int y=0; y<field->height; ++y){

        for(int x=0; x<field->width; ++x){
            cout<< tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).point;
        }
        cout<<endl;
    }
    for(int i=0;i<2;++i){
        cout<<"teamID["<<i<<"] "<< teams[i].teamID<<endl;
        for(unsigned int j=0; j<teams->agents.size();++j){
            cout<<"agent["<<i<<"]["<<j<<"] "<< " "<<teams[i].agents[j].agentID <<" "<< teams[i].agents[j].x<<" " << teams[i].agents[j].y<<endl;
        }
    }
    cout << "/////////////////////////////////////////////////////////////////" << endl;
 }
