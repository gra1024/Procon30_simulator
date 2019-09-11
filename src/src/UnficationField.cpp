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

    for(unsigned int j=0;j<static_cast<unsigned>(arrTeams.at(teamNum).toObject().size());++j){
        string str = arrTeams.at(teamNum).toObject().value("type").toString().toStdString();
        if(str=="move") teams[teamNum].agents[j].actions.type = 1;
        else if(str=="remove") teams[teamNum].agents[j].actions.type = 2;
        else if(str=="stay") teams[teamNum].agents[j].actions.type = 0;
        else teams[teamNum].agents[j].actions.type = -1;

        teams[teamNum].agents[j].actions.dx = arrTeams.at(teamNum).toObject().value("dx").toInt();
        teams[teamNum].agents[j].actions.dy = arrTeams.at(teamNum).toObject().value("dy").toInt();
        teams[teamNum].agents[j].actions.apply=1;
        cout << arrTeams.at(teamNum).toObject().value("dx").toInt() << endl;
    }
    file.close();
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
    int agentID_int;
    QString type_string;
    int dx_int;
    int dy_int;
    int turn_int;
    int apply_int;
    QJsonArray points_array_min,points_array_mid;
    QJsonArray color_array_min,color_array_mid;
    QJsonArray jsonarr;
    QJsonObject actions_obj;
    vector<QJsonObject> actions_vector;
    QJsonObject all_obj;
    all_obj["width"]=field->width;
    all_obj["height"]=field->height;
    for (unsigned int i=0;i<20;i++) {
        for (unsigned int j=0;j<20;j++) {
            points_array_min.push_back(tile->at(i).at(j).point);
        }
        points_array_mid.push_back(points_array_min[static_cast<int>(i)]);
    }
    all_obj["points"]=points_array_mid;
    all_obj["startedAtUnixTime"]=field->startedAtUnixTime;
    all_obj["turn"]=field->turn;
    for (unsigned int i=0;i<20;i++) {
        for (unsigned int j=0;j<20;j++) {
            color_array_min.push_back(tile->at(i).at(j).color);
        }
        color_array_mid.push_back(color_array_min[static_cast<int>(i)]);
    }
    all_obj["tiled"]=color_array_mid;

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
    all_obj["actions"]=jsonarr;
    QJsonDocument jsonDoc(all_obj);
    //json形式
    QByteArray data(jsonDoc.toJson());
    QFile savefile("..\\data\\actions.json");
    savefile.open(QIODevice::WriteOnly);
    savefile.write(data);
    savefile.close();
}

void UnficationField::debug(){

}
