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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton;
    QComboBox *comboBox_2;
    QLabel *label_2;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        comboBox = new QComboBox(MainWindow);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(70, 180, 71, 22));
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 160, 61, 20));
        pushButton = new QPushButton(MainWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 40, 151, 71));
        QFont font;
        font.setPointSize(18);
        pushButton->setFont(font);
        comboBox_2 = new QComboBox(MainWindow);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(250, 180, 80, 22));
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 160, 62, 15));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "red", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "blue", nullptr));

        label->setText(QApplication::translate("MainWindow", "MyTeam", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "field1", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "field2", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "Algorithm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
