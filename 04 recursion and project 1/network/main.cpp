#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using Network = std::map<std::string, std::vector<std::string>>;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


void store(Network& net, std::string& parent, std::string& child)
{
    //if parent does't exist as a parent
    if ( net.find(parent) == net.end() )
    {
        net[parent] = std::vector<std::string>();
    }

    //if child can be found
    if ( find(net.at(parent).begin(), net.at(parent).end(), child)
         != net.at(parent).end() )
    {
        return;
    }

    //if child cannot be found
    net[parent].push_back(child);
}

void print(Network& net, std::string& id, int indent = 0)
{
    for ( int i = 0; i < indent; ++i)
    {
        std::cout << "..";
    }
    std::cout << id << std::endl;

    // if ID has children, print them out as well
    if ( net.find(id) != net.end() )
    {
        for ( std::string child : net.at(id) )
        {
            print(net, child, indent+1);
        }
    }
    //if there are no children, don't call the function again
}

int count(Network& net, std::string& id)
{
    int size = 0;
    if ( net.find(id) != net.end() )
    {
        for ( std::string child : net.at(id) )
        {
            // increase the number of size with each childe encountered
            ++size;
            // add to size the size of the childś own subnetwork
            size += count(net, child);
        }
    }
    return size;
}

int depth(Network& net, std::string& id)
{
    int max_depth = 0;

    // check if there are any children
    if(net.find(id)!=net.end())
    {
        //for each child check the max depth of their subnetworks
        for(const auto& child:net.at(id))

        {
            //chec if the max depth of child network is greater than max depth
            int child_depth=depth(net,const_cast<std::string&>(child));
            if(child_depth>max_depth)
            {
                //save new max depth if needed
                max_depth=child_depth;
            }
        }
    }

    return max_depth + 1;
}

int main()
{
    // TODO: Implement the datastructure here
    Network net;


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            store(net, id1, id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(net, id);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(net, id) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(net, id) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
