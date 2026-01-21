/* Polku
 * Kuvaus:
 * Ohjelmassa on toteutettu Polku-pelin graafinen käyttöliittymä valmiin
 * koodipohjan päälle. Pelin ideana on saada siirrettyä vihreät nappulat
 * vastakkaiselle puolelle ja punaiset nappulat vastakkaiselle puolelle
 * pelilautaa. Pelissä on värinvaihto-ominaisuus, joka toimii pelin ollessa
 * aloitustilassa. Aloitustilaan pääsee painamalla reset-nappulaa. Värinvaihto
 * toimii painamalla "Change Color" nappia ja sen jälkeen valitsemalla kaksi
 * eri väriä. Pelistä löytyy myös ajastin, jolla pelaaja voi mitata peliin
 * kulunutta aikaa. Peli ilmoittaa tehtyjen siirtojen määrästä ja turhien
 * eli paikallaan tehtyjen siirtojen tekemisestä on tehty mahdotonta.
 *
 * Ohjelman kirjoittaja
 * Nimi: Kristian Taipale
 * Opiskelijanumero: H246385
 * Käyttäjätunnus: taipalek
 * E-mail: kristian.taipale@tuni.fi
 *
 *
 * */
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QString>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGameBoard();
    createTextBrowser();
    createResetButton();
    createTimer();
    createColorChangeButton();
    showColorOptions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGameBoard()
{
    //Jos ajastin on päällä, se pysäytetään ja asetetaan nollaan
    //sekä muuttujan että lcd-näytön osalta.
    if(timer_)
    {
        timer_->stop();
        seconds_ = 0;
        LcdSeconds->display(seconds_);
    }

    colorChangeButton_->setEnabled(true);

    //Poistetaan koordinaateista viimeiset kaksi pistettä (yksi kokonainen
    //koordinaatti), mikäli vain aloituspisteen koordinaatit on syötetty
    //Reset-nappia painettaessa. Poistamalla ylimääräinen koordinaatti
    //vältetään ohjelman kaatuminen tilanteessa, jossa koordinaatteja on
    //pariton määrä.
    if(coordinates_.size() % 4 != 0)
    {
        coordinates_.pop_back();
        coordinates_.pop_back();
    }

    //Käydään kaikki coordinates_-muuttujaan tallennetut koordinaatit
    //läpi takaperin ja palautetaan nappulat tätä kautta alkuperäisiin
    //paikkoihinsa sekä palautetaan niiden värit oikeiksi.
    unsigned int coordinateAmount = coordinates_.size();
    while(coordinateAmount > 0)
    {
        Point startingPoint = {coordinates_.at(coordinateAmount - 2),
                               coordinates_.at(coordinateAmount - 1)};
        Point endPoint = {coordinates_.at(coordinateAmount - 4),
                          coordinates_.at(coordinateAmount - 3)};

        if(gameboard.move(startingPoint, endPoint))
        {
            QPushButton* firstButton = buttons_.at(startingPoint.x +
                                                   startingPoint.y * 4);
            QPushButton* secondButton = buttons_.at(endPoint.x +
                                                    endPoint.y * 4);

            QBrush redBrush(Qt::red);
            QPalette redButton;
            redButton.setBrush(QPalette::Button, redBrush);

            QBrush greenBrush(Qt::green);
            QPalette greenButton;
            greenButton.setBrush(QPalette::Button, greenBrush);

            QBrush whiteBrush(Qt::white);
            QPalette whiteButton;
            whiteButton.setBrush(QPalette::Button, whiteBrush);

            if(gameboard.which_slot(endPoint) == 0 &&
                    gameboard.which_slot(startingPoint) == 2)
            {
                firstButton->setPalette(whiteButton);
                secondButton->setPalette(redButton);
            }

            if(gameboard.which_slot(endPoint) == 1 &&
                    gameboard.which_slot(startingPoint) == 2)
            {
                firstButton->setPalette(whiteButton);
                secondButton->setPalette(greenButton);
            }
        }
        coordinateAmount -= 4;
    }

    //Kun kaikki koordinaatit on käyty läpi ja nappulat palautettu
    //alkuperäisille paikoilleen, palautetaan muuttujat ja graafinen
    //käyttöliittymä alkuperäiseen tilaansa.
    coordinates_.clear();
    text_browser_->setText("");
    moveCounter = 0;

    //Asetetaan kaikki nappulat jälleen klikattaviksi.
    for(auto button : buttons_)
    {
        button->setEnabled(true);
    }
    std::vector<std::vector<Slot_type>> board = gameboard.getBoard();

    //Asetetaan tyhjät paikat klikkaamattomiksi pelin alkaessa,
    //jotta ohjelmassa vältytään turhien siirtojen kirjaamiselta
    //coordinates_-muuttujaan sekä niiden aiheuttamilta bugeilta.
    for(unsigned int i = 0; i < board.size(); ++i)
    {
        for(unsigned int j = 0; j < board.at(i).size(); j++)
        {
            if(board.at(i).at(j) == 2)
            {
                buttons_.at(j + 4*i)->setEnabled(false);
            }
        }
    }
}

void MainWindow::pushButtonClicked()
{
    //Kun ensimmäinen koordinaatti kirjataan ylös, peli alkaa
    //ja pelikello laitetaan käyntiin.
    if(coordinates_.size() == 2)
    {
        timer_->start();
        colorChangeButton_->setEnabled(false);
    }

    //Käydään pushButtonit läpi, jotta löydetään klikattu
    //pushButton sender() ja kasvatetaan indexiä, jotta
    //myöhempää käyttöä varten tiedetään sen sijainti.
    int buttonIndex = 0;
    for (auto& button : buttons_)
    {
        if(button != sender())
        {
            buttonIndex++;
        }
        else
        {
            break;
        }
    }

    //Indexin avulla saadaan pushButton:n koordinaatit.
    //jakamalla luku 4:llä saadaan y-koordinaatti eli millä rivillä
    //pushButton sijaitsee ja jakojäännöksestä saamme x-koordinaatin.
    //Uusin koordinaatti on aina viimeisenä, joten tämä tallennetaan
    //secondIndex_-muuttujaan ja edellinen siirretään firstIndex_-muuttujaan.
    coordinates_.push_back(buttonIndex % 4);
    coordinates_.push_back(buttonIndex / 4);
    firstIndex_ = secondIndex_;
    secondIndex_ = buttonIndex;

    //Koordinaattien avulla muodostetaan Point-muuttujat, jotka voidaan
    //lähettää pohjakoodin move-funktiolle, joka toteuttaa siirrot, mikäli
    //mahdollista. Tämä tilanteessa, jossa kaksi nappulaa on painettu.
    if(coordinates_.size() % 4 == 0)
    {
        Point startingPoint = {coordinates_.at(coordinates_.size() - 4),
                               coordinates_.at(coordinates_.size() - 3)};
        Point endPoint = {coordinates_.at(coordinates_.size() - 2),
                          coordinates_.at(coordinates_.size() - 1)};

        //Tarkistetaan, että klikatut nappulat eivät sijaitse samassa
        //pisteessä, koska näitä ei haluta kirjata tehtyjen siirtojen määrään.
        //Pohjakoodissa siirron tekeminen samaan pisteeseen oli sallittua.
        bool samePoints = false;
        if(startingPoint.x == endPoint.x && startingPoint.y == endPoint.y)
        {
            samePoints = true;
        }

        //Mikäli tehty siirto on sallitty, se tehdään ja kirjataan se ylös
        // siirtolaskuriin. Samalla päivitetään graafinen käyttöliittymä
        //vastaamaan pelin nykytilaa
        if(gameboard.move(startingPoint, endPoint) && !samePoints)
        {
            moveCounter++;
            updateGameboard(startingPoint, endPoint);
            printInfo();
        }

        //Siirron jälkeen asetetaan uudet tyhjät paikat klikkaamattomiksi.
        std::vector<std::vector<Slot_type>> board = gameboard.getBoard();
        for(unsigned int i = 0; i < board.size(); ++i)
        {
            for(unsigned int j = 0; j < board.at(i).size(); j++)
            {
                if(board.at(i).at(j) == 2)
                {
                    buttons_.at(j+4*i)->setEnabled(false);
                }
            }
        }
    }

    //Mikäli vain yksi nappula on painettu, asetetaan kaikki nappulat jälleen
    //painettaviksi, koska klikattu värillinen nappi on pystyttävä
    //liikuttamaan tyhjään kohtaan.
    else
    {
        for(auto button : buttons_)
        {
            button->setEnabled(true);
        }
    }
}

//Funktio luo QTextBrowser-widgetin ja asettaa sen sijainnin sekä koon.
void MainWindow::createTextBrowser()
{
    text_browser_ = new QTextBrowser(this);
    text_browser_->setGeometry(398, 170, 130, 70);
}

//Funktio luo QPushButtonin ja asettaa sen sijainnin, värin sekä koon.
//ResetButtonin klikkaus yhdistetään funktioon, joka palauttaa
//pelin ja graafisen käyttöliittymän alkutilaansa.
void MainWindow::createResetButton()
{
    reset_button_ = new QPushButton(this);
    reset_button_->setText("Reset Game");
    reset_button_->setGeometry(411, 250, 100, 40);
    reset_button_->setStyleSheet("color: red");

    connect(reset_button_, SIGNAL(clicked()),
            this, SLOT(resetGameBoard()));
}

//Funktio luo pelin ajastimen sekä lcdnumber-näytön. Funktio luo myös
//QLabel-widgetit, jotka näyttävät tekstejä "minutes" ja "seconds".
//Funktio myös asettaa lcdnumberin sijainnin sekä koon. Ajastin yhdistetään
//onTimerTimeout funktioon, joka hyödyntää ajastimen toimintaa.
void MainWindow::createTimer()
{
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::onTimerTimeout);

    minuteLabel = new QLabel(this);
    minuteLabel->setText("Minutes");
    minuteLabel->setGeometry(404, 83, 55, 13);

    secondLabel = new QLabel(this);
    secondLabel->setText("Seconds:");
    secondLabel->setGeometry(466, 83, 55, 13);

    LcdSeconds = new QLCDNumber(this);
    LcdSeconds->setDigitCount(2);
    LcdSeconds->display("0");
    LcdSeconds->setGeometry(461,100,62,50);

    LcdMinutes = new QLCDNumber(this);
    LcdMinutes->setDigitCount(2);
    LcdMinutes->display("0");
    LcdMinutes->setGeometry(401,100,62,50);
}

//Funktio kasvattaa peliin kuluneen ajan määrää aina, kun QTimer:n timeout
//tapahtuu, eli aina 1000 millisekunnin välein, jolloin funktio kutsuu
//updateView-funktiota.
void MainWindow::onTimerTimeout()
{
    seconds_++;
    updateView();
}

//Funktio päivittää lcdnumberin tilan aina, kun sekunti on kulunut.
void MainWindow::updateView()
{
    minutes_ = seconds_/60;
    int remainingSeconds = seconds_%60;

    LcdMinutes->display(minutes_);
    LcdSeconds->display(remainingSeconds);
}

//Funktio päivittää ja tulostaa tiedon käytetyistä siirroista aina, kun siirto
//on tehty. Funktio myös tarkastaa jokaisen siirron jälkeen, mikäli peli
//on läpäisty. Pelin läpäisyn hetkellä tulostuu oma viestinsä, pelikello
//pysäytetään ja pelin painikkeet poistetaan käytöstä, kunnes reset-nappia
//on painettu. Funktio tulostaa kaikki tekstinsä QTextBrowser-widgettiin.
void MainWindow::printInfo()
{
    if(gameboard.is_game_over() == true)
    {
        text_browser_->setText("Game Completed! \nMoves used: " +
                       QString::fromStdString(std::to_string(moveCounter)));
        if(timer_)
        {
            timer_->stop();
        }
        for(auto button : buttons_)
        {
            button->setEnabled(false);
        }
    }
    else
    {
        text_browser_->setText("Moves used: " +
                       QString::fromStdString(std::to_string(moveCounter)));
    }
}

//Funktio ottaa parametreinaan siirretyn nappulan alku- ja loppupisteen.
//Funktio tarkastelee, mitä tyyppiä alkupisteen nappi oli (punainen tai vihreä)
//ja muuttaa alku- ja loppupisten värit keskenään.
void MainWindow::updateGameboard(Point endPoint, Point startingPoint)
{
    QPushButton* firstButton = buttons_.at(firstIndex_);
    QPushButton* secondButton = buttons_.at(secondIndex_);

    defaultButton1_.setBrush(QPalette::Button, defaultColor1_);
    defaultButton2_.setBrush(QPalette::Button, defaultColor2_);
    emptyButton_.setBrush(QPalette::Button, emptyColor_);

    if(gameboard.which_slot(startingPoint) == 0 &&
            gameboard.which_slot(endPoint) == 2)
    {
        firstButton->setPalette(emptyButton_);
        secondButton->setPalette(defaultButton1_);
    }

    if(gameboard.which_slot(startingPoint) == 1 &&
            gameboard.which_slot(endPoint) == 2)
    {
        firstButton->setPalette(emptyButton_);
        secondButton->setPalette(defaultButton2_);
    }
}

//Funktio luo uuden QPushButtonin, jolla voi avata värinvaihtonapit käyttöönsä
//Pushbutton yhdistetään changeDefaultColors-funktioon.
void MainWindow::createColorChangeButton()
{
    colorChangeButton_ = new QPushButton(this);
    colorChangeButton_->setText("Change Color");
    colorChangeButton_->setGeometry(142, 400, 100, 40);
    colorChangeButton_->setStyleSheet("color: blue"); // Setting text color
    connect(colorChangeButton_, SIGNAL(clicked()),
            this, SLOT(changeDefaultColors()));
}

//Funktio muodostaa yhden napin jokaista pelissä käytettävää väriä kohden ja
//asettaa ne pelilaudan alapuolelle.
void MainWindow::showColorOptions()
{
    QBrush greenBrush(Qt::green);
    QPalette greenButton;
    greenButton.setBrush(QPalette::Button, greenBrush);
    greenButton_ = new QPushButton(this);
    greenButton_->setGeometry(70,460,40,40);
    greenButton_->setPalette(greenButton);
    greenButton_->setEnabled(false);
    colorButtons_.push_back((greenButton_));
    connect(greenButton_, SIGNAL(clicked()),
            this, SLOT(setDefaultColor()));

    QBrush redBrush(Qt::red);
    QPalette redButton;
    redButton.setBrush(QPalette::Button, redBrush);
    redButton_ = new QPushButton(this);
    redButton_->setGeometry(120,460,40,40);
    redButton_->setPalette(redButton);
    redButton_->setEnabled(false);
    colorButtons_.push_back((redButton_));
    connect(redButton_, SIGNAL(clicked()),
            this, SLOT(setDefaultColor()));

    QBrush yellowBrush(Qt::yellow);
    QPalette yellowButton;
    yellowButton.setBrush(QPalette::Button, yellowBrush);
    yellowButton_ = new QPushButton(this);
    yellowButton_->setGeometry(170,460,40,40);
    yellowButton_->setPalette(yellowButton);
    yellowButton_->setEnabled(false);
    colorButtons_.push_back((yellowButton_));
    connect(yellowButton_, SIGNAL(clicked()),
            this, SLOT(setDefaultColor()));

    QBrush magentaBrush(Qt::magenta);
    QPalette magentaButton;
    magentaButton.setBrush(QPalette::Button, magentaBrush);
    magentaButton_ = new QPushButton(this);
    magentaButton_->setGeometry(220,460,40,40);
    magentaButton_->setPalette(magentaButton);
    magentaButton_->setEnabled(false);
    colorButtons_.push_back((magentaButton_));
    connect(magentaButton_, SIGNAL(clicked()),
            this, SLOT(setDefaultColor()));

    QBrush cyanBrush(Qt::cyan);
    QPalette cyanButton;
    cyanButton.setBrush(QPalette::Button, cyanBrush);
    cyanButton_ = new QPushButton(this);
    cyanButton_->setGeometry(270,460,40,40);
    cyanButton_->setPalette(cyanButton);
    cyanButton_->setEnabled(false);
    colorButtons_.push_back((cyanButton_));
    connect(cyanButton_, SIGNAL(clicked()),
            this, SLOT(setDefaultColor()));

}

//Funktio poistaa värinvaihtonapin käytöstä, mikäli sitä on painettu ja tähän
//funktioon päädytty. Funktio asettaa värinappulat painettaviksi ja
//poistaa pelinappulat käytöstä. Kun kahta värinappulaa on painettu, tähän
//funktioon palataan ja värinappulat poistetaan käytöstä ja pelinappulat
//otetaan käyttöön. Tällä kertaa myös pelinappulat ja pelialue poistetaan,
//koska ne tullaan luomaan uudelleen uusilla oletusväreillä.
void MainWindow::changeDefaultColors()
{
    colorChangeButton_->setEnabled(false);
    if(colorButtonsPressed == 0)
    {
        reset_button_->setEnabled(false);
        for(auto button : colorButtons_)
        {
            button->setEnabled(true);
        }
        for(auto button : buttons_)
        {
            button->setEnabled(false);
        }
    }
    if(colorButtonsPressed == 2)
    {
        for(auto button : colorButtons_)
        {
            button->setEnabled(false);
        }
        for(auto button : buttons_)
        {
            button->setEnabled(true);
        }
        colorChangeButton_->setEnabled(true);

        buttons_.clear();
        gameArea = nullptr;
        gameLayout = nullptr;
        colorButtonsPressed = 0;
        reset_button_->setEnabled(true);
        createGameBoard();
    }
}

//Funktio asettaa oletusvärit pelinappuloille. Oletusvärejä löytyy
//5 kappaletta
void MainWindow::setDefaultColor()
{
    //Laskee, millä indeksillä for-looppi on menossa ja sen perusteella
    //muuttaa defaultcoloreiden väriä.
    int colorCounter = 0;
    for(auto button : colorButtons_)
    {
        if(button == sender())
        {
            if(colorCounter == 0)
            {
                defaultColor1_ = defaultColor2_;
                defaultColor2_ =  Qt::green;
                colorButtonsPressed++;
            }
            if(colorCounter == 1)
            {
                defaultColor1_ = defaultColor2_;
                defaultColor2_ = Qt::red;
                colorButtonsPressed++;
            }
            if(colorCounter == 2)
            {
                defaultColor1_ = defaultColor2_;
                defaultColor2_ = Qt::yellow;
                colorButtonsPressed++;
            }
            if(colorCounter == 3)
            {
                defaultColor1_ = defaultColor2_;
                defaultColor2_ = Qt::magenta;
                colorButtonsPressed++;
            }
            if(colorCounter == 4)
            {
                defaultColor1_ = defaultColor2_;
                defaultColor2_ = Qt::cyan;
                colorButtonsPressed++;
            }
        }
        colorCounter++;
    }
    if(colorButtonsPressed == 2)
    {
        changeDefaultColors();
    }
}

//Funktio luo pelilaudan ja siihen kuuluvat elementit, pushButtonit,
//ja määrittää niiden koon ja värin sekä asettaa ne grid-elementin sisään.
void MainWindow::createGameBoard()
{
    gameArea = new QWidget(this);
    gameLayout = new QGridLayout(gameArea);

    //Asetetaan pelin painikkeiden välinen etäisyys x- ja y-suunnassa.
    gameLayout->setHorizontalSpacing(10);
    gameLayout->setVerticalSpacing(10);

    //Asetetaan pelilauta alkamaan 100 pikseliä oikealle ja alas
    //lähtien vasemmasta yläkulmasta. Kaksi jälkimmäistä lukua ei
    //näytä vaikuttavan gridin kokoon, mutta ne on oltava mukana.
    gameLayout->setContentsMargins(100, 100, 0, 0);

    //Luodaan kaikki oletustaustavärit napeille.

    defaultButton1_.setBrush(QPalette::Button, defaultColor1_);
    defaultButton2_.setBrush(QPalette::Button, defaultColor2_);
    emptyButton_.setBrush(QPalette::Button, emptyColor_);

    //Käydään pelilaudan kaikki kohdat läpi ja luodaan niille
    //oikean värinen painike, lisätään ne puhsButtons-vektoriin sekä
    //yhditetään niiden klikkaus pushButtonClicked-funktioon.
    std::vector<std::vector<Slot_type>> board = gameboard.getBoard();
    for(unsigned int i = 0; i < board.size(); ++i)
    {
        for(unsigned int j = 0; j < board.at(i).size(); j++)
        {
            QPushButton* pushButton = new QPushButton("", this);
            if(board.at(i).at(j) != 3)
            {
                pushButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            }
            else
            {
                pushButton->setFixedSize(0, 0);
            }
            if(board.at(i).at(j) == 0)
            {
                pushButton->setPalette(defaultButton1_);
            }

            if(board.at(i).at(j) == 1)
            {
                pushButton->setPalette(defaultButton2_);
            }
            if(board.at(i).at(j) == 2)
            {
                pushButton->setPalette(emptyButton_);
                pushButton->setEnabled(false);
            }

            buttons_.push_back((pushButton));
            if(board.at(i).at(j) != 3)
            {
                gameLayout->addWidget(pushButton, i, j);
                connect(pushButton, &QPushButton::clicked,
                        this, &MainWindow::pushButtonClicked);
            }
        }
    }

    //Asetetaan lopuksi pelialueen nappulat tiiviimmin. Gridin asettelu
    //on luonnostaan erittäin väljä.
    gameLayout->setColumnStretch(5, 1);
    gameLayout->setRowStretch(5, 1);
    setCentralWidget(gameArea);
}
