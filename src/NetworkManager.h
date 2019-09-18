#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Config.h"
#include "ui_MainWindow.h"

class NetworkManager:public QObject
{
public:
    QObject object;

    NetworkManager(Ui::MainWindow *uiMainWindow);
    void get();//Reloadを押すと試合情報が返ってくる
    void post(QByteArray actionData);//Reloadを押すとactionを送信し、行動結果を取得する

    int matchID;

    QJsonObject matchReply;
    QJsonObject moveReply;

private:
    Ui::MainWindow *uiMainWindow;

};

#endif // NETWORKMANAGER_H
