#include <iostream>

using namespace std;

unsigned long int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    unsigned long int result = 1;
    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

unsigned long int combinations(int n, int p)
{
    if (p > n)
    {
        return 0;
    }
    return factorial(n) / (factorial(p) * factorial(n - p));
}

void displayProbability(int totalBalls, int drawnBalls)
{
    unsigned long int totalCombinations = combinations(totalBalls, drawnBalls);

    if (totalCombinations == 0)
    {
        cout << "The probability of guessing all " << drawnBalls << " balls correctly is 1/" << totalCombinations << endl;
    }
    else
    {
        cout << "The probability of guessing all " << drawnBalls << " balls correctly is 1/" << totalCombinations << endl;
    }
}

int main()
{
    int totalBalls, drawnBalls;

    cout << "Enter the total number of lottery balls: ";
    cin >> totalBalls;

    cout << "Enter the number of drawn balls: ";
    cin >> drawnBalls;

    if (totalBalls <= 0)
    {
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_SUCCESS;
    }
    if (drawnBalls > totalBalls)
        {
            cout << "The maximum number of drawn balls is the total amount of balls." << endl;
            return 0;
        }

    displayProbability(totalBalls, drawnBalls);

    return EXIT_SUCCESS;
}
