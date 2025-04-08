#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(const std::string& lukujono, const char merkki, bool valimerkit = false) {
    std::vector <std::string> merkkijono;
    std::string merkit;
    int pituus = lukujono.length();

    if (valimerkit == false) {
        if (lukujono.at(0) == merkki) {
            merkkijono.push_back(merkit);
        } else {
            merkit += lukujono.at(0);
        }
    }
    if (valimerkit == true) {
        if (lukujono.at(0) != merkki) {
            merkit += lukujono.at(0);
        }
    }

    for (int i = 1; i < pituus; i++ ) {
        if (lukujono.at(i) != merkki) {         //lisataan ei-erotin -merkit lukujonoon
            merkit += lukujono.at(i);
        } else {
            if (valimerkit == false) {
                if (lukujono.at(i) == merkki and lukujono.at(i-1) == merkki) {          //jos perakkaiset merkit ovat erotinmerkkeja
                    merkkijono.push_back(merkit);                                       //lisataan false-tilanteessa tyhja rivi vektoriin
                    merkit = "";
                } else {
                    merkkijono.push_back(merkit);           //kun kohdataan yksittainen erotinmerkki, lisataan merkit false-tilanteen vektoriin
                    merkit = "";
                }
            } else {
                if (merkit == "") {         //kun true-tilanteessa tulee erotinmerkki, tyhjaa rivia ei syoteta vektoriin
                    continue;               //tama tarvitaan, koska useamman perakkaisen erotin-merkin kohdalla tulisi tyhjia riveja
                } else {
                    merkkijono.push_back(merkit);           //kun kohdataan erotinmerkki, syotetaan senhetkiset merkit vektoriin
                    merkit = "";
                }
            }
        }
    }

    if (valimerkit == false) {                          //lisataan ylimaarainen rivi, jos viimeinen
        if (lukujono.at(pituus -1) == merkki) {         //merkki on erotinmerkki
            merkkijono.push_back("");
        }
    }
    if (merkit.length() != 0) {                     //jos merkit-lukujonossa on viela arvoja syottamatta,
            merkkijono.push_back(merkit);           //ne syotetaan vektoriin
    }
    return merkkijono;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
