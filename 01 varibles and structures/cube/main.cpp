#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number = 0;
    cin >> number;

    int cube = pow (number, 3);

    int root = cbrt (cube);
    if (number == root or number == 0)
    {
        cout << "The cube of " << number << " is " << cube << "." << endl;
    }
    else
    {
        cout << "Error! The cube of " << number << " is not " << cube << "." << endl;
    }
        return 0;
}
