#include "NetworkManager.h"

NetworkManager::NetworkManager()
{

}

/*　### 初期設定 ###　*/
void NetworkManager::setup(Ui::MainWindow *uiMainWindow, Network *network){
    this->uiMainWindow = uiMainWindow;
    this->network = network;
    matchID = uiMainWindow->spinBox_matchID->value();
    if(uiMainWindow->checkBox_player->checkState() == 0 && uiMainWindow->checkBox_gameMaster->checkState() == 0){
        checkState = 0;
    }else{
        checkState = 1;
    }
}

/*　### サーバーへ接続し、フィールド情報を取得する ###　*/
void NetworkManager::get()
{
    if(checkState==1)return;//practice時の接続を防ぐ
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));

    QUrl url = QUrl("http://127.0.0.1:8081/matches");
    if(matchID!=0){
        QString matchIDStr;
        QString urlStr = QString("%1%2%3").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID));
        url=QUrl(urlStr);
        qDebug()<<"URL:"<<urlStr;
    }

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");
    QNetworkReply *reply = manager->get(request);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
    network->matchReply = jsonDoc.object();
}

/*　### サーバーへ接続し、アルゴリズムによる計算結果を送信する ###　*/
void NetworkManager::post()
{
    if(checkState==1)return;//practice時の接続を防ぐ
    if(matchID==0)return;//試合事前情報取得時のpostを防ぐ

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    object.connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));

    QUrl url = QUrl("http://127.0.0.1:8081/matches");

    QString matchIDStr;
    QString urlStr = QString("%1%2%3%4").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID)).arg("/action");
    url=QUrl(urlStr);
    qDebug()<<"URL:"<<urlStr;

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *reply = manager->post(request,network->actionData);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;
}
