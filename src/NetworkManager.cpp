#include "NetworkManager.h"

NetworkManager::NetworkManager(Ui::MainWindow *uiMainWindow):
    uiMainWindow(uiMainWindow)
{
    matchID = uiMainWindow->spinBox_matchID->value();
}


void NetworkManager::get()//試合情報の取得
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));//接続

    QUrl url = QUrl("http://127.0.0.1:8081/matches");//matchID==0で試合事前情報の取得可能
    if(matchID!=0){//試合中の情報取得に切り替える
        QString matchIDStr;
        QString urlStr = QString("%1%2%3").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID));
        url=QUrl(urlStr);
        qDebug()<<"URL:"<<urlStr;
    }

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");//トークンの追加
    QNetworkReply *reply = manager->get(request);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;//応答(試合情報)をQStringで表示

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
    matchReply = jsonDoc.object();//これをAnalyzeFieldでデコードする
}

void NetworkManager::post(QByteArray actionData)//actionの提出(POST)
{
    if(matchID==0)return;//試合事前情報取得時のpostを防ぐ

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    object.connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));//接続

    QUrl url = QUrl("http://127.0.0.1:8081/matches");

    //matchIDに応じてURLを更新する
    QString matchIDStr;
    QString urlStr = QString("%1%2%3%4").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID)).arg("/action");
    url=QUrl(urlStr);
    qDebug()<<"URL:"<<urlStr;

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");//トークンの追加
    request.setRawHeader("Content-Type","application/json");//Content-Typeの指定
    QNetworkReply *reply = manager->post(request,actionData);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;//応答(行動結果)をQStringで表示...送信の合否確認用
}
