#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    unsigned int number = 0;
    cin >> number;

    if (number <= 0)
    {
       cout << "Only positive numbers accepted" << endl;
       return EXIT_SUCCESS;

    }

    unsigned int smallest_factor = 1;

    for ( unsigned int i = 1; i * i <= number; ++i )
    {
        if (number % i == 0)
        {
            smallest_factor = i;
        }
    }

    unsigned int greater_factor = number / smallest_factor;
    cout << number << " = " << smallest_factor << " * " << greater_factor << endl;

    return 0;
}
