#include "MainWindow.h"
#include <QApplication>

QSettings config("..\\src\\Config.ini", QSettings::IniFormat);

int main(int argc, char *argv[])
{
    config.setIniCodec("UTF-8");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
