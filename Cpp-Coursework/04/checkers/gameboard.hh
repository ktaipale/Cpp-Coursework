/* * Ohjelman kirjoittaja
 * Nimi: Kristian Taipale
 * Opiskelijanumero: H246385
 * Käyttäjätunnus: taipalek
 * E-Mail: kristian.taipale@tuni.fi
 * */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>

// Pelilaudan koko
const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka
class GameBoard
{
public:
    // Rakentaja: tarvittaessa voit lisätä parametreja
    GameBoard();

    // Tulostaa pelilaudan (kunhan olet viimeistellyt metodin).
    void print() const;

    // Asettaa pelilaudalla käytettävän merkin nappuloille.
    void setCharacter(char c);

    // Siirtää ja syö nappulan, mikäli siirto on sallittu.
    void movePiece(std::vector<std::string> coordinates);

    // Palauttaa tiedon siitä, onko peli syytä lopettaa.
    bool isGameOver();

    // Tulostaa käytetyjen siirtojen määrän.
    void printMoveCounter();

    // Tulostaa jäljellä olevien nappuloiden määrän.
    void printRemainingPieces();

private:
    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
    void print_line(unsigned int length, char fill_character) const;

    // Muuttujia, jotka seuraavat pelilaudan ja pelin tilaa.
    char pieceCharacter_;
    int piecesLeft_ = 48;
    int movesUsed_ = 0;

    // Pelilaudan oletustila ohjelman käynnistyessä.
    std::vector<std::vector<int>> gameGrid = {{1, 1, 1, 1, 1, 1, 1, 1},
                                              {1, 1, 1, 1, 1, 1, 1, 1},
                                              {1, 1, 0, 0, 0, 0, 1, 1},
                                              {1, 1, 0, 0, 0, 0, 1, 1},
                                              {1, 1, 0, 0, 0, 0, 1, 1},
                                              {1, 1, 0, 0, 0, 0, 1, 1},
                                              {1, 1, 1, 1, 1, 1, 1, 1},
                                              {1, 1, 1, 1, 1, 1, 1, 1}};
};

#endif // GAMEBOARD_HH
