#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Word
{
    string word;
    int frequency;

    Word(string inW)
    {
        word = inW;
        frequency = 1;
    }

    bool operator == (const Word &other) const
    {
        return word == other.word;
    }

};

struct Country
{
    string country;
    int frequency;

    Country(string inC)
    {
        country = inC;
        frequency = 1;
    }
};

void toUpper(string &s)
{
    s[0] = toupper(s[0]);
}

void parseSentence(string sentence, vector<Word> &words)
{
    Word word("");

    for(int i = 0; i < sentence.length(); i++)
    {
        if(sentence[i] != ' ')
            word.word += sentence[i];
        else
        {
            toUpper(word.word);

            vector<Word>::iterator it = find(words.begin(), words.end(), word);

            if(it != words.end())
                it->frequency++;
            else
            {
                Word newW(word.word);
                newW.frequency = 1;
                words.push_back(newW);
            }

            word.word = "";
        }
    }
}

string parseCSV(string filePath, vector<Word> &words, vector<Country> &countries)
{
    std::ifstream inData(filePath.c_str());

    string temp;

    bool countryShouldBeRegistered = true;
    int counter = 0;



    while(counter < 1000)//!inData.eof())
    {
        getline(inData, temp, ',');
        getline(inData, temp, ',');

        counter++;

        countryShouldBeRegistered = true;

        for(int i = 0; i < countries.size(); i++)
        {
            if(countries[i].country == temp)
            {
                countries[i].frequency++;
                countryShouldBeRegistered = false;
            }
        }

        if(countryShouldBeRegistered)
        {
            Country newC(temp);
            countries.push_back(newC);
        }

        getline(inData, temp, '"');
        getline(inData, temp, '"');
        getline(inData, temp, '"');


        parseSentence(temp.c_str(), words);

        getline(inData, temp);

        cout << "Reviews parsed: " << counter << " of 150 000" << endl;
        system("cls");

        //inData >> randomWord;
    }
    inData.close();

    return "words[rand()%words.size()-1];";
}

void bubbleSortCountries(vector<Country> &countries)
{
    int operations = 0;
    bool sort = true;

    while(sort)
    {
        for(int i = 1; i < countries.size(); i++)
        {
            if(countries[i-1].frequency < countries[i].frequency)
            {
                Country temp(countries[i].country);
                temp.frequency = countries[i].frequency;

                countries[i] = countries[i-1];
                countries[i-1] = temp;
                operations++;
            }
        }
        if(operations == 0)
        {
            sort = false;
        }

        operations = 0;
    }
}

void bubbleSortWords(vector<Word> &words)
{
    int operations = 0;
    bool sort = true;

    while(sort)
    {
        for(int i = 1; i < words.size(); i++)
        {
            if(words[i-1].frequency < words[i].frequency)
            {
                Word temp(words[i].word);
                temp.frequency = words[i].frequency;

                words[i] = words[i-1];
                words[i-1] = temp;
                operations++;
            }
        }
        if(operations == 0)
        {
            sort = false;
        }

        operations = 0;
    }
}

int main()
{
    vector<Word> mostUsedWords;

    vector<Country> countries;

    parseCSV("../WineReviews/winemag-data_first150k.csv", mostUsedWords, countries);

    cout << endl;

    bubbleSortCountries(countries);
    bubbleSortWords(mostUsedWords);

    for(int i = 0; i < 50; i++)
    {
        cout << mostUsedWords[i].word << "(" << mostUsedWords[i].frequency << ")" << endl;
    }

    /*for(int i = 0; i < 5; i++)
    {
        cout << "Country: " << countries[i].country << endl;
        cout << "Frequency: " << countries[i].frequency << endl;
        cout << endl;
    }*/

    return 0;
}
