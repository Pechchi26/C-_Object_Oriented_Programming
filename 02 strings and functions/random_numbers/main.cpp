#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    default_random_engine eng;
    uniform_int_distribution<int> distr(lower, upper);

    int seed_value = 0;
    cout << "Enter a seed value: ";
    cin >> seed_value;
    eng.seed(seed_value);

    string command = "";
    while (command != "q")

    {
        cout << "\nYour drawn random number is " << distr(eng) << endl;

        cout << "Press q to quit or any other key to continue: ";
        cin >> command;
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
