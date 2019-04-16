/********************************************************************************
** Form generated from reading UI file 'AnalyzeField.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEFIELD_H
#define UI_ANALYZEFIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalyzeField
{
public:

    void setupUi(QWidget *AnalyzeField)
    {
        if (AnalyzeField->objectName().isEmpty())
            AnalyzeField->setObjectName(QStringLiteral("AnalyzeField"));
        AnalyzeField->resize(400, 300);

        retranslateUi(AnalyzeField);

        QMetaObject::connectSlotsByName(AnalyzeField);
    } // setupUi

    void retranslateUi(QWidget *AnalyzeField)
    {
        AnalyzeField->setWindowTitle(QApplication::translate("AnalyzeField", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeField: public Ui_AnalyzeField {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEFIELD_H
