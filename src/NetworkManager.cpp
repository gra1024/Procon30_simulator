#include "NetworkManager.h"

NetworkManager::NetworkManager()
{

}

/*　### 初期設定 ###　*/
void NetworkManager::setup(Ui::MainWindow *uiMainWindow, Network *network){
    this->uiMainWindow = uiMainWindow;
    this->network = network;
    matchID = uiMainWindow->spinBox_matchID->value();
    checkState = uiMainWindow->checkBox_practice->checkState();
}

/*　### サーバーへ接続し、フィールド情報を取得する ###　*/
void NetworkManager::get()
{
    if(checkState==1)return;//practice時の接続を防ぐ
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));

    QString urlStr = QString("%1%2").arg(CONFIG_URL).arg("/matches");
    QUrl url = QUrl(urlStr);
    if(matchID!=0){
        QString matchIDStr;
        urlStr = QString("%1%2%3").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID));
        url=QUrl(urlStr);
        qDebug()<<"URL:"<<urlStr;
    }

    QNetworkRequest request(url);

    request.setRawHeader("Authorization",QString::fromStdString(CONFIG_TOKEN).toUtf8());
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

    QString urlStr = QString("%1%2").arg(CONFIG_URL).arg("/matches");
    QUrl url = QUrl(urlStr);

    QString matchIDStr;
    urlStr = QString("%1%2%3%4").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID)).arg("/action");
    url=QUrl(urlStr);
    qDebug()<<"URL:"<<urlStr;

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", QString::fromStdString(CONFIG_TOKEN).toUtf8());
    request.setRawHeader("Content-Type","application/json");
    QNetworkReply *reply = manager->post(request,network->actionData);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;
}
