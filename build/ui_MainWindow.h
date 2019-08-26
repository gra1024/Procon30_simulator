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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QComboBox *comboBox_TeamColor_1;
    QLabel *label_TeamColor_1;
    QPushButton *Button_Start_1;
    QComboBox *comboBox_Algo_1;
    QLabel *label_Algo_1;
    QPushButton *Button_Reload_1;
    QLCDNumber *display_RED_1;
    QLCDNumber *display_Blue_1;
    QLabel *label_Game_1;
    QLabel *label_Time_1;
    QSpinBox *spinBox_Time_1;
    QLabel *label_Lamp_1_1;
    QLabel *label_Lamp_1_2;
    QLabel *label_MaxTurn_1;
    QSpinBox *spinBox_MaxTurn_1;
    QLabel *label_Back_Red_1;
    QLabel *label_Back_Blue_1;
    QLabel *label_Turn_1;
    QLCDNumber *display_Turn_1;
    QPushButton *Button_Reset_1;
    QPushButton *pushButton;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(400, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("MS UI Gothic"));
        MainWindow->setFont(font);
        comboBox_TeamColor_1 = new QComboBox(MainWindow);
        comboBox_TeamColor_1->addItem(QString());
        comboBox_TeamColor_1->addItem(QString());
        comboBox_TeamColor_1->setObjectName(QString::fromUtf8("comboBox_TeamColor_1"));
        comboBox_TeamColor_1->setGeometry(QRect(70, 90, 61, 22));
        label_TeamColor_1 = new QLabel(MainWindow);
        label_TeamColor_1->setObjectName(QString::fromUtf8("label_TeamColor_1"));
        label_TeamColor_1->setGeometry(QRect(10, 90, 61, 20));
        Button_Start_1 = new QPushButton(MainWindow);
        Button_Start_1->setObjectName(QString::fromUtf8("Button_Start_1"));
        Button_Start_1->setGeometry(QRect(10, 30, 61, 31));
        QFont font1;
        font1.setPointSize(18);
        Button_Start_1->setFont(font1);
        comboBox_Algo_1 = new QComboBox(MainWindow);
        comboBox_Algo_1->addItem(QString());
        comboBox_Algo_1->addItem(QString());
        comboBox_Algo_1->setObjectName(QString::fromUtf8("comboBox_Algo_1"));
        comboBox_Algo_1->setGeometry(QRect(70, 70, 61, 22));
        label_Algo_1 = new QLabel(MainWindow);
        label_Algo_1->setObjectName(QString::fromUtf8("label_Algo_1"));
        label_Algo_1->setGeometry(QRect(10, 70, 61, 20));
        Button_Reload_1 = new QPushButton(MainWindow);
        Button_Reload_1->setObjectName(QString::fromUtf8("Button_Reload_1"));
        Button_Reload_1->setGeometry(QRect(70, 30, 61, 31));
        display_RED_1 = new QLCDNumber(MainWindow);
        display_RED_1->setObjectName(QString::fromUtf8("display_RED_1"));
        display_RED_1->setGeometry(QRect(10, 180, 51, 23));
        display_RED_1->setFont(font);
        display_RED_1->setStyleSheet(QString::fromUtf8("background:#fff;"));
        display_Blue_1 = new QLCDNumber(MainWindow);
        display_Blue_1->setObjectName(QString::fromUtf8("display_Blue_1"));
        display_Blue_1->setGeometry(QRect(70, 180, 51, 23));
        display_Blue_1->setStyleSheet(QString::fromUtf8("background:#fff;"));
        label_Game_1 = new QLabel(MainWindow);
        label_Game_1->setObjectName(QString::fromUtf8("label_Game_1"));
        label_Game_1->setGeometry(QRect(10, 10, 61, 16));
        label_Time_1 = new QLabel(MainWindow);
        label_Time_1->setObjectName(QString::fromUtf8("label_Time_1"));
        label_Time_1->setGeometry(QRect(10, 110, 61, 21));
        spinBox_Time_1 = new QSpinBox(MainWindow);
        spinBox_Time_1->setObjectName(QString::fromUtf8("spinBox_Time_1"));
        spinBox_Time_1->setGeometry(QRect(70, 110, 61, 21));
        label_Lamp_1_1 = new QLabel(MainWindow);
        label_Lamp_1_1->setObjectName(QString::fromUtf8("label_Lamp_1_1"));
        label_Lamp_1_1->setGeometry(QRect(90, 10, 16, 16));
        label_Lamp_1_2 = new QLabel(MainWindow);
        label_Lamp_1_2->setObjectName(QString::fromUtf8("label_Lamp_1_2"));
        label_Lamp_1_2->setGeometry(QRect(110, 10, 16, 16));
        label_MaxTurn_1 = new QLabel(MainWindow);
        label_MaxTurn_1->setObjectName(QString::fromUtf8("label_MaxTurn_1"));
        label_MaxTurn_1->setGeometry(QRect(10, 130, 61, 21));
        spinBox_MaxTurn_1 = new QSpinBox(MainWindow);
        spinBox_MaxTurn_1->setObjectName(QString::fromUtf8("spinBox_MaxTurn_1"));
        spinBox_MaxTurn_1->setGeometry(QRect(70, 130, 61, 21));
        label_Back_Red_1 = new QLabel(MainWindow);
        label_Back_Red_1->setObjectName(QString::fromUtf8("label_Back_Red_1"));
        label_Back_Red_1->setGeometry(QRect(10, 170, 50, 41));
        label_Back_Red_1->setStyleSheet(QString::fromUtf8("background:#f00"));
        label_Back_Blue_1 = new QLabel(MainWindow);
        label_Back_Blue_1->setObjectName(QString::fromUtf8("label_Back_Blue_1"));
        label_Back_Blue_1->setGeometry(QRect(70, 170, 50, 41));
        label_Back_Blue_1->setStyleSheet(QString::fromUtf8("background:#00f"));
        label_Turn_1 = new QLabel(MainWindow);
        label_Turn_1->setObjectName(QString::fromUtf8("label_Turn_1"));
        label_Turn_1->setGeometry(QRect(10, 220, 51, 21));
        display_Turn_1 = new QLCDNumber(MainWindow);
        display_Turn_1->setObjectName(QString::fromUtf8("display_Turn_1"));
        display_Turn_1->setGeometry(QRect(10, 240, 51, 23));
        display_Turn_1->setFont(font);
        display_Turn_1->setStyleSheet(QString::fromUtf8("background:#fff;"));
        Button_Reset_1 = new QPushButton(MainWindow);
        Button_Reset_1->setObjectName(QString::fromUtf8("Button_Reset_1"));
        Button_Reset_1->setGeometry(QRect(70, 270, 61, 21));
        pushButton = new QPushButton(MainWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(282, 10, 111, 31));
        label_Back_Blue_1->raise();
        label_Back_Red_1->raise();
        comboBox_TeamColor_1->raise();
        label_TeamColor_1->raise();
        Button_Start_1->raise();
        comboBox_Algo_1->raise();
        label_Algo_1->raise();
        Button_Reload_1->raise();
        display_RED_1->raise();
        display_Blue_1->raise();
        label_Game_1->raise();
        label_Time_1->raise();
        spinBox_Time_1->raise();
        label_Lamp_1_1->raise();
        label_Lamp_1_2->raise();
        label_MaxTurn_1->raise();
        spinBox_MaxTurn_1->raise();
        label_Turn_1->raise();
        display_Turn_1->raise();
        Button_Reset_1->raise();
        pushButton->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox_TeamColor_1->setItemText(0, QApplication::translate("MainWindow", "red", nullptr));
        comboBox_TeamColor_1->setItemText(1, QApplication::translate("MainWindow", "blue", nullptr));

        label_TeamColor_1->setText(QApplication::translate("MainWindow", "TeamColor", nullptr));
        Button_Start_1->setText(QApplication::translate("MainWindow", "Start", nullptr));
        comboBox_Algo_1->setItemText(0, QApplication::translate("MainWindow", "field1", nullptr));
        comboBox_Algo_1->setItemText(1, QApplication::translate("MainWindow", "field2", nullptr));

        label_Algo_1->setText(QApplication::translate("MainWindow", "Algorithm", nullptr));
        Button_Reload_1->setText(QApplication::translate("MainWindow", "Reload", nullptr));
        label_Game_1->setText(QApplication::translate("MainWindow", "Game1", nullptr));
        label_Time_1->setText(QApplication::translate("MainWindow", "Time", nullptr));
        label_Lamp_1_1->setText(QApplication::translate("MainWindow", "x", nullptr));
        label_Lamp_1_2->setText(QApplication::translate("MainWindow", "x", nullptr));
        label_MaxTurn_1->setText(QApplication::translate("MainWindow", "MaxTurn", nullptr));
        label_Back_Red_1->setText(QString());
        label_Back_Blue_1->setText(QString());
        label_Turn_1->setText(QApplication::translate("MainWindow", "Turn", nullptr));
        Button_Reset_1->setText(QApplication::translate("MainWindow", "reset", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "FromJSON to C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
