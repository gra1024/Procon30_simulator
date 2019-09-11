#include "AnalyzeField.h"
#include "ui_AnalyzeField.h"

AnalyzeField::AnalyzeField(Ui::MainWindow *uiMainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeField),
    uiMainWindow(uiMainWindow)
{
    ui->setupUi(this);
    string title = "Field";
    this->setWindowTitle(QString::fromStdString(title));
}

AnalyzeField::~AnalyzeField()
{
    delete ui;
}

vector<string> AnalyzeField::split(const string &str, char sep)
{
    vector<std::string> v;
    stringstream ss(str);
    string buffer;
    while( std::getline(ss, buffer, sep) ) {
        v.push_back(buffer);
    }
    return v;
}

void AnalyzeField::setup(vector<vector<Tile>> *tile, Teams *teams, Field *field)
{
    this->tile = tile;
    this->teams = teams;
    this->field = field;
    decodeAndSet();
    setUi();
}

void AnalyzeField::pushReload(){
    decodeAndUpdate();
}

void AnalyzeField::setUi()
{
    mag = CONFIG_MAGNIFICATION_OF_FIELD/100*50;
    setFixedSize(QSize(mag*field->width + 1, mag*field->height+ 1));
    show();
}

void AnalyzeField::drow(){
    drowField();
    repaint();
}

string AnalyzeField::decodeAndSet(){
    QFile file("../data/fieldInfo.json");
    if (! file.open(QFile::ReadOnly)) {
        return "ERROR --decodeAndSet-- ";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();

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
        }

        tile->push_back(tileline);
    }

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

    if(uiMainWindow->spinBox_teamID->value() == teams[0].teamID){
        field->TeamColorNumber[0] = teams[0].teamID;
        field->TeamColorNumber[1] = teams[1].teamID;
    }else if(uiMainWindow->spinBox_teamID->value() == teams[1].teamID){
        field->TeamColorNumber[0] = teams[1].teamID;
        field->TeamColorNumber[1] = teams[0].teamID;
    }else{
        cout<<"ERROR --please set teamID--" << endl;
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

string AnalyzeField::decodeAndUpdate(){
    QFile file("../data/fieldInfo.json");
    if (! file.open(QFile::ReadOnly)) {
        return "ERROR --decoadAndUpdate--";
    }
    QTextStream in(&file);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(in.readAll().toUtf8());
    QJsonObject obj = jsonDoc.object();

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
    file.close();
    return "";
}

void AnalyzeField::drowField(){


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
    }//タイルの色塗りつぶす

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
    }//タイルのポイントを描写

    for(int i=0; i<2; ++i){
        for(unsigned int j=0; j < teams[i].agents.size(); ++j){
            str = QString::fromStdString(to_string(j));
            painter.drawText(static_cast<int>((teams[i].agents[j].x*mag)-mag*0.4), static_cast<int>((teams[i].agents[j].y*mag)-mag*0.1),str);
        }
    }//エージェントナンバーを描写

    painter.end();
}

void AnalyzeField::encode(int type[],int dx[],int dy[]){

    int agentID_int;
    QString type_string;
    int dx_int;
    int dy_int;
    QJsonArray jsonarr;
    QJsonObject actions_obj;
    vector<QJsonObject> actions_vector;
    for (unsigned int i=0;i<teams[0].agents.size();i++) {
        agentID_int = teams[0].agents[i].agentID;
        switch (type[i]) {
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
        dx_int=dx[i];
        dy_int=dy[i];
        QJsonObject agent_obj={
            {"teamID",agentID_int},
            {"type",type_string},
            {"dx",dx_int},
            {"dy",dy_int},
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
    QFile savefile("..\\data\\AgentMoveing.json");
    savefile.open(QIODevice::WriteOnly);
    savefile.write(data);
    savefile.close();
}

void AnalyzeField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *fieldPixmap);
    painter.end();
}

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
