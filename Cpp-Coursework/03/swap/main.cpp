#include <cstdlib>
#include <iostream>

int swap(int& ii, int& jii){
    int muuttuja = 0;
    muuttuja = ii;
    ii = jii;
    jii = muuttuja;
    return ii and jii;

}

#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
