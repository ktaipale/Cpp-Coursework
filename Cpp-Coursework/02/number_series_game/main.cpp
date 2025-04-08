#include <iostream>
#include <string>



int main()
{
    std::cout << "How many numbers would you like to have? ";
    int lukumaara = 0;
    std::cin >> lukumaara;

    for (int luku = 1; luku <= lukumaara; ++luku ) {
        if (luku % 3 == 0 and luku % 7 == 0) {
            std::cout <<"zip boing" << std::endl;
        } else if (luku % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else if (luku % 7 == 0) {
            std::cout <<"boing" << std::endl;
        } else {
            std::cout << luku << std::endl;
        }
    }
    return 0;
}
