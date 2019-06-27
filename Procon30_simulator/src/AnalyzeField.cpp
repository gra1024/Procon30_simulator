#include "AnalyzeField.h"
#include "ui_analyzefield.h"

extern QSettings config;

AnalyzeField::AnalyzeField(vector<vector<Tile>>& tile, vector<vector<Agent>>& agent, Field& field, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalyzeField),
    tile(tile),
    agent(agent),
    field(field)
{
    ui->setupUi(this);
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

string AnalyzeField::LoadFieldFromTxt()
{
    string path = CONFIG_PATH_OF_FIELD_TXT.toStdString();
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
    string path = CONFIG_PATH_OF_AGENT_TXT.toStdString();
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
