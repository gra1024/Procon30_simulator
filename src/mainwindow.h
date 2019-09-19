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
    AnalyzeField* AF = nullptr;
    Computer* C = nullptr;
    UnficationField* UF = nullptr;
    NetworkManager* NM = nullptr;
    PointCalculate* PC = nullptr;

    vector<vector<Tile>> tile;
    Teams teams[2];
    Field field;
    Actions action;
    Network network;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_reload_clicked();
    void on_pushButton_close_clicked();
    void updateTeamPoints();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
