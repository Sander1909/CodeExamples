#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <stdlib.h>

using namespace std;
string generateWord(string filePath)
{
    std::ifstream inData(filePath.c_str());
    std::vector <string> words;
    string randomWord;
    while(!inData.eof())
    {
        inData >> randomWord;
        words.push_back(randomWord);
    }
    inData.close();

    return words[rand()%words.size()-1];
}

bool testLetter(char playerLetter, string secretWord)
{
    for(unsigned int i = 0; i < secretWord.length(); i ++)
    {
        if(playerLetter == secretWord[i])
        {

            return true;
        }
    }

    return false;

}

void printWrongLetters(string wrongLetters)
{
    cout << "Wrong letters: ";

    if(wrongLetters.length() == 0)
    {
        cout << endl;
    }
    else
    {
    for(int i = 0; i < wrongLetters.length() - 1; i++)
    {
        cout << wrongLetters[i] << ", ";
    }

    cout << wrongLetters[wrongLetters.length() - 1] << endl;
    }
}

string listLetters(string wrongLetters, char playerLetter)
{

    if(testLetter(playerLetter, wrongLetters) == true)
    {
        return wrongLetters;
    }
    wrongLetters = wrongLetters + playerLetter;

    return wrongLetters;
}


string replaceLetters(char playerLetter, string displayedWord, string secretWord)
{
    for(unsigned int i = 0; i < secretWord.length(); i ++)
    {
        if(playerLetter == secretWord[i])
        {
            displayedWord[i] = secretWord[i];
        }
    }


    return displayedWord;
}

bool render(string wrongLetters, vector<string> bob)
{
    for(int i = 0; i < wrongLetters.length(); i++)
    {
        cout << bob[i] << endl;

        if(wrongLetters.length() == 6)
        {
            return true;
        }
    }

    return false;
}

bool wordIsCorrect(string displayedWord, string secretWord)
    {
            for(int i = 0; i < displayedWord.length(); i++)
            {
                if(displayedWord[i] != secretWord[i])
                {
                    return false;
                }
            }

            return true;
    }

int main()
{
    srand(time(nullptr));

    string secretWord = generateWord("../Hangman/Words.txt");
    string displayedWord = secretWord;
    string playerWord = "";
    string wrongLetters = "";
    char playerLetter = 0;
    vector<string> bob;
    bool gameIsOver = false;

    int *test;

    bob.push_back("_________");
    bob.push_back("| /     |");
    bob.push_back("|/      O");
    bob.push_back("|      /|\\");
    bob.push_back("|       |");
    bob.push_back("|      / \\");


    cout << "Welcome to Hangman!" << endl << "You have been given a word of " << secretWord.length() << " letters" << endl;

    for(int i = 0; i < secretWord.length(); i ++)
    {
        displayedWord[i] = '_';
    }

    while(gameIsOver == false)
    {

        cout << "Please submit letter:" << endl;

        cin >> playerWord;

        system("cls");

        //Hvis player gjetter riktig ord vinner man, hvis ikke legges den første bokstaven til playerLetter
        if(playerWord == secretWord)
        {
            break;
        }
        else
        {
            playerLetter = playerWord[0];
        }
        //--

        if(testLetter(playerLetter, secretWord) == true)
        {
            displayedWord = replaceLetters(playerLetter, displayedWord, secretWord);
        }
        else
        {
            wrongLetters = listLetters(wrongLetters, playerLetter);
        }

                if (wordIsCorrect(displayedWord, secretWord) == true)
                {
                    break;
                }

        printWrongLetters(wrongLetters);

        //Skriver ut displayedWord pluss mellomrom
        for(int i = 0; i < secretWord.length(); i++)
        {
            cout << displayedWord[i] << " ";

        }
        //--

        cout << endl;

        gameIsOver = render(wrongLetters, bob);

    }



    if(gameIsOver == true)
    {

        for(int i = 1; i < 6; i++)
        {
            cout << bob[i] << endl;

        }

        cout << "Game Over!" << endl << "You'll get em next time" << endl << "The word was " << secretWord << endl;
    }
    else
    {
        cout << "You Win!" << endl << "Congratulations!" << endl;
    }

    cout << endl;

    return 0;
}
