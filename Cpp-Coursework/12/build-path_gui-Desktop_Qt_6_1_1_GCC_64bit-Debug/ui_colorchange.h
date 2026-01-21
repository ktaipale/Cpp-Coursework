/********************************************************************************
** Form generated from reading UI file 'colorchange.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORCHANGE_H
#define UI_COLORCHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_colorchange
{
public:

    void setupUi(QDialog *colorchange)
    {
        if (colorchange->objectName().isEmpty())
            colorchange->setObjectName(QString::fromUtf8("colorchange"));
        colorchange->resize(400, 300);

        retranslateUi(colorchange);

        QMetaObject::connectSlotsByName(colorchange);
    } // setupUi

    void retranslateUi(QDialog *colorchange)
    {
        colorchange->setWindowTitle(QCoreApplication::translate("colorchange", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class colorchange: public Ui_colorchange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORCHANGE_H
