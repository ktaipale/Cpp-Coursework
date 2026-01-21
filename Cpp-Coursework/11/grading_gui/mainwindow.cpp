#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);
    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);

    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::onCountButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCountButtonClicked()
{
    int N_points = ui->spinBoxN->value();
    int G_points = ui->spinBoxG->value();
    int P_points = ui->spinBoxP->value();
    int E_points = ui->spinBoxE->value();
    int Weeklies = score_from_weekly_exercises(N_points, G_points);
    int Projects = score_from_projects(P_points);
    int grade = calculate_total_grade(N_points, G_points, P_points, E_points);
    ui->textBrowser->setText(QString("W-Score: ").append(QString::number(Weeklies)) + "\n" +
                             QString("P-Score: ").append(QString::number(Projects)) + "\n" +
                             QString("Total grade: ").append(QString::number(grade)));
}

