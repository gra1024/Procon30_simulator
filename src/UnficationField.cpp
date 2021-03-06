#include "UnficationField.h"

UnficationField::UnficationField()
{

}

UnficationField::~UnficationField()
{

}

/*### 初期設定 ###*/
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
    cout << "setup UnificationField" << endl;;
}


/* ### アルゴリズムの選択 ### */
void UnficationField::start(){
    missedMovePos.clear();
    load(0,CONFIG_PATH_OF_FILE_INPUT_ACTIONS_1_BY_GAMEMASTER);
    load(1,CONFIG_PATH_OF_FILE_INPUT_ACTIONS_2_BY_GAMEMASTER);
    //debug();
    copy();
    provisionalMove();
    while(1){
        if(check()==0) break;
    }
    move();
    field->turn++;
    encode(CONFIG_PATH_OF_FILE_OUTPUT_FIELD_BY_GAMEMASTER);
}

/* ### エージェントのアクション情報のロード、デコード ### */
string UnficationField::load(int teamNum, string path){
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        cout << "ERROR --UnficationField::load--" << endl;
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

/* ### teamsの内容をprovisionalTeamsへコピー ### */
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

/* ### 仮移動 ## */
void UnficationField::provisionalMove(){
    for(int i=0;i<2;++i){
        for(unsigned int j = 0; j < teams[i].agents.size(); ++j){
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

/* ### 行動が競合していないかの判断 ### */
int UnficationField::check(){
    int x, y, x2=0, y2=0;
    int check = 0, check2 = 0;
    for(int i=0;i<2;++i){
        for(unsigned int j=0;j< teams[i].agents.size(); ++j){
            if(teams[i].agents[j].actions.apply == 1){
                x = provisionalTeams[i].agents[j].x;
                y = provisionalTeams[i].agents[j].y;

                /* removeなら元居た場所をmissリストに追加 */
                if(tile->at(static_cast<unsigned>(y)-1).at(static_cast<unsigned>(x)-1).color == field->TeamColorNumber[1]){
                    Pos pos;
                    pos.x = provisionalTeams[i].agents[j].x - teams[i].agents[j].actions.dx;
                    pos.y = provisionalTeams[i].agents[j].y - teams[i].agents[j].actions.dy;
                    missedMovePos.push_back(pos);
                }

                for (int i2 = 0; i2 < 2; ++i2){
                    for(unsigned int j2 = 0; j2 < teams[i2].agents.size() + missedMovePos.size(); ++j2){
                        if(!(i == i2 && j == j2)){//同じエージェントではない
                            if(j2 < teams[i2].agents.size()){
                                x2 = provisionalTeams[i2].agents[j2].x;
                                y2 = provisionalTeams[i2].agents[j2].y;
                            }else{
                                x2 = missedMovePos[j2 - teams[i2].agents.size()].x;
                                y2 = missedMovePos[j2 - teams[i2].agents.size()].y;
                            }
                            if(x == x2 && y == y2){ //被っていたなら
                                Pos pos;
                                pos.x = provisionalTeams[i].agents[j].x;
                                pos.y = provisionalTeams[i].agents[j].y;
                                missedMovePos.push_back(pos);
                                provisionalTeams[i].agents[j].x -= teams[i].agents[j].actions.dx;
                                provisionalTeams[i].agents[j].y -= teams[i].agents[j].actions.dy;
                                teams[i].agents[j].actions.apply = 0;
                                check = 1;
                                check2 = 1;
                                break;
                            }
                        }
                    }
                    if(check2 == 1){
                        check2 = 0;
                        break;
                    }
                }
            }
        }
    }
    return check;
}

/* ### エージェントの移動の操作 ### */
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

/* ### フィールド情報のエンコード ### */
void UnficationField::encode(string path){
    QJsonArray Points;
    vector<QJsonArray> points_array_mid;
    for (unsigned int i=0;i<static_cast<unsigned int>(field->height);i++) {
        QJsonArray points_array_min;
        for (unsigned int j=0;j<static_cast<unsigned int>(field->width);j++) {
            /*QJsonArray instant;
            instant.append(tile->at(i).at(j).point);
            points_array_min.push_back(instant);*/
            points_array_min.append(tile->at(i).at(j).point);
        }
        points_array_mid.push_back(points_array_min);
    }
    for(auto name:points_array_mid)
    {
        Points.append(name);
    } // points

    vector<QJsonArray> color_array_mid;
    QJsonArray Color;
    for (unsigned int i=0;i<static_cast<unsigned int>(field->height);i++) {
        QJsonArray color_array_min;
        for (unsigned int j=0;j<static_cast<unsigned int>(field->width);j++) {
            color_array_min.push_back(tile->at(i).at(j).color);
        }
        color_array_mid.push_back(color_array_min);
    }
    for(auto name:color_array_mid)
    {
        Color.append(name);
    } // tiled

    QJsonArray teamsQJA;
    for (unsigned int i=0;i<2;i++) {
        QJsonObject teamsObj;
        QJsonArray agentsArr;
        teamsObj["teamID"]=teams[i].teamID;
        for(unsigned int j=0;j<teams[0].agents.size();j++){
            QJsonObject agentsObj;
            agentsObj["agentID"]=teams[i].agents[j].agentID;
            agentsObj["x"]=teams[i].agents[j].x;
            agentsObj["y"]=teams[i].agents[j].y;
            agentsArr.append(agentsObj);
        }
        teamsObj["agents"]=agentsArr;
        teamsObj["tilePoint"]=teams[i].tilePoint;
        teamsObj["areaPoint"]=teams[i].areaPoint;
        teamsQJA.append(teamsObj);
    } // teams

    QJsonArray jsonarr;
    vector<QJsonObject> actions_vector;
    int agentID_int;
    QString type_string;
    int dx_int, dy_int, turn_int, apply_int;
    for (unsigned int i=0;i<2;i++){
        for (unsigned int j=0;j<teams[0].agents.size();j++) {
            agentID_int = teams[i].agents[j].agentID;
            switch (teams[i].agents[j].actions.type) {
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
            dx_int=teams[i].agents[j].actions.dx;
            dy_int=teams[i].agents[j].actions.dy;
            turn_int=field->turn;
            apply_int=teams[i].agents[j].actions.apply;
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
    }
    for(auto name:actions_vector)
    {
        jsonarr.append(name);
    } // actions

    QJsonObject all_obj;
    all_obj["width"] = field->width;
    all_obj["height"] = field->height;
    all_obj["points"] = Points;
    all_obj["startedAtUnixTime"] = field->startedAtUnixTime;
    all_obj["turn"] = field->turn;
    all_obj["tiled"] = Color;
    all_obj["teams"] = teamsQJA;
    all_obj["actions"]=jsonarr;

    QJsonDocument jsonDoc(all_obj);
    QByteArray data(jsonDoc.toJson());
    QFile savefile(QString::fromStdString(path));
    savefile.open(QIODevice::WriteOnly);
    savefile.write(data);
    savefile.close();

}

/* ### アプリケーション出力 ### */
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

