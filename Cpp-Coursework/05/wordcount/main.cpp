#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream file_object(file_name);

    if (not file_object) {
        cout << "Error! The file " << file_name << " cannot be opened.";
        return EXIT_FAILURE;
    }
    map<string, int> esiintymislaskuri;
    vector<string> rivit;
    vector<string> sanat;
    vector<string> sanamaara;
    string line;
    string rivi;
    string sana;

    while (getline(file_object, line)) {

            rivit.push_back((" " + line + " "));
            int pituus = line.length();
            for (int i = 0; i <= pituus; i++) {
                if (line[i] != ' ' and i != pituus) {
                    sana += line[i];
                } else {
                    sanamaara.push_back((sana));
                    if (find(sanat.begin(), sanat.end(), sana) != sanat.end()) {
                        sana = "";
                    } else {
                        sanat.push_back(sana);
                        sana = "";
                    }
                }
            }
    }

    sort(sanat.begin(), sanat.end());
    int lukumaara = 1;
    for (unsigned int i = 0; i < sanamaara.size(); i++) {
        if (esiintymislaskuri.find(sanamaara[i]) != esiintymislaskuri.end()) {
            auto it = esiintymislaskuri.find(sanamaara[i]);
            esiintymislaskuri.insert_or_assign(sanamaara[i], it->second +1);
        } else {
            esiintymislaskuri.insert({sanamaara[i], lukumaara});
            }
        }

    int x = 0;
    int sanalaskuri = 0;
    int laskuri = 1;
    for (auto iter = esiintymislaskuri.begin(); iter != esiintymislaskuri.end(); ++iter) {
        int y = 0;
        for (string s : rivit) {
            if (s.find(" " + sanat[x] + " ") != string::npos) {
                if (y == 0) {
                    y++;
                    sanalaskuri += 1;
                } else {
                    sanalaskuri += 1;
                }
            }
        }
        cout << (*iter).first << " " << sanalaskuri << ": ";
        y = 0;
        for (string s : rivit) {
            if (s.find(" " + sanat[x] + " ") != string::npos) {
                if (y == 0) {
                    cout << laskuri;
                    y++;
                    sanalaskuri += 1;
                } else {
                    cout << ", " << laskuri;
                    sanalaskuri += 1;
                }
            }
            laskuri++;
        }
        x++;
        laskuri = 1;
        sanalaskuri = 0;
        cout << endl;
    }
}
