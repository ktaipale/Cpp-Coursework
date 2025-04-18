#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }
        std::string::iterator alku;
        alku = word.begin();
        std::string::iterator loppu;
        loppu = word.end();

        if (word.length() >= 2) {
            alku++;
            loppu--;
            shuffle(alku, loppu, generator);
        }

        std::cout << word << std::endl;

        // TODO: implement your solution here
    }
}
