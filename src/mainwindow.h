#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"
#include "AnalyzeField.h"
#include "Computer.h"
#include "NetworkManager.h"
#include "UnficationField.h"
#include "PointCalculate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_reload_clicked();
    void on_pushButton_close_clicked();

private:
    int selectAlgolithm(int num);
    void updateTeamPoints(int num);
    void autoReload();
    Ui::MainWindow *ui;
    NetworkManager* NM = nullptr;
    Network network;

    // FirstPlayer用（仮）
    AnalyzeField* AF = nullptr;
    PointCalculate* PC = nullptr;
    Computer* C = nullptr;
    vector<vector<Tile>> tile;
    Teams teams[2];
    Field field;

    // SecondPlayer用（仮）
    AnalyzeField* AF2 = nullptr;
    PointCalculate* PC2 = nullptr;
    Computer* C2 = nullptr;
    vector<vector<Tile>> tile2;
    Teams teams2[2];
    Field field2;

   // GameMaster用（仮）
    AnalyzeField* AF3 = nullptr;
    PointCalculate* PC3 = nullptr;
    UnficationField* UF = nullptr;
    vector<vector<Tile>> tile3;
    Teams teams3[2];
    Field field3;
};

#endif // MAINWINDOW_H
