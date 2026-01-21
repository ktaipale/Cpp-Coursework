#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int lampotila = 0;
    cin >> lampotila;

    cout << lampotila << " degrees Celsius is " << lampotila * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << lampotila << " degrees Fahrenheit is " << (lampotila - 32) / 1.8 << " degrees Celsius" << endl;
    return 0;
}
