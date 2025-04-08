#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <QTextBrowser>
#include <QLCDNumber>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    GameBoard gameboard;
    void onTimerTimeout();


private slots:
    void resetGameBoard();
    void changeDefaultColors();
    void setDefaultColor();

private:
    Ui::MainWindow *ui;

    const int BUTTON_HEIGHT = 40;
    const int BUTTON_WIDTH = 40;

    std::vector<QPushButton*> buttons_;
    std::vector<int> coordinates_;
    std::vector<QPushButton*> colorButtons_;

    QWidget* gameArea;
    QGridLayout* gameLayout;

    QTextBrowser* text_browser_;
    QPushButton* reset_button_;
    QPushButton* colorChangeButton_;
    QPushButton* greenButton_;
    QPushButton* redButton_;
    QPushButton* yellowButton_;
    QPushButton* magentaButton_;
    QPushButton* cyanButton_;

    int firstIndex_ = 0;
    int secondIndex_ = 0;
    int moveCounter = 0;

    QLCDNumber* LcdSeconds;
    QLCDNumber* LcdMinutes;
    QLabel* minuteLabel;
    QLabel* secondLabel;
    QTimer* timer_ = nullptr;
    int seconds_ = 0;
    int minutes_ = 0;

    QBrush defaultColor1_ = Qt::red;
    QBrush defaultColor2_ = Qt::green;
    QBrush emptyColor_ = Qt::white;
    QPalette defaultButton1_;
    QPalette defaultButton2_;
    QPalette emptyButton_;
    int colorButtonsPressed = 0;

    void createGameBoard();
    void pushButtonClicked();
    void createTextBrowser();
    void createResetButton();
    void createTimer();
    void updateView();
    void printInfo();
    void updateGameboard(Point startingPoint, Point endPoint);
    void createColorChangeButton();
    void showColorOptions();
};
#endif // MAINWINDOW_HH
