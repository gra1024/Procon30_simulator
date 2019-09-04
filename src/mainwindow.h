#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Config.h"
#include "AnalyzeField.h"


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

private slots:
    void on_pushButton_createNewGame_clicked();
    void on_pushButton_close_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
