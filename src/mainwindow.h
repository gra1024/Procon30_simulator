#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"
#include "AnalyzeField.h"
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
    NetworkManager* manager;

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_reload_clicked();
    void on_pushButton_close_clicked();



private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
