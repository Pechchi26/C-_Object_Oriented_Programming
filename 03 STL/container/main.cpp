#include <cstdlib>
#include <iostream>
#include <vector>


// Prints the elements in the parameter vector ints.
void print_integers(const std::vector< int >& ints)
{
    for(auto elem : ints) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        std::cin >> new_integer;
        ints.push_back(new_integer);

        // TODO: Implement your solution here
    }
}


bool same_values(const std::vector<int>& ints)
{


    for (std::vector<int>::size_type index=0; index< ints.size()-1;index++)
    {

        if (ints.at(index) != ints.at(index+1))
        {

            return false;
        }
    }

    return true;

}

bool is_ordered_non_strict_ascending(const std::vector<int>& ints)
{
    for ( std::vector<int>::size_type index=0; index< ints.size()-1;index++)
    {
        if (ints.at(index) > ints.at(index+1))
        {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(const std::vector<int>& ints)
{
    for (std::vector<int>::size_type index=0; index< ints.size()-2;index++)
    {
        if (ints.at(index+1)-ints.at(index) != ints.at(index+2)-ints.at(index+1))
        {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(const std::vector<int>& ints)
{

    for (std::vector<int>::size_type index=0; index< ints.size()-2;++index)
    {
        if(ints.at(index)==0 || ints.at(index+1)==0)
        {
            return false;
        }
        if ( ints.at(index+1)/ints.at(index) != ints.at(index+2)/ints.at(index+1))
        {
            return false;
        }
    }
    return true;
}

// TODO: Implement your solution here


void triple_integers(std::vector<int>& ints)
{
    for (int& element : ints)
    {
        element=element*3;

    }

}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        std::cout << "All the integers are the same" << std::endl;
    } else {
        std::cout << "All the integers are not the same" << std::endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    } else {
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;
    }

    if(is_arithmetic_series(integers)) {
        std::cout << "The integers form an arithmetic series" << std::endl;
    } else {
        std::cout << "The integers do not form an arithmetic series" << std::endl;
    }

    if(is_geometric_series(integers)) {
        std::cout << "The integers form a geometric series" << std::endl;
    } else {
        std::cout << "The integers do not form a geometric series" << std::endl;
    }

    triple_integers(integers);
    std::cout << "Tripled values: ";
    print_integers(integers);

    return EXIT_SUCCESS;
}

