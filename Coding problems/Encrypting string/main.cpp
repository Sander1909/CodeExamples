#include <iostream>
#include <ctime>
using namespace std;

void encrypt(string &toEncrypt)
{
    int hits = 1;
    string encrypted = "";

    for(int i = 0; i< toEncrypt.length() - 1; i++)
    {
        if(toEncrypt[i] == toEncrypt[i + 1])
        {
            hits++;

        }
        else
        {
            char buffer[20];
            encrypted = encrypted + itoa(hits, buffer, 10);

            hits = 1;

            encrypted = encrypted + toEncrypt[i];
        }
    }

    for(int i = toEncrypt.length(); i>0; i--)
    {
        if(toEncrypt[i] == toEncrypt [i - 1])
        {
            hits++;

        }
        else
        {
            char buffer[20];
            encrypted = encrypted + itoa(hits, buffer, 10);

            encrypted = encrypted + toEncrypt[i - 1];

            break;
        }
    }

    toEncrypt = encrypted;
}


string decrypt (string toDecrypt)
{
    string decrypted = "";
    int number = 0;
    char letter;

    for(int i = 0; i< toDecrypt.length(); i = i + 2)
    {
        //number = stoi(toDecrypt[i]);
    }


}

int main()
{
    char randomChar;
    string word = "";

    srand(time(nullptr));

    for(int i = 0; i < 20; i++)
    {
        randomChar = (rand()%2) + 65;

       word = word + randomChar;
    }

    cout << word << " (original string)" << endl;


    encrypt(word);

    cout << word << " (encrypted string) " << endl;




    return 0;
}
