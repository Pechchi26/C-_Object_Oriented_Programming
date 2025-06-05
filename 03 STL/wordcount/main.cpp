#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <sstream>



using namespace std;

int main()
{
    // Read input and output file names
    string input_file_name = "";
    cout << "Input file: ";
    cin >> input_file_name;

    // Open input file and check that it exists
    ifstream input_file_object(input_file_name);

    if ( not input_file_object )
    {
        cout << "Error! The file " << input_file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, set<int>> dictionary;

    string row = "";
    unsigned int row_number = 1;

    while ( getline(input_file_object, row) )
    {
        // splitting string exercise tools, row of text into words

        string word = "";
        istringstream rowstream(row);

        while ( rowstream >> word )
        {
            dictionary[word].insert(row_number);
        }
        ++row_number;
    }

    for ( map<string, set<int>>::iterator word_iterator = dictionary.begin() ;
          word_iterator != dictionary.end() ;
          ++ word_iterator )

    {
        cout << word_iterator->first << " " << word_iterator->second.size() << ": ";

        // set<int>::iterator - another loop to locate and print out
        set<int>::iterator line_iterator;
                for (line_iterator = word_iterator->second.begin();
                     line_iterator != word_iterator->second.end(); ++line_iterator)
                {
                    if (line_iterator != word_iterator->second.begin())
                    {
                        cout << ", ";
                    }
                    cout << *line_iterator;
                }

                cout << endl;

    }


    return 0;
}
