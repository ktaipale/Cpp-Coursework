#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gradecalculator.hh"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCountButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
