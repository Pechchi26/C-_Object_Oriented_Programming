#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib> // For EXIT_SUCCESS and EXIT_FAILURE

using namespace std;

int main()
{
    string filename;
    cout << "Input file: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, int> scores;
    string line;

    while (getline(file, line))
    {
        size_t delimiter_pos = line.find(':');
        if (delimiter_pos == string::npos)
        {
            continue; // Skip lines that don't have a delimiter
        }

        string name = line.substr(0, delimiter_pos);
        int points = stoi(line.substr(delimiter_pos + 1));

        scores[name] += points;
    }

    file.close();

    cout << "Final scores:" << endl;
    for (const auto& entry : scores)
    {
        cout << entry.first << ": " << entry.second << endl;
    }

    return EXIT_SUCCESS;
}
