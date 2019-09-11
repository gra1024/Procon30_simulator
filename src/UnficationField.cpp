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
    for(int i=0;i<2;++i){
        provisionalTeams[i].teamID = 0;
        for(unsigned int j=0;j<teams[i].agents.size();++j){
            Agent agentLine;
            agentLine.x = 0;
            agentLine.y = 0;
            agentLine.agentID = 0;
            agentLine.actions.dx = 0;
            agentLine.actions.dy = 0;
            agentLine.actions.type = 0;
            agentLine.actions.apply = 0;
            provisionalTeams[i].agents.push_back(agentLine);
        }
    }
    cout << "setup UnificationField" << endl;
}

void UnficationField::start(){
    load(0,CONFIG_PATH_OF_AGENT_TXT_1);
    load(1,CONFIG_PATH_OF_AGENT_TXT_2);
    debug();
    copy();
    provisionalMove();
    while(1){
        if(check()==0) break;
    }
        cout << "1234567890" << endl;
    move();
    cout << "34567890-" << endl;
    encode(CONFIG_PATH_OF_FIELD_JSON);
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
    return "";
}

void UnficationField::copy(){
    for(int i=0;i<2;++i){
        provisionalTeams[i].teamID = teams[i].teamID;
        for(unsigned int j=0;j<teams[i].agents.size();++j){
            provisionalTeams[i].agents[j].x = teams[i].agents[j].x;
            provisionalTeams[i].agents[j].y = teams[i].agents[j].y;
            provisionalTeams[i].agents[j].agentID = teams[i].agents[j].agentID;
            provisionalTeams[i].agents[j].actions.dx = teams[i].agents[j].actions.dx;
            provisionalTeams[i].agents[j].actions.dy = teams[i].agents[j].actions.dy;
            provisionalTeams[i].agents[j].actions.type = teams[i].agents[j].actions.type;
            provisionalTeams[i].agents[j].actions.apply = teams[i].agents[j].actions.apply;
        }
    }
}

void UnficationField::provisionalMove(){
    for(int i=0;i<2;++i){
        for(unsigned int j = 0; j < (teams[i].agents.size()); ++j){
            provisionalTeams[i].agents[j].x += teams[i].agents[j].actions.dx;
            provisionalTeams[i].agents[j].y += teams[i].agents[j].actions.dy;
            if(provisionalTeams[i].agents[j].x <= 0
                    || provisionalTeams[i].agents[j].x > field->width
                    || provisionalTeams[i].agents[j].y <= 0
                    || provisionalTeams[i].agents[j].y > field->height){ //if(枠外にエージェントがいたら)
                provisionalTeams[i].agents[j].x -= teams[i].agents[j].actions.dx;
                provisionalTeams[i].agents[j].y -= teams[i].agents[j].actions.dy;
                teams[i].agents[j].actions.apply = -1;
            }
        }
    }
}

int UnficationField::check(){
    int x, y;
    int check = 0;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j<(teams[i].agents.size());++j){
            if(teams[i].agents[j].actions.apply != -1){
                x = provisionalTeams[i].agents[j].x;
                y = provisionalTeams[i].agents[j].y;
                for(unsigned int k=0; k < teams[i].agents.size(); ++k){
                    if(j != k){
                        if(x == provisionalTeams[i].agents[k].x && y == provisionalTeams[i].agents[k].y){
                            provisionalTeams[i].agents[k].x -= teams[i].agents[j].actions.dx;
                            provisionalTeams[i].agents[k].y -= teams[i].agents[j].actions.dy;
                            teams[i].agents[j].actions.apply = 0;
                            check = 1;
                            break;
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
    for(int i=0; i<2; ++i){
        for(unsigned int j=0; j < teams[i].agents.size(); ++j){
            dx = teams[i].agents[j].actions.dx;
            dy = teams[i].agents[j].actions.dy;
            if(teams[i].agents[j].actions.apply == 1){ //apply==1
                if(teams[i].agents[j].actions.type == 1){ //move
                    teams[i].agents[j].x += dx;
                    teams[i].agents[j].y += dy;
                    cout << teams[i].agents[j].y << " "<< teams[i].agents[j].x << endl;
                    tile->at(static_cast<unsigned>(teams[i].agents[j].y) - 1).at(static_cast<unsigned>(teams[i].agents[j].x) - 1).color
                            =teams[i].teamID;
                }else if(teams[i].agents[j].actions.type==2){ //remove
                    tile->at(static_cast<unsigned>(teams[i].agents[j].y+dy)-1).at(static_cast<unsigned>(teams[i].agents[j].x+dx)-1).color
                            =WHITE;
                }else{ //stay

                }
            }
        }
    }
}

void UnficationField::encode(string path){
    int agentID_int;
    QString type_string;
    int dx_int;
    int dy_int;
    int turn_int;
    int apply_int;
    QJsonArray jsonarr;
    QJsonObject actions_obj;
    vector<QJsonObject> actions_vector;
    for (unsigned int i=0;i<teams[0].agents.size();i++) {
        agentID_int = teams[0].agents[i].agentID;
        switch (teams[0].agents[i].actions.type) {
        case 0 :
            type_string="stay";
            break;
        case 1:
            type_string="move";
            break;
        case 2 :
            type_string="remove";
            break;
        }
        dx_int=teams[0].agents[i].actions.dx;
        dy_int=teams[0].agents[i].actions.dy;
        turn_int=field->turn+1;
        apply_int=teams[0].agents[i].actions.apply;
        QJsonObject agent_obj={
            {"agentID",agentID_int},
            {"type",type_string},
            {"dx",dx_int},
            {"dy",dy_int},
            {"turn",turn_int},
            {"apply",apply_int}
        };
        actions_vector.push_back(agent_obj);
    }
    for(auto name:actions_vector)
    {
        jsonarr.append(name);
    }
    actions_obj["actions"]=jsonarr;
    QJsonDocument jsonDoc(actions_obj);
    //json形式
    QByteArray data(jsonDoc.toJson());
    QFile savefile(QString::fromStdString(path));
    savefile.open(QIODevice::WriteOnly);
    savefile.write(data);
    savefile.close();
}

void UnficationField::debug(){
    cout << "//////////Debug UF//////////" << endl;
    cout<<"teamID[i][j] agentID x y dx dy type apply "<< endl;
    for(int i=0;i<2;++i){
        cout<<"teamID["<<i<<"] "<< teams[i].teamID<<endl;
        for(unsigned int j=0; j<teams->agents.size();++j){
            cout<<"agent["<<i<<"]["<<j<<"] "<< " "<<
                  teams[i].agents[j].agentID <<" "<< teams[i].agents[j].x<<" " << teams[i].agents[j].y<< " "<<
                  teams[i].agents[j].actions.dx<< " "<<teams[i].agents[j].actions.dy<< " "<<
                  teams[i].agents[j].actions.type<< " "<<teams[i].agents[j].actions.apply<< endl;
        }
    }
    cout << "/////////////////////////////" << endl;
}
