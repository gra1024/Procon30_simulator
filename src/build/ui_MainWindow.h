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
#include <QtWidgets/QCheckBox>
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
    QPushButton *pushButton_close;
    QPushButton *pushButton_reload;
    QPushButton *pushButton_start;
    QLabel *label_algolithm;
    QLabel *label_teamColor;
    QLabel *label_time;
    QLabel *label_maxTurn;
    QComboBox *comboBox_algolithm;
    QComboBox *comboBox_teamColor;
    QSpinBox *spinBox_time;
    QSpinBox *spinBox_maxTurn;
    QLabel *label_color_red;
    QLabel *label_color_blue;
    QLabel *label_color_red_2;
    QLabel *label_color_blue_2;
    QLCDNumber *lcdNumber_red;
    QLCDNumber *lcdNumber_blue;
    QLCDNumber *lcdNumber_3;
    QLabel *label_color_white;
    QLabel *label_color_white_2;
    QLabel *label_teamID;
    QSpinBox *spinBox_teamID;
    QCheckBox *checkBox_practice;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(850, 320);
        QFont font;
        font.setFamily(QString::fromUtf8("MS UI Gothic"));
        MainWindow->setFont(font);
        pushButton_close = new QPushButton(MainWindow);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setGeometry(QRect(640, 260, 200, 40));
        pushButton_reload = new QPushButton(MainWindow);
        pushButton_reload->setObjectName(QString::fromUtf8("pushButton_reload"));
        pushButton_reload->setGeometry(QRect(220, 10, 200, 40));
        pushButton_start = new QPushButton(MainWindow);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setEnabled(true);
        pushButton_start->setGeometry(QRect(10, 10, 200, 40));
        pushButton_start->setMaximumSize(QSize(16777215, 16777215));
        pushButton_start->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_start->setMouseTracking(false);
        label_algolithm = new QLabel(MainWindow);
        label_algolithm->setObjectName(QString::fromUtf8("label_algolithm"));
        label_algolithm->setGeometry(QRect(10, 60, 200, 40));
        label_teamColor = new QLabel(MainWindow);
        label_teamColor->setObjectName(QString::fromUtf8("label_teamColor"));
        label_teamColor->setGeometry(QRect(10, 110, 200, 40));
        label_time = new QLabel(MainWindow);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(10, 210, 200, 40));
        label_maxTurn = new QLabel(MainWindow);
        label_maxTurn->setObjectName(QString::fromUtf8("label_maxTurn"));
        label_maxTurn->setGeometry(QRect(10, 260, 200, 40));
        comboBox_algolithm = new QComboBox(MainWindow);
        comboBox_algolithm->addItem(QString());
        comboBox_algolithm->addItem(QString());
        comboBox_algolithm->setObjectName(QString::fromUtf8("comboBox_algolithm"));
        comboBox_algolithm->setGeometry(QRect(220, 60, 200, 40));
        comboBox_teamColor = new QComboBox(MainWindow);
        comboBox_teamColor->addItem(QString());
        comboBox_teamColor->addItem(QString());
        comboBox_teamColor->setObjectName(QString::fromUtf8("comboBox_teamColor"));
        comboBox_teamColor->setGeometry(QRect(220, 110, 200, 40));
        spinBox_time = new QSpinBox(MainWindow);
        spinBox_time->setObjectName(QString::fromUtf8("spinBox_time"));
        spinBox_time->setGeometry(QRect(220, 210, 200, 40));
        spinBox_maxTurn = new QSpinBox(MainWindow);
        spinBox_maxTurn->setObjectName(QString::fromUtf8("spinBox_maxTurn"));
        spinBox_maxTurn->setGeometry(QRect(220, 260, 200, 40));
        label_color_red = new QLabel(MainWindow);
        label_color_red->setObjectName(QString::fromUtf8("label_color_red"));
        label_color_red->setGeometry(QRect(430, 10, 200, 20));
        label_color_red->setStyleSheet(QString::fromUtf8("background:#f00"));
        label_color_blue = new QLabel(MainWindow);
        label_color_blue->setObjectName(QString::fromUtf8("label_color_blue"));
        label_color_blue->setGeometry(QRect(640, 10, 200, 20));
        label_color_blue->setStyleSheet(QString::fromUtf8("background:#00f"));
        label_color_red_2 = new QLabel(MainWindow);
        label_color_red_2->setObjectName(QString::fromUtf8("label_color_red_2"));
        label_color_red_2->setGeometry(QRect(430, 80, 200, 20));
        label_color_red_2->setStyleSheet(QString::fromUtf8("background:#f00"));
        label_color_blue_2 = new QLabel(MainWindow);
        label_color_blue_2->setObjectName(QString::fromUtf8("label_color_blue_2"));
        label_color_blue_2->setGeometry(QRect(640, 80, 200, 20));
        label_color_blue_2->setStyleSheet(QString::fromUtf8("background:#00f"));
        lcdNumber_red = new QLCDNumber(MainWindow);
        lcdNumber_red->setObjectName(QString::fromUtf8("lcdNumber_red"));
        lcdNumber_red->setGeometry(QRect(430, 30, 200, 50));
        lcdNumber_red->setStyleSheet(QString::fromUtf8("background:#fff"));
        lcdNumber_blue = new QLCDNumber(MainWindow);
        lcdNumber_blue->setObjectName(QString::fromUtf8("lcdNumber_blue"));
        lcdNumber_blue->setGeometry(QRect(640, 30, 200, 50));
        lcdNumber_blue->setStyleSheet(QString::fromUtf8("background:#fff"));
        lcdNumber_3 = new QLCDNumber(MainWindow);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(430, 130, 200, 50));
        lcdNumber_3->setStyleSheet(QString::fromUtf8("background:#fff"));
        label_color_white = new QLabel(MainWindow);
        label_color_white->setObjectName(QString::fromUtf8("label_color_white"));
        label_color_white->setGeometry(QRect(430, 110, 200, 20));
        label_color_white->setStyleSheet(QString::fromUtf8("background:#fff"));
        label_color_white_2 = new QLabel(MainWindow);
        label_color_white_2->setObjectName(QString::fromUtf8("label_color_white_2"));
        label_color_white_2->setGeometry(QRect(430, 180, 200, 20));
        label_color_white_2->setStyleSheet(QString::fromUtf8("background:#fff"));
        label_teamID = new QLabel(MainWindow);
        label_teamID->setObjectName(QString::fromUtf8("label_teamID"));
        label_teamID->setGeometry(QRect(10, 160, 200, 40));
        spinBox_teamID = new QSpinBox(MainWindow);
        spinBox_teamID->setObjectName(QString::fromUtf8("spinBox_teamID"));
        spinBox_teamID->setGeometry(QRect(220, 160, 200, 40));
        spinBox_teamID->setMaximum(999999999);
        checkBox_practice = new QCheckBox(MainWindow);
        checkBox_practice->setObjectName(QString::fromUtf8("checkBox_practice"));
        checkBox_practice->setGeometry(QRect(430, 210, 200, 40));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_close->setText(QApplication::translate("MainWindow", "close", nullptr));
        pushButton_reload->setText(QApplication::translate("MainWindow", "Reload", nullptr));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", nullptr));
        label_algolithm->setText(QApplication::translate("MainWindow", "Algolithm", nullptr));
        label_teamColor->setText(QApplication::translate("MainWindow", "TeamColor", nullptr));
        label_time->setText(QApplication::translate("MainWindow", "Time", nullptr));
        label_maxTurn->setText(QApplication::translate("MainWindow", "MaxTurn", nullptr));
        comboBox_algolithm->setItemText(0, QApplication::translate("MainWindow", "Algolithm1", nullptr));
        comboBox_algolithm->setItemText(1, QApplication::translate("MainWindow", "Algolithm2", nullptr));

        comboBox_teamColor->setItemText(0, QApplication::translate("MainWindow", "Red", nullptr));
        comboBox_teamColor->setItemText(1, QApplication::translate("MainWindow", "Blue", nullptr));

        label_color_red->setText(QString());
        label_color_blue->setText(QString());
        label_color_red_2->setText(QString());
        label_color_blue_2->setText(QString());
        label_color_white->setText(QString());
        label_color_white_2->setText(QString());
        label_teamID->setText(QApplication::translate("MainWindow", "TeamID", nullptr));
        checkBox_practice->setText(QApplication::translate("MainWindow", "Practice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
