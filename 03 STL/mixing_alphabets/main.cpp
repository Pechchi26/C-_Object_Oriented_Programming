#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;
    string single_word;

    getline(cin,word);
    while (word != "END") //this loop handle one word at a time
    {
        size_t space_pos=word.find(' ');
        if(space_pos != string::npos)
        {
            single_word = word.substr(0,space_pos);
            word = word.substr(space_pos+1);
            if ( single_word.length() >3)
            {
                //change the line to not inculde the first and last letter
                shuffle(single_word.begin()+1, single_word.end()-1, generator);

            }
             std::cout << single_word << std::endl;
        }
        else
        {
            single_word=word;
            word="END";
        }



    }



        if (word == "END")
        {
            return EXIT_SUCCESS;
        }



    return 0;
}
