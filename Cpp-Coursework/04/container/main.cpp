#include <cstdlib>
#include <iostream>
#include <vector>


// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
        // TODO: Implement your solution here
    }
}

// TODO: Implement your solution here

bool same_values(const std::vector <int>& numerot) {
    int ensimmainen_numero = numerot.at(0);
    int numeroiden_maara = numerot.size();
    for (int i = 1; i < numeroiden_maara; ++i) {
        if (ensimmainen_numero != numerot.at(i)) {
            return false;
        }
    }
    return true;

}

bool is_ordered_non_strict_ascending(const std::vector <int> numerot) {
    int numeroiden_maara = numerot.size();
    for (int i = 0; i < numeroiden_maara - 1; ++i) {
        if (numerot.at(i) > numerot.at(i+1)) {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(const std::vector <int> numerot) {
    int erotus = numerot.at(1) - numerot.at(0);
    int numeroiden_maara = numerot.size();
    for (int i = 1; i < numeroiden_maara - 1; ++i) {
        if (numerot.at(i+1) - numerot.at(i) != erotus) {
            return false;
        }
    }
    return true;
}

bool is_geometric_series (const std::vector <int> numerot) {
    if (numerot.at(1) == 0 and numerot.at(0) == 0){
        return false;
    }
    int kerroin = numerot.at(1) / numerot.at(0);
    int numeroiden_maara = numerot.size();
    for (int i = 1; i < numeroiden_maara - 1; ++i) {
        if (numerot.at(i+1) / numerot.at(i) != kerroin) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    std::cout << "Tripled values:";

    for(int i = 0; i < how_many; i++)
    {
        std::cout << " " << integers[i] * 3;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
