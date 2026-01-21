#include <iostream>

using namespace std;

int todennakoisyys(unsigned long int pallojen_maara, unsigned long int arvotut_pallot) {
    unsigned long int osoittaja = 1;
    unsigned long int nimittaja1 = 1;
    unsigned long int nimittaja2 = 1;
    for (unsigned long int i = 1; i <= pallojen_maara; ++i) {
        osoittaja *= i;
    }
    for (unsigned long int i = 1; i <= pallojen_maara - arvotut_pallot; ++i) {
        nimittaja1 *= i;
    }
    for (unsigned long int i = 1; i <= arvotut_pallot; ++i) {
        nimittaja2 *= i;
    }
    return osoittaja / (nimittaja1 * nimittaja2);
}


int main()
{
    int pallojen_maara = 0;
    int arvotut_pallot = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> pallojen_maara;
    cout << "Enter the number of drawn balls: ";
    cin >> arvotut_pallot;
    if ( pallojen_maara < 0 ) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }
    else if (arvotut_pallot < 0 ) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }
    else {
        if ( arvotut_pallot > pallojen_maara ){
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
            return 0;
        }
        else {
            cout << "The probability of guessing all " << arvotut_pallot << " balls correctly is " << "1/" << todennakoisyys(pallojen_maara, arvotut_pallot) << endl;
        }
        return 0;
    }
}

