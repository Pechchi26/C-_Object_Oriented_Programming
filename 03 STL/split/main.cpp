#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;


vector<string> split(string line,
       const char& separator)
{
   vector<string> result;
   while(line.find(separator) != string::npos)
   {
       string word = line.substr(0, line.find(separator));
       line = line.substr(line.find(separator)+1,line.size());

           result.push_back(word);
   }
    result.push_back(line);
    return result;
}


vector<string> split_empty(string line, const char&separator, bool empty)
{
    vector<string> result;
    while(line.find(separator) != string::npos)
    {
        string word = line.substr(0, line.find(separator));
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());

        line = line.substr(line.find(separator)+1,line.size());

        if(!empty || !word.empty()){
            result.push_back(word);}
    }


        if (!empty || !line.empty()) {
            result.push_back(line);}

     return result;
}



int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    vector< string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for(const auto& part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split_empty(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for(const auto& part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
