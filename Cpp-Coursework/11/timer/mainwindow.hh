#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer = nullptr;

private slots:
    // Add your slots here
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onResetButtonClicked();
    void onCloseButtonClicked();
    void onTimerTimeout();

private:
    Ui::MainWindow *ui;
    // Add other necessary members here
    int seconds_ = 0;
    void updateView();
};

#endif // MAINWINDOW_HH
