#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Read input and output file names
    string input_file_name = "";
    cout << "Input file: ";
    cin >> input_file_name;

    string output_file_name = "";
    cout << "Output file: ";
    cin >> output_file_name;

    // Open input file and check that it exists
    ifstream input_file_object(input_file_name);

    if ( not input_file_object )
    {
        cout << "Error! The file " << input_file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    // Open output file
    ofstream output_file_object(output_file_name);

    string line = "";
    int i = 1;
     while ( getline(input_file_object, line) )
     {
         output_file_object << i << " " << line << endl;
         i++;
     }


    // Close files
    input_file_object.close();
    output_file_object.close();

    return 0;
}
