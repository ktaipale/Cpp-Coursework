#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    map<string, int> players;

    ifstream file_object(file_name);
    map<string, int>::iterator iter;
    iter = players.begin();

    if (not file_object) {
        cout << "Error! The file " << file_name << " cannot be opened.";
        return EXIT_FAILURE;
    }
    string player;
    int score;
    string line;
    int index;
    int length;

    while (getline(file_object,line)) {
        index = line.find(":");
        player = line.substr(0, index);
        length = line.length();
        score = stoi(line.substr(index + 1, length - index));
        if (players.find(player) != players.end()) {
            score += players[player];
            players.insert_or_assign(player, score);

        } else {
            players.insert({player, score});
        }
    }
    cout << "Final scores:" << endl;
    for (auto iter = players.begin(); iter != players.end(); ++iter) {
        cout << (*iter).first << ": " << (*iter).second << endl;
    }
}
