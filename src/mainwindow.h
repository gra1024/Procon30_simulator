#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<vector<Tile>> tile;
    vector<vector<Agent>> agent;
    Field field;


private slots:
    void on_startButton_clicked();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
