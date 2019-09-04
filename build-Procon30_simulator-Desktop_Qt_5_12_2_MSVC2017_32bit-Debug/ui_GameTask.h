/********************************************************************************
** Form generated from reading UI file 'GameTask.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMETASK_H
#define UI_GAMETASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameTask
{
public:
    QPushButton *pushButton_start;
    QPushButton *pushButton_reload;
    QLabel *label_text_1;
    QLabel *label_text_gameNo;
    QLabel *label_text_2;
    QLabel *label_text_3;
    QLabel *label_text_5;
    QLabel *label_text_4;
    QComboBox *comboBox_algolithm;
    QComboBox *comboBox_teamColor;
    QSpinBox *spinBox_time;
    QSpinBox *spinBox_maxTurn;
    QLabel *label_background_2;
    QLabel *label_background_1;
    QLabel *label_background_3;
    QLCDNumber *lcdNumber_red;
    QLCDNumber *lcdNumber_blue;
    QLCDNumber *lcdNumber_turn;
    QPushButton *pushButton_close;
    QLabel *label_text_6;
    QLabel *label_lamp_2;
    QLabel *label_lamp_1;

    void setupUi(QWidget *GameTask)
    {
        if (GameTask->objectName().isEmpty())
            GameTask->setObjectName(QString::fromUtf8("GameTask"));
        GameTask->resize(291, 171);
        pushButton_start = new QPushButton(GameTask);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(10, 30, 61, 31));
        pushButton_reload = new QPushButton(GameTask);
        pushButton_reload->setObjectName(QString::fromUtf8("pushButton_reload"));
        pushButton_reload->setGeometry(QRect(80, 30, 61, 31));
        label_text_1 = new QLabel(GameTask);
        label_text_1->setObjectName(QString::fromUtf8("label_text_1"));
        label_text_1->setGeometry(QRect(10, 10, 50, 21));
        label_text_gameNo = new QLabel(GameTask);
        label_text_gameNo->setObjectName(QString::fromUtf8("label_text_gameNo"));
        label_text_gameNo->setGeometry(QRect(60, 10, 21, 21));
        label_text_2 = new QLabel(GameTask);
        label_text_2->setObjectName(QString::fromUtf8("label_text_2"));
        label_text_2->setGeometry(QRect(10, 70, 61, 21));
        label_text_3 = new QLabel(GameTask);
        label_text_3->setObjectName(QString::fromUtf8("label_text_3"));
        label_text_3->setGeometry(QRect(10, 90, 61, 21));
        label_text_5 = new QLabel(GameTask);
        label_text_5->setObjectName(QString::fromUtf8("label_text_5"));
        label_text_5->setGeometry(QRect(10, 140, 61, 21));
        label_text_4 = new QLabel(GameTask);
        label_text_4->setObjectName(QString::fromUtf8("label_text_4"));
        label_text_4->setGeometry(QRect(10, 120, 61, 21));
        comboBox_algolithm = new QComboBox(GameTask);
        comboBox_algolithm->addItem(QString());
        comboBox_algolithm->addItem(QString());
        comboBox_algolithm->setObjectName(QString::fromUtf8("comboBox_algolithm"));
        comboBox_algolithm->setGeometry(QRect(80, 70, 61, 21));
        comboBox_teamColor = new QComboBox(GameTask);
        comboBox_teamColor->addItem(QString());
        comboBox_teamColor->addItem(QString());
        comboBox_teamColor->setObjectName(QString::fromUtf8("comboBox_teamColor"));
        comboBox_teamColor->setGeometry(QRect(80, 90, 61, 22));
        spinBox_time = new QSpinBox(GameTask);
        spinBox_time->setObjectName(QString::fromUtf8("spinBox_time"));
        spinBox_time->setGeometry(QRect(80, 120, 61, 20));
        spinBox_maxTurn = new QSpinBox(GameTask);
        spinBox_maxTurn->setObjectName(QString::fromUtf8("spinBox_maxTurn"));
        spinBox_maxTurn->setGeometry(QRect(80, 140, 61, 21));
        label_background_2 = new QLabel(GameTask);
        label_background_2->setObjectName(QString::fromUtf8("label_background_2"));
        label_background_2->setGeometry(QRect(220, 30, 61, 41));
        label_background_2->setStyleSheet(QString::fromUtf8("background:#00f"));
        label_background_1 = new QLabel(GameTask);
        label_background_1->setObjectName(QString::fromUtf8("label_background_1"));
        label_background_1->setGeometry(QRect(150, 30, 61, 41));
        label_background_1->setStyleSheet(QString::fromUtf8("background:#f00"));
        label_background_3 = new QLabel(GameTask);
        label_background_3->setObjectName(QString::fromUtf8("label_background_3"));
        label_background_3->setGeometry(QRect(150, 90, 61, 51));
        label_background_3->setStyleSheet(QString::fromUtf8("background:#fff"));
        lcdNumber_red = new QLCDNumber(GameTask);
        lcdNumber_red->setObjectName(QString::fromUtf8("lcdNumber_red"));
        lcdNumber_red->setGeometry(QRect(150, 40, 61, 23));
        lcdNumber_red->setStyleSheet(QString::fromUtf8("background:#fff"));
        lcdNumber_blue = new QLCDNumber(GameTask);
        lcdNumber_blue->setObjectName(QString::fromUtf8("lcdNumber_blue"));
        lcdNumber_blue->setGeometry(QRect(220, 40, 61, 23));
        lcdNumber_blue->setStyleSheet(QString::fromUtf8("background:#fff"));
        lcdNumber_turn = new QLCDNumber(GameTask);
        lcdNumber_turn->setObjectName(QString::fromUtf8("lcdNumber_turn"));
        lcdNumber_turn->setGeometry(QRect(150, 110, 61, 23));
        lcdNumber_turn->setStyleSheet(QString::fromUtf8("background:#fff"));
        pushButton_close = new QPushButton(GameTask);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(220, 140, 61, 23));
        label_text_6 = new QLabel(GameTask);
        label_text_6->setObjectName(QString::fromUtf8("label_text_6"));
        label_text_6->setGeometry(QRect(150, 90, 61, 21));
        label_lamp_2 = new QLabel(GameTask);
        label_lamp_2->setObjectName(QString::fromUtf8("label_lamp_2"));
        label_lamp_2->setGeometry(QRect(110, 10, 16, 16));
        label_lamp_1 = new QLabel(GameTask);
        label_lamp_1->setObjectName(QString::fromUtf8("label_lamp_1"));
        label_lamp_1->setGeometry(QRect(90, 10, 16, 16));
        pushButton_start->raise();
        pushButton_reload->raise();
        label_text_1->raise();
        label_text_gameNo->raise();
        label_text_2->raise();
        label_text_3->raise();
        label_text_5->raise();
        label_text_4->raise();
        comboBox_algolithm->raise();
        spinBox_maxTurn->raise();
        spinBox_time->raise();
        comboBox_teamColor->raise();
        label_background_2->raise();
        label_background_1->raise();
        label_background_3->raise();
        lcdNumber_red->raise();
        lcdNumber_blue->raise();
        lcdNumber_turn->raise();
        pushButton_close->raise();
        label_text_6->raise();
        label_lamp_2->raise();
        label_lamp_1->raise();

        retranslateUi(GameTask);

        QMetaObject::connectSlotsByName(GameTask);
    } // setupUi

    void retranslateUi(QWidget *GameTask)
    {
        GameTask->setWindowTitle(QApplication::translate("GameTask", "Form", nullptr));
        pushButton_start->setText(QApplication::translate("GameTask", "Start", nullptr));
        pushButton_reload->setText(QApplication::translate("GameTask", "Reload", nullptr));
        label_text_1->setText(QApplication::translate("GameTask", "GameNo.", nullptr));
        label_text_gameNo->setText(QApplication::translate("GameTask", "x", nullptr));
        label_text_2->setText(QApplication::translate("GameTask", "Algolithm", nullptr));
        label_text_3->setText(QApplication::translate("GameTask", "TeamColor", nullptr));
        label_text_5->setText(QApplication::translate("GameTask", "MaxTurn", nullptr));
        label_text_4->setText(QApplication::translate("GameTask", "Time", nullptr));
        comboBox_algolithm->setItemText(0, QApplication::translate("GameTask", "Algo1", nullptr));
        comboBox_algolithm->setItemText(1, QApplication::translate("GameTask", "Algo2", nullptr));

        comboBox_teamColor->setItemText(0, QApplication::translate("GameTask", "Red", nullptr));
        comboBox_teamColor->setItemText(1, QApplication::translate("GameTask", "Blue", nullptr));

        label_background_2->setText(QString());
        label_background_1->setText(QString());
        label_background_3->setText(QString());
        pushButton_close->setText(QApplication::translate("GameTask", "close", nullptr));
        label_text_6->setText(QApplication::translate("GameTask", "Turn", nullptr));
        label_lamp_2->setText(QApplication::translate("GameTask", "x", nullptr));
        label_lamp_1->setText(QApplication::translate("GameTask", "x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameTask: public Ui_GameTask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMETASK_H
