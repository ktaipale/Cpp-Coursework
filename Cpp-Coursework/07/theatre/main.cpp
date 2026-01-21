/* COMP.CS.110 Project 2: Theatre
 * ===========================
 * Tekijä: Kristian Taipale
 * Opiskelijanumero: 246385
 *
 * Ohjelma ottaa käyttäjältä syötteitä ja tekee niiden
 * pohjalta hakuja teatterin tietoihin. Aluksi ohjelma lukee syötetiedoston
 * ja tallentaa tämän tiedot tietorakenteeseen. Ohjelman toimintoja ovat
 * theatres, joka tulostaa kaikki tunnetut teatterit aakkosjärjestyksessä,
 * plays, joka tulostaa kaikki tunnetut näytelmät aakkosjärjestyksessä,
 * theatres_of_play, joka tulostaa teatterit, joissa annettu näytelmä
 * esitetään, plays_in_theatre, joka tulostaa annetun teatterin näytelmät
 * aakkosjärjestyksessä, plays_in_town, joka tulostaa tietyn paikkakunnan
 * näytemät, joissa on vapaita paikkoja sekä players_in_play, joka
 * tulostaa kaikki annetun näytelmän näyttelijät.
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const string PROMPT = "the> ";

// Error and other messages
const string EMPTY_FIELD = "Error: empty field in line ";
const string FILE_ERROR = "Error: input file cannot be opened";
const string WRONG_PARAMETERS = "Error: wrong number of parameters";
const string THEATRE_NOT_FOUND = "Error: unknown theatre";
const string PLAY_NOT_FOUND = "Error: unknown play";
const string PLAYER_NOT_FOUND = "Error: unknown player";
const string TOWN_NOT_FOUND = "Error: unknown town";
const string COMMAND_NOT_FOUND = "Error: unknown command";
const string NOT_AVAILABLE = "No plays available";

// Tietorakenne, johon näytelmän tiedot tallennetaan
struct Play {
    std::string theatre;
    std::string act;
    std::string actor;
    int seats;
};

// Casual split function, if delim char is between "'s, ignores it.
vector<string> split(const string& str, char delim)
{
    vector<string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    return result;
}

// Funktio ottaa parametrinaan map:n, johon tallennetaan string-Play pareja,
// joiden avulla tiedoston tietoja voidaan myöhemmin hakea. Funktio palauttaa
// bool-arvon tosi, mikäli tiedoston luku onnistuu.
bool readFile(std::ifstream &input_file, std::map<std::string,
              std::vector<Play>> &acts)
{
    int line_counter = 1;   // Rivilaskuri virhetulostusta varten
    std::string line;
    std::vector<std::string> parts;

    while(std::getline(input_file, line))
    {
        parts = split(line, ';');
        if (parts.size() != NUMBER_OF_FIELDS)
        {   std::cout << EMPTY_FIELD << line_counter << std::endl;
            return false;
        }

        for (const std::string& string : parts)
        {
            if (string.size() == 0)
            {
                return false;
            }
        }

        // Tarkastetaan, onko syötetiedostossa viimeisessä sarakkeessa
        // none, jolloin sitä pitää käsitellä string-tyyppisenä int:n sijaan.
        // Lopuksi Play-tietorakenteet tallennetaan map-tietorakenteeseen.
        if (parts.at(4) == "none")
        {
            Play play = {parts.at(1),
                         parts.at(2),
                         parts.at(3),
                         0};
            acts[parts.at(0)].push_back(play);
        }
        else
        {
            Play play = {parts.at(1),
                         parts.at(2),
                         parts.at(3),
                         stoi(parts.at(4))};
            acts[parts.at(0)].push_back(play);
        }

        line_counter ++;
    }
    return true;
}

// Funktio ottaa parametrinaan vektorin, jossa on tallennettuna
// tulostettavat tiedot ja tulostaa ne aakkosjärjestyksessä.
void printAlphabetically(std::vector<std::string> vector)
{
    std::sort(vector.begin(), vector.end());
    for(std::string s : vector)
    {
        std::cout << s << std::endl;
    }
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja. Funktio lisää syötetiedoston tiedot tulostettavassa muodossa
// vektoriin, joka lähetetään printAlphabetically-funktiolle tulostettavaksi.
void printTheatres(std::map<std::string, std::vector<Play>> &acts)
{
    std::vector<std::string> theatres;
    for (const auto& act : acts)
    {
        for(Play play : act.second)
        {
            if(std::find(theatres.begin(), theatres.end(), play.theatre)
                    == theatres.end())
            {
                theatres.push_back(play.theatre);
            }
        }
    }

    printAlphabetically(theatres);
    std::cout << PROMPT;
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja sekä vektorin, johon on tallennettuna käyttäjän syöte oikeanlaista
// tulostusta varten. Funktio lisää syötetiedoston tiedot tulostettavassa
// muodossa vektoriin, joka lähetetään printAlphabetically-funktiolle
// tulostettavaksi.
void printPlays(std::map<std::string, std::vector<Play>> &acts,
                std::vector<std::string> &input_vector)
{
    std::vector<std::string> theatres;

    if(input_vector.size() != 1)
    {
        std::cout << WRONG_PARAMETERS << std::endl << PROMPT;
        return;
    }
    for (const auto& act : acts)
    {
        for(Play play : act.second)
        {
            std::vector<string> split_act = split(play.act, '/');
            std::string full_name = "";
            if(split_act.size() == 2)
            {
                full_name = split_act.at(0) + " *** " + split_act.at(1);
            }
            else
            {
                full_name = split_act.at(0);
            }
            if(std::find(theatres.begin(), theatres.end(), full_name)
                    == theatres.end())
            {
                theatres.push_back(full_name);
            }
        }
    }

    printAlphabetically(theatres);
    std::cout << PROMPT;
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja sekä vektorin, johon on tallennettuna käyttäjän syöte oikeanlaista
// tulostusta varten. Funktio lisää syötetiedoston tiedot tulostettavassa
// muodossa vektoriin, joka lähetetään printAlphabetically-funktiolle
// tulostettavaksi.
void printActsInTheatre(std::map<std::string, std::vector<Play>> &acts,
                        std::vector<std::string> &input_vector)
{
    bool is_act = false;
    std::vector<string> theatres;
    for(const auto& act : acts)
    {
        for(Play play : act.second)
        {
            std::vector<string> split_vector = split(play.act, '/');
            if (split_vector.size() == 2)
            {
                if(input_vector.at(1) == split_vector.at(0)
                        || input_vector.at(1) == split_vector.at(1))
                {
                    if(std::find(theatres.begin(), theatres.end(),
                                 play.theatre) == theatres.end())
                    {
                        theatres.push_back(play.theatre);
                        is_act = true;
                    }
                }
            }
            else
            {
                if(input_vector.at(1) == split_vector.at(0))
                {
                    if(std::find(theatres.begin(), theatres.end(),
                                 play.theatre) == theatres.end())
                    {
                        theatres.push_back(play.theatre);
                        is_act = true;
                    }
                }
            }
        }
    }
    if(!is_act)
    {
        std::cout << PLAY_NOT_FOUND << endl << PROMPT;
        return;
    }

    printAlphabetically(theatres);
    std::cout << PROMPT;
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja sekä vektorin, johon on tallennettuna käyttäjän syöte oikeanlaista
// tulostusta varten. Funktio lisää syötetiedoston tiedot tulostettavassa
// muodossa vektoriin, joka lähetetään printAlphabetically-funktiolle
// tulostettavaksi.
void printPlaysInTheatre(std::map<std::string, std::vector<Play>> &acts,
                         std::vector<std::string> &input_vector)
{
    bool is_theatre = false;
    std::vector<string> plays;
    for(const auto& act : acts)
    {
        for(Play play : act.second)
        {
            std::vector<string> split_vector = split(play.act, '/');
            if(input_vector.at(1) == play.theatre)
            {
                if(std::find(plays.begin(), plays.end(), play.act)
                        == plays.end())
                {
                    plays.push_back(split_vector.at(0));
                    is_theatre = true;
                }
            }
        }
    }

    if(!is_theatre)
    {
        std::cout << THEATRE_NOT_FOUND << std::endl << PROMPT;
        return;
    }

    printAlphabetically(plays);
    std::cout << PROMPT;
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja sekä vektorin, johon on tallennettuna käyttäjän syöte oikeanlaista
// tulostusta varten. Funktio lisää syötetiedoston tiedot tulostettavassa
// muodossa vektoriin, joka lähetetään printAlphabetically-funktiolle
// tulostettavaksi.
void printPlaysInTown(std::map<std::string, std::vector<Play>> &acts,
                      std::vector<std::string> &input_vector)
{
    std::vector<string> plays;
    bool is_town = false;

    for(const auto& act : acts)
    {
        if(input_vector.at(1) == act.first)
        {
            is_town = true;
            for(Play play : act.second)
            {
                std::vector<string> split_vector = split(play.act, '/');
                if (split_vector.size() == 2)
                {
                    // Käydään läpi jo tallennetut näytelmät ja poistetaan
                    // olemassa oleva tieto, mikäli sama näytelmä ilmenee
                    // uusissa tiedoissa, jotta tieto näytelmästä on
                    // ajantasalla.
                    for(unsigned long i = 0; i < plays.size(); i+=2)
                    {
                        if(plays.at(i) == (play.theatre + " : " +
                                           split_vector.at(0) +
                                           " --- " + split_vector.at(1)
                                           + " : "))
                        {
                            plays.erase(plays.begin() + i);
                            plays.erase(plays.begin() + i);
                        }
                    }
                    plays.push_back(play.theatre + " : " + split_vector.at(0)
                                    + " --- " + split_vector.at(1) + " : ");
                    plays.push_back(to_string(play.seats));
                }
                else
                {
                    for(unsigned long i = 0; i < plays.size(); i+=2)
                    {
                        if(plays.at(i) == (play.theatre + " : "
                                           + split_vector.at(0) + " : "))
                        {
                            plays.erase(plays.begin() + i);
                            plays.erase(plays.begin() + i);
                        }
                    }
                    plays.push_back(play.theatre + " : "
                    + split_vector.at(0) + " : ");
                    plays.push_back(to_string(play.seats));
                }
            }
        }
    }

    if(!is_town)
    {
        std::cout << TOWN_NOT_FOUND << std::endl << PROMPT;
        return;
    }

    std::vector<std::string> printable_vector;
    for(unsigned long x = 0; x < plays.size(); x+=2)
    {
        if(plays.at(x+1) != "0")
        {
            printable_vector.push_back(plays.at(x) + plays.at(x+1));
        }
    }

    if(printable_vector.size() == 0)
    {
        std::cout << NOT_AVAILABLE << endl;
    }

    printAlphabetically(printable_vector);
    std::cout << PROMPT;
}

// Funktio ottaa parametrinaan map:n, joka sisältää string-Play
// pareja sekä vektorin, johon on tallennettuna käyttäjän syöte oikeanlaista
// tulostusta varten. Funktio lisää syötetiedoston tiedot tulostettavassa
// muodossa vektoriin, joka lähetetään printAlphabetically-funktiolle
// tulostettavaksi.
void printPlayers(std::map<std::string, std::vector<Play>> &acts,
                  std::vector<std::string> &input_vector)
{
    bool is_actor = false;
    bool is_theatre = false;
    std::vector<string> plays;
    for(const auto& act : acts)
    {
        for(Play play : act.second)
        {
            std::vector<string> split_vector = split(play.act, '/');
            if(split_vector.size() == 2)
            {
                if(input_vector.size() == 2)
                {
                    if(input_vector.at(1) == split_vector.at(0)
                            || input_vector.at(1) == split_vector.at(1))
                    {
                        std::string added_string = play.theatre + " : "
                                                 + play.actor;
                        if(std::find(plays.begin(), plays.end(), added_string)
                                == plays.end())
                        {
                            plays.push_back(added_string);
                            is_actor = true;
                        }
                    }
                }
                if(input_vector.size() == 3)
                {
                    if(input_vector.at(2) == play.theatre)
                    {
                        is_theatre = true;
                        if(input_vector.at(1) == split_vector.at(0)
                                || input_vector.at(1) == split_vector.at(1))
                        {
                            std::string added_string = play.theatre
                                    + " : " + play.actor;
                            if(std::find(plays.begin(), plays.end(),
                                         added_string) == plays.end())
                            {
                                plays.push_back(added_string);
                                is_actor = true;
                            }
                        }
                    }
                }
            }
            else
            {
                if(input_vector.at(1) == split_vector.at(0))
                {
                    if(input_vector.size() == 2)
                    {
                        std::string added_string = play.theatre + " : "
                                                 + play.actor;
                        if(std::find(plays.begin(), plays.end(), added_string)
                                == plays.end())
                        {
                            plays.push_back(added_string);
                            is_actor = true;
                        }
                    }
                    if(input_vector.size() == 3)
                    {
                        std::string added_string = play.theatre + " : "
                                                 + play.actor;
                        if(input_vector.at(2) == play.theatre)
                        {
                            is_theatre = true;
                            if(input_vector.at(1) == split_vector.at(0))
                            {
                                std::string added_string = play.theatre
                                                + " : " + play.actor;
                                if(std::find(plays.begin(), plays.end(),
                                             added_string) == plays.end())
                                {
                                    plays.push_back(added_string);
                                    is_actor = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(!is_theatre && input_vector.size() == 3)
    {
        std::cout << THEATRE_NOT_FOUND << std::endl << PROMPT;
        return;
    }
    if(!is_actor)
    {
        std::cout << PLAY_NOT_FOUND << std::endl << PROMPT;
        return;
    }

    printAlphabetically(plays);
    std::cout << PROMPT;
}

// Main function
int main()
{
    std::string file_name = "";
    std::map<std::string, std::vector<Play>> acts;
    std::vector<std::string> sortedVector;

    std::cout << "Input file: ";
    getline(std::cin, file_name);
    std::ifstream input_file(file_name);

    if (!input_file)
    {
        std::cout << FILE_ERROR;
        return EXIT_FAILURE;
    }

    bool event = readFile(input_file, acts);
    if (!event)
    {
        return EXIT_FAILURE;
    }

    input_file.close();

    std::cout << PROMPT;
    std::string input;

    while (std::getline(std::cin, input))
    {
        std::vector<std::string> input_vector;
        input_vector = split(input, ' ');
        std::transform(input_vector[0].begin(), input_vector[0].end(),
                input_vector[0].begin(), ::toupper);

        if (input_vector.at(0) == "QUIT")
        {
            return EXIT_SUCCESS;
        }
        else if (input_vector.at(0) == "THEATRES")
        {
            printTheatres(acts);
        }
        else if (input_vector.at(0) == "PLAYS")
        {
            printPlays(acts, input_vector);
        }
        else if (input_vector.at(0) == "THEATRES_OF_PLAY")
        {
            printActsInTheatre(acts, input_vector);
        }
        else if (input_vector.at(0) == "PLAYS_IN_THEATRE")
        {
            printPlaysInTheatre(acts, input_vector);
        }
        else if (input_vector[0] == "PLAYS_IN_TOWN")
        {
            printPlaysInTown(acts, input_vector);
        }
        else if (input_vector.at(0) == "PLAYERS_IN_PLAY")
        {
            printPlayers(acts, input_vector);
        }
        else
        {
            std::cout << COMMAND_NOT_FOUND << std::endl << "the> ";
        }
    }

    return EXIT_SUCCESS;
}
