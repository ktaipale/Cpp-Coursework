/* * Ohjelman kirjoittaja
 * Nimi: Kristian Taipale
 * Opiskelijanumero: H246385
 * Käyttäjätunnus: taipalek
 * E-Mail: kristian.taipale@tuni.fi
 * */

#include "gameboard.hh"
#include <iostream>
#include <cmath>

GameBoard::GameBoard()
{

}

// Funktio tulosta pelilaudan annetulla merkillä pieceCharacter_.
void GameBoard::print() const
{
    // Tulostetaan yläreuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            // Tulosta tässä tyhjä tai pelilaudan alkio (i, j)
            if(gameGrid.at(i).at(j) == 1)
            {
                std::cout << pieceCharacter_ << " ";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

// Funktio asettaa nappulalle käytettävän merkin pelaajan syötteestä.
void GameBoard::setCharacter(char c)
{
    pieceCharacter_ = c;
}

// Funktio saa parametreinaan käyttäjän syöttämät hyväksytyksi tarkastetut
// koordinaatit. Funktio tarkastaa, onko siirto laillinen ja mikäli näin on,
// toteuttaa siirron. Muussa tapauyksessa funktio ei tee muuta kuin tulostaa
// ilmoituksen väärän laisesta siirrosta.
void GameBoard::movePiece(std::vector<std::string> coordinates)
{
    // Tallennetaan coordinates-vektorista arvot luettavampaan muotoon.
    int startingCoordinateX = std::stoi(coordinates.at(0));
    int startingCoordinateY = std::stoi(coordinates.at(1));
    int moveCoordinateX = std::stoi(coordinates.at(2));
    int moveCoordinateY = std::stoi(coordinates.at(3));
    int eatenCoordinateX = (startingCoordinateX + moveCoordinateX) / 2;
    int eatenCoordinateY = (startingCoordinateY + moveCoordinateY) / 2;

    // Funktio tarkastaa, että alkupisteessä on nappula, loppupisteessä ei ole
    // nappulaa, että nappula liikkuu kulmittain sekä sen, että ylitettävässä
    // ruudussa on nappi, joka tulee syödyksi. Mikäli kaikki ehdot täyttyvät,
    // on siirto sallittu ja nappula siirretään sekä ylitetty nappula syödään.
    if(gameGrid.at(startingCoordinateY - 1).at(startingCoordinateX - 1) == 1 &&
            gameGrid.at(moveCoordinateY - 1).at(moveCoordinateX - 1) == 0 &&
            std::abs(startingCoordinateX - moveCoordinateX) == 2 &&
            std::abs(startingCoordinateY - moveCoordinateY) == 2 &&
            gameGrid.at(eatenCoordinateY - 1).at(eatenCoordinateX - 1) == 1)
    {
        // Muutetaan gameGrid:n tilaa oikeanlaiseksi sekä muutetaan pelilaudan
        // tilaa tarkkailevien muuttujien tilaa, jotta pelin päätösruudussa
        // saadaan tulostettua halutut tiedot. Pelilaudan uusi tila tulostetaan
        // ennen uuden syötteen kysymistä oikeanlaisen siirron tekemisen
        // helpottamiseksi.
        gameGrid.at(startingCoordinateY - 1).at(startingCoordinateX - 1) = 0;
        gameGrid.at(moveCoordinateY - 1).at(moveCoordinateX - 1) = 1;
        gameGrid.at(eatenCoordinateY - 1).at(eatenCoordinateX - 1) = 0;
        piecesLeft_--;
        movesUsed_++;
        print();
    }
    else
    {
        std::cout << "Cannot move from start point to destination point.";
        std::cout << std::endl;
    }
}

// Funktio tarkastaa pelilaudan piecesLeft_ muuttujasta, onko peli syytä
// lopettaa (onko arvo 1). Funktio palauttaa tiedon pelin lopettamisesta.
bool GameBoard::isGameOver()
{
    if(piecesLeft_ == 1)
    {
        return true;
    }
    return false;
}

// Funktio tulostaa käytettyjen siirtojen määrän sitä kutsuttaessa.
void GameBoard::printMoveCounter()
{
    std::cout << movesUsed_;
}

// Funktio tulostaa jäljellä olevien nappuloiden määrän sitä kutsuttaessa.
void GameBoard::printRemainingPieces()
{
    std::cout << piecesLeft_;
}

// Funktio tulostaa pelilaudan kiinteät osat.
void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}
