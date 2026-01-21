#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::on_countButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked()
{
    QString WEIGHT = ui->weightLineEdit->text();
    double weight = WEIGHT.toDouble();
    QString HEIGHT = ui->heightLineEdit->text();
    double height = HEIGHT.toDouble() / 100;
    double bmi = weight / pow(height, 2);

    if (bmi == INFINITY)
    {
        ui->resultLabel->setText(QString("Cannot count"));
        ui->infoTextBrowser->setText(QString(""));
    }
    else if(bmi > 25)
    {
        ui->resultLabel->setText(QString::number(bmi));
        ui->infoTextBrowser->setText(QString("Overweight"));
    }
    else if(bmi < 18.5)
    {
        ui->resultLabel->setText(QString::number(bmi));
        ui->infoTextBrowser->setText(QString("Underweight"));
    }
    else if (bmi < 25 && bmi > 0)
    {
        ui->resultLabel->setText(QString::number(bmi));
        ui->infoTextBrowser->setText(QString("Normal range"));
    }
}

