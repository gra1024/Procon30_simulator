#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"
#include "AnalyzeField.h"
#include "Computer.h"
#include "NetworkManager.h"


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
    Computer* C=nullptr;
    NetworkManager* manager;
    vector<vector<Tile>> tile;
    Teams teams[2];
    Field field;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_reload_clicked();
    void on_pushButton_close_clicked();



private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
