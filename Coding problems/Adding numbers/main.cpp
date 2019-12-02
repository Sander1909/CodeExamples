#include <iostream>
#include <ctime>
#include <vector>

/*Good morning! Here's your coding interview problem for today.

This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?*/


using namespace std;


bool numbersAddUp(std::vector<int> numbers, int k)
{
    for(int i = 0; i < numbers.size(); i++)
    {
        for(int j = i; j < numbers.size(); j++)
        {
            if(numbers[i] + numbers[j] == k && i != j)
            {
                cout << "The numbers " << numbers[i] << " and " << numbers[j] << " add up to " << k << endl;
                return true;
            }
        }
    }
    cout << "No two numbers in this list add up to " << k << endl;
    return false;
}

int main()
{
    srand(time(nullptr));

    std::vector<int> numbers;

    int listSize =  10;
    int numbersRange = 30;

    for(int i = 0; i < listSize; i++)
    {
        numbers.push_back(rand()%numbersRange);
        cout << numbers[i] << " ";
    }
    cout << endl;

    int k = 40;

    numbersAddUp(numbers, k);

    cout << "Hello World!" << endl;
    return 0;
}
