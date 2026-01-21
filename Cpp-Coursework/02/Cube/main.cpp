#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int luku = 0;
    cout << "Enter a number: ";
    cin >> luku;
    if ( pow(luku,3) > pow(2,32)) {
        cout << "Error! The cube of " << luku << " is not " << luku * luku * luku << endl;
    }
    else {
        cout << "The cube of " << luku << " is " << luku * luku * luku << "." << endl;
    }
    return 0;
}
