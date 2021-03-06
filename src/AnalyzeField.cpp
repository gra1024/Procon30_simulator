#include "AnalyzeField.h"
#include "ui_AnalyzeField.h"

AnalyzeField::AnalyzeField(int uiNum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeField)
{
    ui->setupUi(this);
    string title = "Field";
    title += to_string(uiNum);
    this->setWindowTitle(QString::fromStdString(title));
}

AnalyzeField::~AnalyzeField()
{
    delete ui;
}

/* ### 初期設定 ### */
void AnalyzeField::setup(Ui::MainWindow *uiMainWindow, vector<vector<Tile>> *tile, Teams *teams, Field *field, Network *network)
{
    this->uiMainWindow = uiMainWindow;
    this->tile = tile;
    this->teams = teams;
    this->field = field;
    this->network = network;
    tile->clear();
    teams->agents.clear();
    decodeAndSet(CONFIG_PATH_OF_FILE_INPUT_FIELD_BY_PLAYER);
    setUi();
    field->maxTurn = this->uiMainWindow->spinBox_maxTurn->value();
    //debug();
}

/* ### pushreloadを押した時にデコードを行う ### */
void AnalyzeField::pushReload(){
    decodeAndUpdate(CONFIG_PATH_OF_FILE_INPUT_FIELD_BY_PLAYER);
}

/* ### 初期設定 ### */
void AnalyzeField::setUi()
{
    mag = CONFIG_MAGNIFICATION_OF_FIELD/100*50;
    setFixedSize(QSize(mag*field->width + 1, mag*field->height+ 1));
    show();
}

/* ### マップ表示 ### */
void AnalyzeField::drow(){
    drowField();
    repaint();
}

/* ### 取得した全情報をデコード ### */
string AnalyzeField::decodeAndSet(string path){
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        return "ERROR --decodeAndSet-- ";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();
    if(uiMainWindow->checkBox_player->checkState() == 0 && uiMainWindow->checkBox_gameMaster->checkState() == 0){
        obj = network->matchReply;
    }

    field->width = obj["width"].toInt();
    field->height = obj["height"].toInt();
    field->startedAtUnixTime = obj["startedAtUnixTime"].toInt();
    field->turn = obj["turn"].toInt();

    QJsonArray arrPoints = obj["points"].toArray();
    QJsonArray arrTiled = obj["tiled"].toArray();
    QJsonArray arrTeams = obj["teams"].toArray();

    for (int i=0;i<static_cast<int>(field->height);i++) {
        vector<Tile> tileline;
        for(int j=0;j<static_cast<int>(field->width);j++){
            Tile tileData;
            tileData.point=arrPoints.at(i).toArray().at(j).toInt();
            tileData.color=arrTiled.at(i).toArray().at(j).toInt();
            tileline.push_back(tileData);
            field->fieldPoint.totalPoint += tileData.point;
            if(tileData.point > 0){
                field->fieldPoint.positiveTile++;
            }
            else if (tileData.point < 0){
                field->fieldPoint.negativeTile++;
                field->fieldPoint.negativePoint += tileData.point;
            }
        }
        tile->push_back(tileline);
    }
    field->fieldPoint.averagePoint = field->fieldPoint.totalPoint / (field->width * field->height);
    field->fieldPoint.averageNegativePoint = field->fieldPoint.totalPoint / (field->fieldPoint.negativeTile + 1);

    for(int i=0;i<2;++i){
        teams[i].teamID = arrTeams.at(i).toObject().value("teamID").toInt();
        for(int j=0;j<arrTeams.at(i).toObject().value("agents").toArray().size();++j){
            Agent agentData;
            agentData.agentID = arrTeams.at(i).toObject().value("agents").toArray().at(j).toObject().value("agentID").toInt();
            agentData.x = arrTeams.at(i).toObject().value("agents").toArray().at(j).toObject().value("x").toInt();
            agentData.y = arrTeams.at(i).toObject().value("agents").toArray().at(j).toObject().value("y").toInt();
            teams[i].agents.push_back(agentData);
        }
    }

    // 後で手直し
    if(uiMainWindow->spinBox_teamID->value() == teams[0].teamID){
        field->TeamColorNumber[0] = teams[0].teamID;
        field->TeamColorNumber[1] = teams[1].teamID;
    }else if(uiMainWindow->spinBox_teamID->value() == teams[1].teamID){
        field->TeamColorNumber[0] = teams[1].teamID;
        field->TeamColorNumber[1] = teams[0].teamID;
    }else{
        cout<<"ERROR --please set teamID--" << endl;
    }

    if(field->TeamColorNumber[0] == teams[0].teamID){
        field->myTeam = 0;
    }else{
        field->myTeam = 1;
    }

    if((uiMainWindow->comboBox_teamColor->currentText()=="Red"
        && uiMainWindow->spinBox_teamID->value() == teams[0].teamID)
            || (uiMainWindow->comboBox_teamColor->currentText()=="Blue"
                && uiMainWindow->spinBox_teamID->value() == teams[1].teamID)){
        red = teams[0].teamID;
        blue = teams[1].teamID;
        colorPattern = 0;
    }else if((uiMainWindow->comboBox_teamColor->currentText()=="Red"
              && uiMainWindow->spinBox_teamID->value() == teams[1].teamID)
                  || (uiMainWindow->comboBox_teamColor->currentText()=="Blue"
                      && uiMainWindow->spinBox_teamID->value() == teams[0].teamID)){
        red = teams[1].teamID;
        blue = teams[0].teamID;
        colorPattern = 1;
    }else{
        cout<<"error"<<endl;
    }

    file.close();
    return "";
}

/* ###　フィールド情報をデコードし、盤面の内部情報を更新する ### */
string AnalyzeField::decodeAndUpdate(string path){
    QFile file(QString::fromStdString(path));
    if (! file.open(QFile::ReadOnly)) {
        return "ERROR --decoadAndUpdate--";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();
    if(uiMainWindow->checkBox_player->checkState() == 0 && uiMainWindow->checkBox_gameMaster->checkState() == 0){
        obj = network->matchReply;
    }

    QJsonArray arrTiled = obj["tiled"].toArray();
    QJsonArray arrTeams = obj["teams"].toArray();

    for (int i=0;i<field->height;i++) {
        for(int j=0;j<field->width;j++){
            tile->at(static_cast<unsigned>(i)).at(static_cast<unsigned>(j)).color=arrTiled.at(i).toArray().at(j).toInt();
        }
    }

    for(int i=0;i<2;++i){
        for(int j=0;j<arrTeams.at(i).toObject().value("agents").toArray().size();++j){
            teams[i].agents[static_cast<unsigned>(j)].x
                    = arrTeams.at(i).toObject().value("agents").toArray().at(j).toObject().value("x").toInt();
            teams[i].agents[static_cast<unsigned>(j)].y
                    = arrTeams.at(i).toObject().value("agents").toArray().at(j).toObject().value("y").toInt();
        }
    }
    field->turn = obj["turn"].toInt();
    file.close();
    return "";
}

/* ### 現在のフィールドを描画する ### */
void AnalyzeField::drowField(){
    this->fieldPixmap=new QPixmap(QSize(static_cast<int>(mag*field->width) + 1, static_cast<int>(mag*field->height) + 1));
    QPainter painter(this->fieldPixmap);
    for(int y=0; y<field->height; ++y){
        for(int x=0; x<field->width; ++x){
            QPointF points[4] = {
                QPointF(x*mag, y*mag),
                QPointF(x*mag+mag, y*mag),
                QPointF(x*mag+mag, y*mag+mag),
                QPointF(x*mag, y*mag+mag)
            };
            if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color==red)
                painter.setBrush(QBrush(QColor(255, 102, 102, 255), Qt::SolidPattern));
            else if(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).color==blue)
                painter.setBrush(QBrush(QColor(102, 102, 255, 255), Qt::SolidPattern));
            else painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
            painter.drawConvexPolygon(points, 4);
        }
    }//タイルの色を塗りつぶす

    for(int i=0; i<2; ++i){
        for(unsigned int j=0; j < teams->agents.size(); ++j){
            QPointF points[4] = {
                QPointF((teams[i].agents[j].x - 1)*mag, (teams[i].agents[j].y - 1)*mag),
                QPointF((teams[i].agents[j].x - 1)*mag+mag, (teams[i].agents[j].y - 1)*mag),
                QPointF((teams[i].agents[j].x - 1)*mag+mag, (teams[i].agents[j].y - 1)*mag+mag),
                QPointF((teams[i].agents[j].x - 1)*mag, (teams[i].agents[j].y - 1)*mag+mag)
            };
            if((i==0&&colorPattern==0)||(i==1&&colorPattern==1)){
                painter.setBrush(QBrush(QColor(255, 56, 56, 255), Qt::SolidPattern));
            }else if((i==0&&colorPattern==1)||(i==1&&colorPattern==0)){
                painter.setBrush(QBrush(QColor(56, 56, 255, 255), Qt::SolidPattern));
            }else{
                cout<<"error"<<endl;
            }
            painter.drawConvexPolygon(points, 4);

        }
    }//エージェントの現在地を塗りつぶす

    QString str;
    QFont font = painter.font();
    font.setPixelSize(static_cast<int>(mag*0.4));
    painter.setFont(font);
    for(int y=0; y<field->height; ++y){
        for(int x=0; x<field->width; ++x){
            str = QString::fromStdString(to_string(tile->at(static_cast<unsigned>(y)).at(static_cast<unsigned>(x)).point));
            painter.drawText(static_cast<int>(x*mag+mag*0.3), static_cast<int>(y*mag+mag*0.4),str);
        }
    }//タイルのポイントを描画

    for(int i=0; i<2; ++i){
        for(unsigned int j=0; j < teams[i].agents.size(); ++j){
            str = QString::fromStdString(to_string(j));
            painter.drawText(static_cast<int>((teams[i].agents[j].x*mag)-mag*0.4), static_cast<int>((teams[i].agents[j].y*mag)-mag*0.1),str);
        }
    }//エージェントナンバーを描画

    painter.end();
}

/* ### アルゴリズムが算出した次の手を表示 ### */
void AnalyzeField::drowNextPosition(){
    unsigned int i;
    unsigned int MposX,MposY;
    unsigned int mag = static_cast <unsigned>(this->mag);
    QPainter painter(this->fieldPixmap);
    for(i=0;i<teams->agents.size();i++)
    {
    MposX=static_cast<unsigned>(static_cast<int>(teams[field->myTeam].agents[i].x)-1+teams[field->myTeam].agents[i].actions.dx);
    MposY=static_cast<unsigned>(static_cast<int>(teams[field->myTeam].agents[i].y)-1+teams[field->myTeam].agents[i].actions.dy);
    QPointF points[6] = {
            QPointF(MposX*mag+2, MposY*mag+2),
            QPointF(MposX*mag+mag-2, MposY*mag+2),
            QPointF(MposX*mag+mag-2, MposY*mag+mag-2),
            QPointF(MposX*mag+2, MposY*mag+mag-2),
            QPointF(MposX*mag+mag/2, MposY*mag+mag/2),
            QPointF((static_cast<unsigned>(teams[field->myTeam].agents[i].x)-1)*mag+mag/2,(static_cast<unsigned>(teams[field->myTeam].agents[i].y)-1)*mag+mag/2)
        };
        if(teams[field->myTeam].agents[i].actions.type == 2) painter.setPen(QPen(QColor(0, 180, 0, 255),3)); // remove
        else painter.setPen(QPen(QColor(255, 180, 0, 255),3)); // move or stay
        painter.drawLine(points[0],points[1]);
        painter.drawLine(points[1],points[2]);
        painter.drawLine(points[2],points[3]);
        painter.drawLine(points[3],points[0]);
        painter.drawLine(points[4],points[5]);
    }
        painter.end();
        repaint();
}

/* ### 動く先の情報(actions)をjsonFile化 ### */
void AnalyzeField::encode(string path){
    QString type_string;
    QJsonArray jsonarr;
    QJsonObject actions_obj;
    vector<QJsonObject> actions_vector;
    string strType;
    for (unsigned int i=0;i<teams[0].agents.size();i++) {
        switch (teams[field->myTeam].agents[i].actions.type) {
        case 0 :
            strType = "stay";
            break;
        case 1:
            strType = "move";
            break;
        case 2 :
            strType = "remove";
            break;
        }
        QJsonObject agent_obj={
            {"agentID", teams[field->myTeam].agents[i].agentID},
            {"type", QString::fromStdString(strType)},
            {"dx", teams[field->myTeam].agents[i].actions.dx},
            {"dy", teams[field->myTeam].agents[i].actions.dy},
        };
        actions_vector.push_back(agent_obj);
    }
    for(auto name:actions_vector)
    {
        jsonarr.append(name);
    }
    actions_obj["actions"] = jsonarr;
    QJsonDocument jsonDoc(actions_obj);
    network->actionData = jsonDoc.toJson();
    QFile savefile(QString::fromStdString(path));
    savefile.open(QIODevice::WriteOnly);
    savefile.write(network->actionData);
    savefile.close();
}

/* ### SecondPlayerのためのField色等の反転 ### */
void AnalyzeField::inversionForSecondPlayer(){
    swap(&field->playerColor[0], &field->playerColor[1]);
    swap(&field->TeamColorNumber[0], &field->TeamColorNumber[1]);
    if(field->myTeam == 0){
        field->myTeam = 1;
    }else{
        field->myTeam = 0;
    }
}

/* ### Swap ### */
void AnalyzeField::swap(int *x, int *y){
    int z;
    z = *x;
    *x = *y;
    *y = z;
}

/* ### イベントの描写 ### */
void AnalyzeField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *fieldPixmap);
    painter.end();
}

/* ### データのアプリケーション出力 ### */
void AnalyzeField::debug(){
    cout << "////////////Debug AF///////////////" << endl;
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
    cout << "///////////////////////////////////////" << endl;
}
