#include "NetworkManager.h"

NetworkManager::NetworkManager()
{

}


void NetworkManager::get()//teamIDによるリクエストの変更、データ送信時のPOSTリクエスト
{
    //cout<<"aaa"<<endl;
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));
    QNetworkRequest request(QUrl("http://127.0.0.1:8081/matches"));
    request.setRawHeader("Authorization", "procon30_example_token");//トークンの追加
    QNetworkReply *reply = manager->get(request);
    eventLoop.exec();

    cout<<reply->readAll().data()<<endl;//応答をcharで表示
}

void NetworkManager::post()//actionの提出、行動結果の受信
{

}
