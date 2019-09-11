#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Config.h"

class NetworkManager:public QObject
{
public:
    NetworkManager();
    void get();//Reloadを押すと試合情報が返ってくる
    void post();//Reloadを押すとactionを送信し、行動結果を取得する

};

#endif // NETWORKMANAGER_H
