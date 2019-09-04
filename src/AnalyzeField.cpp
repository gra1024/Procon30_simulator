#include "AnalyzeField.h"
#include "ui_analyzefield.h"

extern QSettings config;

AnalyzeField::AnalyzeField(int gameNumberCount,
                           vector<vector<Tile>>& tile,
                           vector<vector<Agent>>& agent,
                           Field& field,
                           QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeField),
    tile(tile),
    agent(agent),
    field(field)
{
    gnc = gameNumberCount;
    ui->setupUi(this);
    string title = "Field" + to_string(gnc);
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

void AnalyzeField::setup()
{
    setField();
    setAgent();
    setUi();
}

void AnalyzeField::setField()
{
    string StrFieldFromLoadFile = LoadFieldFromTxt();
    decodeField(StrFieldFromLoadFile);
}

void AnalyzeField::setAgent()
{
    string StrAgentFromLoadFile = LoadAgentFromTxt();
    decodeAgent(StrAgentFromLoadFile);
}

void AnalyzeField::setUi()
{
    mag = static_cast<unsigned>(CONFIG_MAGNIFICATION_OF_FIELD)/100*50;
    setFixedSize(QSize(static_cast<int>(mag*field.width) + 1, static_cast<int>(mag*field.height) + 1));
    show();
    drowField();
}

void AnalyzeField::reload(vector<vector<Tile>> tile,vector<vector<Agent>> agent,Field field)
{
    //ファイルの読み込み フィールド情報
    QFile Fieldfile("フィールド情報_turn0.json");
    Fieldfile.open(QFile::ReadOnly);
    QTextStream FieldfileText (&Fieldfile);

    //Fieldfile から取り出した textstream をQtクラスのJSON形式に変換
    QJsonDocument QFieldfileDoc = QJsonDocument::fromJson(FieldfileText.readAll().toUtf8());
    QJsonObject QFieldfileobj = QFieldfileDoc.object();
    QStringList QFieldfilekeys =QFieldfileobj.keys();

    //QJson形式の配列を作成。ファイル内にある配列を作成(一番大きい)
    QJsonArray Field_points = QFieldfileobj.value("points").toArray();
    QJsonArray Field_color=QFieldfileobj.value("tiled").toArray();
    QJsonArray Field_teams=QFieldfileobj.value("teams").toArray();

    //qDebug()<<static_cast<unsigned int>(QFieldfileobj.value("width").toDouble());

    //QJSON形式をこちらで定義した変数に合わせて入れる struct Field
    field.width=static_cast<unsigned int>(QFieldfileobj.value("width").toDouble());

    field.height=static_cast<unsigned int>(QFieldfileobj.value("height").toDouble());
    field.startedAtUnixTime= static_cast<unsigned int>(QFieldfileobj.value("startedAtUnixTime").toDouble());
    field.turn= static_cast<unsigned int>(QFieldfileobj.value("turn").toDouble());

    //QJSON形式をこちらで定義した変数に合わせて入れる struct Tile pushとかを使ってた
    for (unsigned int i=0;i<field.height;i++) {
        vector<Tile> tileline;
        for(unsigned int j=0;j<static_cast<unsigned int>(field.width);j++){
            Tile tileData;
            tileData.point=static_cast<int>(Field_points.at(static_cast<int>(i)).toArray().at(static_cast<int>(j)).toDouble());
            tileData.color=WHITE;

            tileline.push_back(tileData);
        }
        tile.push_back(tileline);
    }
    //QJSON形式をこちらで定義した変数に合わせて入れる struct Agent
    for(int i=0;i<2;i++){
        vector<Agent> agentline;
        for(int j=0;j<Field_teams.at(0).toObject().value("agents").toArray().size();j++){
            Agent agentData;
            int k=i*(j+1)+j;
            agentData.teamID=static_cast<unsigned int>(Field_teams.at(0).toObject().value("teamID").toDouble());
            QJsonArray agent_array=Field_teams.at(i).toObject().value("agents").toArray();
            agentData.agentID=static_cast<unsigned int>(agent_array.at(k).toObject().value("agentID").toDouble());
            agentData.x=static_cast<unsigned int>(agent_array.at(k).toObject().value("x").toDouble());
            agentData.y=static_cast<unsigned int>(agent_array.at(k).toObject().value("y").toDouble());
            agentData.tilePoint=static_cast<unsigned int>(Field_teams.at(i).toObject().value("tilePoint").toDouble());
            agentData.areaPoint=static_cast<unsigned int>(Field_teams.at(i).toObject().value("areaPoint").toDouble());
            agentline.push_back(agentData);
        }
        agent.push_back(agentline);
    }

/*
    先輩のプログラム　参考に
    for(auto itr1 = numberList.begin()+1;itr1 != numberList.end(); ++itr1){
        vector<Tile> tileList;
        for(auto itr2 = (*itr1).begin();itr2 != (*itr1).end(); ++itr2){
            Tile tileData;
            string s = *itr2;
            tileData.point =atoi(s.c_str());
            tileData.color = WHITE;
            tileList.push_back(tileData);
        }
        tile.push_back(tileList);
    }
    //QJSON形式をこちらで定義した変数に合わせて入れる(visual studioの形式を再現。フィールド情報)
    FieldInformaitionTurn0.width= QFieldfileobj.value("width").toDouble();
    FieldInformaitionTurn0.height= QFieldfileobj.value("height").toDouble();
    QJsonArray points_line[20];
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {
     points_line[i]=Field_points.at(i).toArray();
    }
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {for(int j=0;j<FieldInformaitionTurn0.width;j++){
     FieldInformaitionTurn0.points[i][j]=points_line[i].at(j).toDouble();
     //std::cout<<FieldInformaitionTurn0.points[i][j];
    }    }
    FieldInformaitionTurn0.startedAtunixTime= QFieldfileobj.value("height").toDouble();
    FieldInformaitionTurn0.turn= QFieldfileobj.value("turn").toDouble();
    QJsonArray color_line[20];
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {
     color_line[i]=Field_color.at(i).toArray();
    }
    for (int i=0;i<FieldInformaitionTurn0.height;i++) {for(int j=0;j<FieldInformaitionTurn0.width;j++){
     FieldInformaitionTurn0.tiled[i][j]=color_line[i].at(j).toDouble();
     //std::cout<<FieldInformaitionTurn0.tiled[i][j];
    }    }
    Myteam.teamID= Field_teams.at(0).toObject().value("teamID").toDouble();
    //qDebug()<<Field_teams.at(0).toObject().value("teamID").toDouble();
    QJsonArray our_team_agents=Field_teams.at(0).toObject().value("agents").toArray();
    QJsonObject our_agents[8];
    for (int i=0;i<our_team_agents.size();i++) {
     our_agents[i]=our_team_agents.at(i).toObject();
     //qDebug()<<our_agents[i];
     Myteam.first_agents.agentID=our_agents[i].value("agentID").toDouble();
     Myteam.first_agents.x=our_agents[i].value("x").toDouble();
     Myteam.first_agents.y=our_agents[i].value("y").toDouble();
    }
    Myteam.tilePoint=Field_teams.at(0).toObject().value("tilePoint").toDouble();
    Myteam.areaPoint=Field_teams.at(0).toObject().value("areaPoint").toDouble();
    Enemyteam.teamID= Field_teams.at(1).toObject().value("teamID").toDouble();
    QJsonArray enemy_team_agents=Field_teams.at(1).toObject().value("agents").toArray();
    QJsonObject enemy_agents[8];
    for (int i=0;i<enemy_team_agents.size();i++) {
     enemy_agents[i]=enemy_team_agents.at(i).toObject();
     //qDebug()<<enemy_agents[i];
     Enemyteam.first_agents.agentID=our_agents[i].value("agentID").toDouble();
     Enemyteam.first_agents.x=our_agents[i].value("x").toDouble();
     Enemyteam.first_agents.y=our_agents[i].value("y").toDouble();
    }
    Enemyteam.tilePoint=Field_teams.at(0).toObject().value("tilePoint").toDouble();
    Enemyteam.areaPoint=Field_teams.at(0).toObject().value("areaPoint").toDouble();
    //↑おそらくjson形式の構造体に数値が入ってる
    Myteam.teamID=QFieldfileobj.value("teamID").toDouble();

     //QJSON形式をこちらで定義した変数に合わせて入れる(visual studioの形式を再現。行動情報)
        QFile MoveInformationID5("行動情報_ID5.json");
        MoveInformationID5.open(QFile::ReadOnly);
        QTextStream MoveInformationTextID5 (&MoveInformationID5);
        //MoveInformationID5 から取り出した textstream をQtクラスのJSON形式に変換
        QJsonDocument QMoveInformationID5Doc = QJsonDocument::fromJson(MoveInformationTextID5.readAll().toUtf8());
        QJsonObject QMoveInformationID5obj = QMoveInformationID5Doc.object();
        QStringList QMoveInformationID5keys =QMoveInformationID5obj.keys();
        //配列actionsを作成
        QJsonObject actions_array = QMoveInformationID5obj.value("actions").toArray().at(0).toObject();
        //qDebug()<<QMoveInformationID5Doc;
        We_first_agent_actions.agentID= actions_array.value("teamID").toDouble();
        QJsonArray We_first_agent_actions_Array=actions_array.value("actions").toArray();
        QJsonObject We_first_agent[8];
        for (int i=0;i<We_first_agent_actions_Array.size();i++) {
         We_first_agent[i]=We_first_agent_actions_Array.at(i).toObject();
         //qDebug()<<our_agents[i];
         We_first_agent_actions.type=our_agents[i].value("type").toString();
         //actionsのtypeができてない！
         //qDebug()<<our_agents[i].value("type").toString();
         We_first_agent_actions.dx=our_agents[i].value("dx").toDouble();
         We_first_agent_actions.dy=our_agents[i].value("dy").toDouble();
        }
        //ファイルの読み込み 行動情報(ID6)
        QFile MoveInformationID6("行動情報_ID6.json");
        MoveInformationID6.open(QFile::ReadOnly);
        QTextStream MoveInformationTextID6 (&MoveInformationID6);
        //MoveInformationID6 から取り出した textstream をQtクラスのJSON形式に変換
        QJsonDocument QMoveInformationID6Doc = QJsonDocument::fromJson(MoveInformationTextID6.readAll().toUtf8());
        QJsonObject QMoveInformationID6obj = QMoveInformationID6Doc.object();
        QStringList QMoveInformationID6keys =QMoveInformationID6obj.keys();
        //配列actionsを作成
        QJsonArray actions_arrayID6 = QMoveInformationID6obj.value("actions").toArray();
        We_second_agent_actions.agentID= actions_arrayID6.at(0).toObject().value("teamID").toDouble();
        QJsonArray We_second_agent_actions_Array=actions_arrayID6.at(0).toObject().value("actions").toArray();
        QJsonObject We_second_agent[8];
        for (int i=0;i<We_second_agent_actions_Array.size();i++) {
         We_second_agent[i]=We_second_agent_actions_Array.at(i).toObject();
         //qDebug()<<our_agents[i];
         We_first_agent_actions.type=We_second_agent[i].value("type").toString();
         //actionsのtypeができてない！
         qDebug()<<We_second_agent_actions.type;
         We_second_agent_actions.dx=We_second_agent[i].value("dx").toDouble();
         We_second_agent_actions.dy=We_second_agent[i].value("dy").toDouble();
        }


*/
Fieldfile.close();

}

string AnalyzeField::LoadFieldFromTxt()
{
    string path = CONFIG_PATH_OF_FIELD_TXT.toStdString() + to_string(gnc) + ".txt";
    QFile file(QString::fromStdString(path));
    if (! file.open(QIODevice::ReadOnly)) {
        return "ERROR";
    }
    QTextStream in(&file);
    QString qstr = in.readAll();
    string str = qstr.toStdString();
    file.close();
    cout << "receive "<<str << endl;
    return str;
}

void AnalyzeField::decodeField(string StrFieldFromLoadFile)
{
    vector<string> columnList;
    vector<vector<string> > numberList;
    columnList = split(StrFieldFromLoadFile, ':');
    for (auto itr = columnList.begin(); itr != columnList.end(); ++itr) {
        cout << *itr << endl;
        numberList.push_back(split(*itr, ' '));
    }

    field.width = static_cast<unsigned>(atoi(numberList[0][0].c_str()));
    field.height = static_cast<unsigned>(atoi(numberList[0][1].c_str()));
    field.turn = 0;

    for(auto itr1 = numberList.begin()+1;itr1 != numberList.end(); ++itr1){
        vector<Tile> tileList;
        for(auto itr2 = (*itr1).begin();itr2 != (*itr1).end(); ++itr2){
            Tile tileData;
            string s = *itr2;
            tileData.point =atoi(s.c_str());
            tileData.color = WHITE;
            tileList.push_back(tileData);
        }
        tile.push_back(tileList);
    }
}

string AnalyzeField::LoadAgentFromTxt()
{
    string path = CONFIG_PATH_OF_AGENT_TXT.toStdString() + to_string(gnc) + ".txt";
    QFile file(QString::fromStdString(path));
    if (! file.open(QIODevice::ReadOnly)) {
        return "ERROR";
    }
    QTextStream in(&file);
    QString qstr = in.readAll();
    string str = qstr.toStdString();
    file.close();
    cout << "receive "<< str << endl;
    return str;
}

void AnalyzeField::decodeAgent(string StrAgentFromLoadFile)
{
    vector<string> columnList;
    vector<vector<string> > numberList;
    columnList = split(StrAgentFromLoadFile, ':');
    for (auto itr = columnList.begin(); itr != columnList.end(); ++itr) {
        cout << *itr << endl;
        numberList.push_back(split(*itr, ' '));
    }

    unsigned int agentMax = static_cast<unsigned>(atoi(numberList[0][0].c_str()));

    vector<Agent> agentList;
    int colorcheck = 0;
    for(auto itr1 = numberList.begin() + 1;itr1 != numberList.end(); ++itr1){
        Agent agentData;
        auto itr2 = (*itr1).begin();
        string s = *itr2;
        agentData.x = static_cast<unsigned>(atoi(s.c_str()));
        ++itr2;
        s = *itr2;
        agentData.y = static_cast<unsigned>(atoi(s.c_str()));
        if(colorcheck==0) tile[agentData.x - 1][agentData.y - 1].color = field.playerColor[0];
        else tile[agentData.x - 1][agentData.y - 1].color = field.playerColor[1];
        agentList.push_back(agentData);
        if(agentList.size() % agentMax == 0){
            agent.push_back(agentList);
            agentList.clear();
            colorcheck++;
        }
    }
}

void AnalyzeField::drowField(){

    this->fieldPixmap=new QPixmap(QSize(static_cast<int>(mag*field.width) + 1, static_cast<int>(mag*field.height) + 1));
    QPainter painter(this->fieldPixmap);

    for(unsigned int y=0; y<field.height; ++y){
        for(unsigned int x=0; x<field.width; ++x){
            QPointF points[4] = {
                QPointF(x*mag, y*mag),
                QPointF(x*mag+mag, y*mag),
                QPointF(x*mag+mag, y*mag+mag),
                QPointF(x*mag, y*mag+mag)
            };
            if(tile[x][y].color==RED) painter.setBrush(QBrush(QColor(255, 102, 102, 255), Qt::SolidPattern));
            else if(tile[x][y].color==BLUE) painter.setBrush(QBrush(QColor(102, 102, 255, 255), Qt::SolidPattern));
            else painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

            painter.drawConvexPolygon(points, 4);
        }
    }
    for(unsigned int i=0; i<2; ++i){
        for(unsigned int j=0; j < agent[0].size(); ++j){
            QPointF points[4] = {
                QPointF((agent[i][j].x - 1)*mag, (agent[i][j].y - 1)*mag),
                QPointF((agent[i][j].x - 1)*mag+mag, (agent[i][j].y - 1)*mag),
                QPointF((agent[i][j].x - 1)*mag+mag, (agent[i][j].y - 1)*mag+mag),
                QPointF((agent[i][j].x - 1)*mag, (agent[i][j].y - 1)*mag+mag)
            };
            if(i==0) painter.setBrush(QBrush(QColor(204, 0, 0, 255), Qt::SolidPattern));
            else painter.setBrush(QBrush(QColor(0, 0, 204, 255), Qt::SolidPattern));
            painter.drawConvexPolygon(points, 4);

        }
    }
    painter.end();
}

void AnalyzeField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, *fieldPixmap);
    painter.end();
}
