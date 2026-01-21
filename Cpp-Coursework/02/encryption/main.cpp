#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string merkkijono = "";
    string avain = "";
    string salattu_teksti = "";

    cout << "Enter the encryption key: ";
    getline(cin, avain);

    if (avain.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters.";
        return EXIT_FAILURE;
    }

    for (char x : avain){
        if (isupper(x)) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
            }
         }

    for(char letter = 'a'; letter <= 'z'; letter++) {
        if(avain.find(letter) == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z.";
            return EXIT_FAILURE;
        }
    }

    cout << "Enter the text to be encrypted: ";
    getline (cin, merkkijono);

    for (char x : merkkijono){
        if (isupper(x)) {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
            }
         }


    for(char letter : merkkijono) {
        int index = letter - 'a';
        salattu_teksti += avain.at(index);
    }

    cout << "Encrypted text: " << salattu_teksti << endl;
    return 0;
}
