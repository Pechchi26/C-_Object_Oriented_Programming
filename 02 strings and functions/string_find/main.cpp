#include <iostream>
#include <string>

using namespace std;

int main()
{
    string longer = "";
    string shorter = "";

    cout << "Enter a (longer) string: ";
    cin >> longer;

    cout << "Enter a (shorter) string to be found: ";
    cin >> shorter;

    // code for: Check that the shorter string is actually shorter than the longer string
    if ( shorter.size() > longer.size() )
    {
        cout << "Not found" << endl;
        return EXIT_SUCCESS;
    }

    unsigned int start_index = 0;
    string::size_type found_index = longer.find(shorter, start_index);

    if ( found_index == string::npos )
    {
        //code for: not found
        cout << "Not found" << endl;
        return EXIT_SUCCESS;
    }

    cout << "Found at " << found_index;

        start_index = found_index + 1 ;

        while (start_index < longer.size()) {
            found_index = longer.find(shorter, start_index);

        if (found_index == string::npos)
            break;

      cout << ", " << found_index;

         start_index = found_index + 1 ;
    }

    cout << endl;

    return 0;
}
