#include <iostream>

using namespace std;

void flip(char &c)
{
    c == 'x' ? c = 'y' : c = 'x';
}

int arrangeString(string &s)
{
    int operations = 0;

    for(unsigned int i = 0; i < s.length(); i++)
    {
        if((s[i] == 'y' && i < (s.length() / 2)) || (s[i] == 'x' && i > (s.length() / 2)))
        {
            flip(s[i]);
            operations++;
        }
    }

    return operations;
}

int main()
{
    string s = "xyxxxyxyy";

    cout << s << endl;

    cout << arrangeString(s) << endl;

    cout << s << endl;

    return 0;
}
