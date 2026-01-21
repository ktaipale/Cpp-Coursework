#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_findPushButton_clicked()
{
    QString filename = ui->fileLineEdit->text();
    string file = filename.toStdString();
    QString findwhat = ui->keyLineEdit->text();
    string find = findwhat.toStdString();
    ifstream readfile(file);
    if(!readfile || file.size() == 0)
    {
        ui->textBrowser->setText(QString("File not found").append(QString(findwhat)));
    }
    else if(find.size() == 0)
    {
        ui->textBrowser->setText(QString("File found"));
    }
    else
    {
        string line;
        while(getline(readfile, line))
        {
            if(!ui->matchCheckBox->isChecked())
            {
                transform(line.begin(), line.end(), line.begin(), ::toupper);
                transform(find.begin(), find.end(), find.begin(), ::toupper);
                ui->textBrowser->setText(QString("is upper"));
            }
            if(line.find(find) != string::npos)
            {
                ui->textBrowser->setText(QString("Word found"));
                return;
            }
        }
        ui->textBrowser->setText(QString("Word not found"));
    }
    readfile.close();
}

