#include "AnalyzeField.h"
#include "ui_AnalyzeField.h"

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

void AnalyzeField::setupField()
{
    string StrFieldFromLoadFile = LoadFieldFromTxt();
    decodeField(StrFieldFromLoadFile);
    string StrAgentFromLoadFile = LoadAgentFromTxt();
    decodeAgent(StrAgentFromLoadFile);
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
        cout << "------- "<< *itr << endl;
        numberList.push_back(split(*itr, ' '));
    }

    field.width = atoi(numberList[0][1].c_str());
    field.height = atoi(numberList[0][0].c_str());
    field.turn = -1;

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
        cout << "------- " << *itr << endl;
        numberList.push_back(split(*itr, ' '));
    }

    int agentMax = atoi(numberList[0][0].c_str());

    vector<Agent> agentList;
    for(auto itr1 = numberList.begin() + 1;itr1 != numberList.end(); ++itr1){
        Agent agentData;
        auto itr2 = (*itr1).begin();
        string s = *itr2;
        agentData.x = atoi(s.c_str());
        ++itr2;
        s = *itr2;
        agentData.y = atoi(s.c_str());
        agentList.push_back(agentData);
        if(agentList.size() % static_cast<unsigned>(agentMax) == 0){
            agent.push_back(agentList);
            agentData = {};
        }
    }
}

