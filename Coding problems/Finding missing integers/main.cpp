#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

/*
 *
 * Good morning! Here's your coding interview problem for today.

This problem was asked by Stripe.


Given an array of integers, find the first missing positive integer in linear time and constant space.

In other words, find the lowest positive integer that does not exist in the array.

The array can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.
*/

using namespace std;

int highestPossibleInteger(vector<int> numbers)
{
    int highestPossible = numbers[0] + 1;

    for(int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << endl;
        if(numbers[i] >= highestPossible)
        {
            highestPossible = numbers[i] + 1;
        }
    }
    return highestPossible;
}

int lowestPossibleInteger(vector<int> numbers)
{
    sort(numbers.begin(), numbers.end());

    numbers.push_back(numbers.back());


    for(int i = 0; i < numbers.size(); i++)
    {
        if(numbers[i] + 1 != numbers[i+1])
        {
            return numbers[i] + 1;
        }
    }

    numbers.pop_back();

    return numbers.back();
}

int main()
{

    srand(time(nullptr));

    vector<int> n;

    for(int i = 0; i < 10; i++)
    {
        n.push_back(rand()%15);
    }

    cout << "Highest possible integer: " << highestPossibleInteger(n) << endl;

    cout << "Lowest possible integer: " << lowestPossibleInteger(n) << endl;

    cout << "Hello World!" << endl;
    return 0;
}
