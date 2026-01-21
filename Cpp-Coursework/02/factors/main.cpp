#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    int luku = 0;
    cin >> luku;

    if (luku <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        int luku1 = 0;
        int luku2 = 0;
        for (int numero = int(sqrt(luku)); numero > 0; --numero ){
            if ( luku % numero == 0) {
                luku1 = numero;
                break;
            }
        }
        luku2 = luku / luku1;
        cout << luku << " = " << luku1 << " * " << luku2 << endl;
    }

    return 0;
}
