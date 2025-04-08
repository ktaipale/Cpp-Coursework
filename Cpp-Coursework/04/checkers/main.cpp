/* Tammipeli (yhdelle pelaajalle)
 *
 * Kuvaus:
 *   Ohjelma toteuttaa tammipelin yhdelle pelaajalle. Pelilaudan koko
 * on 8 x 8, ja se täytetään tyhjillä sekä pelinappuloilla, jotka käyttäjä
 * valitsee itse ohjelman käynnistyessä. Pelilauta on aluksi täynnä
 * nappuloita, mutta keskellä on 4 x 4 -kokoinen alue tyhjää.
 * Tarkoitus on saada pelilauta tyhjennettyä niin, että jäljellä on
 * vain yksi pelinappula (joka ei tässä ohjelmassa ole koskaan mahdollista,
 * mutta ohjelma on tehty ohjeiden mukaan niin, että sen oletetaan olevan
 * mahdollista). Nappulaa voi siirtää viistosti toisen nappulan yli,
 * jolloin poistetaan se nappula, jonka yli hypättiin.
 *   Joka kierroksella käyttäjältä kysytään kahta pistettä (neljää
 * koordinaattia): siirrettävää nappulaa ja sen kohdesijaintia.
 * Ohjelma tarkistaa, voidaanko siirto tehdä.
 *   Ohjelma päättyy, kun pelilaudalla on enää yksi pelinappula tai kun
 * käyttäjä antaa lopetuskomennon (merkki 'q' tai 'Q'). Tällöin ohjelma
 * tulostaa, kuinka monta siirtoa tehtiin ja kuinka monta nappulaa on
 * vielä jäljellä.
 *
 * Ohjelman kirjoittaja
 * Nimi: Kristian Taipale
 * Opiskelijanumero: H246385
 * Käyttäjätunnus: taipalek
 * E-Mail: kristian.taipale@tuni.fi
 *
 * */

#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

// Funktio ottaa parametreinaan käyttäjältä luetun merkkijonon,
// jakaa sen osiin välilyöntien kohdalta ja palauttaa vektorin,
// johon merkkijonon osat on lisätty.
vector<string> split(string line,
                     char sep,
                     bool ignore_empty = false)
{
    vector<string> splitted_vector = {};
    string substring = "";

    while(line.find(sep) != string::npos)
    {
        substring = line.substr(0, line.find(sep));
        line = line.substr(line.find(sep)+1, string::npos);

        if(!(ignore_empty && substring.empty()))
        {
            splitted_vector.push_back(substring);
        }
    }
    if(!(ignore_empty && line.empty()))
    {
        splitted_vector.push_back(line);
    }
    return splitted_vector;
}

int main()
{    
    // Luodaan pelilauta ja ohjelmassa käytettävät muuttujat.
    // piece-muuttuja määritellään "tyhjäksi", jotta sille
    // ei erikseen tarvitse määritellä jotakin alutilaa.
    GameBoard gameboard;
    string line;
    char piece = '\0';
    bool gameOver = false;
    bool validInput;
    vector<string> coordinates;

    // Kysytään käyttäjältä nappuloina käytettävää merkkiä niin
    // kauan, kuin sellainen saadaan hyväksytyssä muodossa.
    while(!piece)
    {
        cout << "Enter piece character: ";
        getline(cin, line);
        if(line.size() == 1)
        {
            piece = line.at(0);
            // Asetetaan pelilaudan merkiksi saatu merkki.
            gameboard.setCharacter(piece);
        }
    }

    // Kun merkki on saatu, tulostetaan pelilauta ensimmäisen kerran
    // käyttäen gameboard-olion metodia print.
    gameboard.print();

    // Peliä pidetään käynnissä, kunnes peli päättyy (gameOver = true).
    while(!gameOver)
    {
        // Palautetaan muuttujat oletustilaansa, jotta edellisen
        // while loopin jäljiltä olevat arvot eivät sotke ohjelman toimintaa.
        validInput = true;
        coordinates.clear();

        cout << "Enter start point (x, y) and";
        cout << " destination point (x, y), or q to quit: ";
        getline(cin, line);
        coordinates = split(line, ' ', true);

        // Jos syötettyjä arvoja on vain yksi, tarkastetaan onko kyseinen arvo
        // q tai Q, jolloin ohjelman suoritus lopetetaan. Muussa tapauksessa
        // kyseessä on virheellinen syöte ja syötettä kysytään uudelleen.
        if(coordinates.size() == 1)
        {
            if(coordinates.at(0) == "q" || coordinates.at(0) == "Q")
            {
                gameOver = true;
                gameboard.printMoveCounter();
                cout << " move(s) made." << endl;
                gameboard.printRemainingPieces();
                cout << " piece(s) left.";
                break;
            }
        }

        // Jos syötteitä on haluttu 4 kappaletta, tarkastetaan ovatko syötteet
        // sallittuja (ovatko numeroita ja pelilaudan sisällä). Virheellisen
        // syötteen kohdalla validInput = false, jotta gameboardin metodia
        // movePiece ei kutsuta turhaan väärillä syötteillä.
        if(coordinates.size() == 4)
        {
            for(int i = 0; i < 4; i++)
            {
                int coordinate;
                string mark = coordinates.at(i);
                if(isdigit(mark.at(0)) == 0)
                {
                    cout << "Invalid start/destination point." << endl;
                    validInput = false;
                    break;

                }
                coordinate = stoi(mark);

                if(coordinate < 1 || coordinate > 8)
                {
                    cout << "Invalid start/destination point." << endl;
                    validInput = false;
                    break;
                }
            }

            if(validInput)
            {
                // gameboard-olion movePiece hoitaa nappuloiden siirtelyn
                // annetuilla koordinaateilla.
                gameboard.movePiece(coordinates);
            }

        }
        else
        {
            cout << "Invalid start/destination point." << endl;
        }

        // while loopin lopussa tarkastetaan aina, onko peli syytä lopettaa.
        gameOver = gameboard.isGameOver();
    }

    return 0;
}
