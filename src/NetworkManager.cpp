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
        cout<<urlStr.toLocal8Bit().constData()<<endl;//QString to std::string urlCheck
    }

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");//トークンの追加
    QNetworkReply *reply = manager->get(request);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;//応答(試合情報)をQStringで表示

    //この後replyをAnalyzeFieldに送ってデータデコード、computerクラスで最善手の計算を行い、AnalyzeFieldで行動のエンコード、それをpost()が受け取る流れ

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
    matchReply = jsonDoc.object();//これをAnalizeFieldでデコードする

    //試合事前情報の取得ではjson変換はなし、この結果を見てMainWindowでteamID等を入力する形式の予定
    //試合情報の取得ではjson変換する、これをAnalyzefieldへ送信し、計算用変数へデコードしてもらう
}

void NetworkManager::post()//actionの提出(POST)、行動結果の取得
{
    if(matchID==0)return;//試合事前情報取得時のpostを防ぐ
    QString postDataStr = "{\"actions\":[{\"agentID\":2,\"dx\":1,\"dy\":1,\"type\":\"move\"},{\"agentID\":3,\"dx\":1,\"dy\":1,\"type\":\"move\"}]}";
    //ここはAnalizeFieldのエンコードよりactionのQstringを取得できるようにする
    QByteArray postData = postDataStr.toUtf8();

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QEventLoop eventLoop;
    object.connect(manager, SIGNAL(finished(QNetworkReply*)),&eventLoop, SLOT(quit()));//接続

    QUrl url = QUrl("http://127.0.0.1:8081/matches");

    //matchIDに応じてURLを更新する
    QString matchIDStr;
    QString urlStr = QString("%1%2%3%4").arg(url.toString()).arg("/").arg(matchIDStr.setNum(matchID)).arg("/action");
    url=QUrl(urlStr);
    cout<<urlStr.toLocal8Bit().constData()<<endl;//QString to std::string

    QNetworkRequest request(url);

    request.setRawHeader("Authorization", "procon30_example_token");//トークンの追加
    request.setRawHeader("Content-Type","application/json");//Content-Typeの指定
    QNetworkReply *reply = manager->post(request,postData);
    eventLoop.exec();

    QString jsonStr = QString::fromUtf8(reply->readAll());
    qDebug()<<jsonStr;//応答(行動結果)をQStringで表示

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8());
    moveReply = jsonDoc.object();//これをAnalizeFieldでデコードする
}
