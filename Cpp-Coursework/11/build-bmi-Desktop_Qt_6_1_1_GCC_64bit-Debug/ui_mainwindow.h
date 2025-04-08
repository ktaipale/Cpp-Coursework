/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *countButton;
    QPushButton *closeButton;
    QTextBrowser *infoTextBrowser;
    QLabel *weightLabel;
    QLabel *heightLabel;
    QLabel *kg;
    QLabel *cm;
    QLabel *BMI;
    QLabel *info;
    QFrame *line;
    QLabel *resultLabel;
    QLineEdit *weightLineEdit;
    QLineEdit *heightLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        countButton = new QPushButton(centralwidget);
        countButton->setObjectName(QString::fromUtf8("countButton"));
        countButton->setGeometry(QRect(60, 160, 84, 28));
        closeButton = new QPushButton(centralwidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(60, 360, 84, 28));
        infoTextBrowser = new QTextBrowser(centralwidget);
        infoTextBrowser->setObjectName(QString::fromUtf8("infoTextBrowser"));
        infoTextBrowser->setGeometry(QRect(150, 270, 161, 91));
        weightLabel = new QLabel(centralwidget);
        weightLabel->setObjectName(QString::fromUtf8("weightLabel"));
        weightLabel->setGeometry(QRect(70, 70, 63, 20));
        heightLabel = new QLabel(centralwidget);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
        heightLabel->setGeometry(QRect(70, 110, 63, 20));
        kg = new QLabel(centralwidget);
        kg->setObjectName(QString::fromUtf8("kg"));
        kg->setGeometry(QRect(270, 60, 63, 20));
        cm = new QLabel(centralwidget);
        cm->setObjectName(QString::fromUtf8("cm"));
        cm->setGeometry(QRect(270, 110, 63, 20));
        BMI = new QLabel(centralwidget);
        BMI->setObjectName(QString::fromUtf8("BMI"));
        BMI->setGeometry(QRect(60, 240, 63, 20));
        info = new QLabel(centralwidget);
        info->setObjectName(QString::fromUtf8("info"));
        info->setGeometry(QRect(60, 270, 63, 20));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(60, 210, 251, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(150, 240, 111, 20));
        weightLineEdit = new QLineEdit(centralwidget);
        weightLineEdit->setObjectName(QString::fromUtf8("weightLineEdit"));
        weightLineEdit->setGeometry(QRect(150, 60, 113, 28));
        heightLineEdit = new QLineEdit(centralwidget);
        heightLineEdit->setObjectName(QString::fromUtf8("heightLineEdit"));
        heightLineEdit->setGeometry(QRect(150, 110, 113, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(closeButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        countButton->setText(QCoreApplication::translate("MainWindow", "Count", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        weightLabel->setText(QCoreApplication::translate("MainWindow", "Weight:", nullptr));
        heightLabel->setText(QCoreApplication::translate("MainWindow", "Height:", nullptr));
        kg->setText(QCoreApplication::translate("MainWindow", "kg", nullptr));
        cm->setText(QCoreApplication::translate("MainWindow", "cm", nullptr));
        BMI->setText(QCoreApplication::translate("MainWindow", "BMI:", nullptr));
        info->setText(QCoreApplication::translate("MainWindow", "Info:", nullptr));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
