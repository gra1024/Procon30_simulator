/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *pushButton_config;
    QPushButton *pushButton_close;
    QPushButton *pushButton_createNewGame;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(151, 91);
        QFont font;
        font.setFamily(QString::fromUtf8("MS UI Gothic"));
        MainWindow->setFont(font);
        pushButton_config = new QPushButton(MainWindow);
        pushButton_config->setObjectName(QString::fromUtf8("pushButton_config"));
        pushButton_config->setGeometry(QRect(10, 60, 61, 23));
        pushButton_close = new QPushButton(MainWindow);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(80, 60, 61, 23));
        pushButton_createNewGame = new QPushButton(MainWindow);
        pushButton_createNewGame->setObjectName(QString::fromUtf8("pushButton_createNewGame"));
        pushButton_createNewGame->setGeometry(QRect(10, 10, 131, 41));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_config->setText(QApplication::translate("MainWindow", "config", nullptr));
        pushButton_close->setText(QApplication::translate("MainWindow", "close", nullptr));
        pushButton_createNewGame->setText(QApplication::translate("MainWindow", "Create New Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
