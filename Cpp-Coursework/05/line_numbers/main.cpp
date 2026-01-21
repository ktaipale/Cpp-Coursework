#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file;
    string output_file;
    cout << "Input file: ";
    getline (cin, input_file);
    cout << "Output file: ";
    getline (cin, output_file);

    ifstream file_object(input_file);
    if (not file_object) {
        cout << "Error! The file " << input_file << " cannot be opened.";
        return EXIT_FAILURE;
    } else {
       string line;
       int i = 1;
       ofstream output(output_file);
       while (getline(file_object, line)) {
           output << i << " " << line << endl;
           i++;
       }
       file_object.close();
       output.close();
    }




}
