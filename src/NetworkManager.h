#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Config.h"
#include "ui_MainWindow.h"

class NetworkManager:public QObject
{
public:
    QObject object;

    NetworkManager();
    void setup(Ui::MainWindow *uiMainWindow, Network *network);
    void get();//Reloadを押すと試合情報が返ってくる
    void post();//Reloadを押すとactionを送信し、行動結果を取得する

    QJsonObject moveReply;

private:
    Ui::MainWindow *uiMainWindow;
    Network *network;
    int matchID;
    bool checkState;

};

#endif // NETWORKMANAGER_H
