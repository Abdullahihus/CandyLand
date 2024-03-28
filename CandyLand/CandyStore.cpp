#include "CandyStore.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

CandyStore::CandyStore()
{
    for (int i = 0; i < _candy_amount; i++)
    {
        _candies.push_back(Candy());
    }
}

CandyStore::CandyStore(vector<Candy> candyStore)
{
    _candies = candyStore;
}


vector <Candy> CandyStore::loadCandy(string filename)
{
    ifstream file_in(filename);
    if (!file_in.is_open())
    {
        cout << "CAN'T OPEN FILE" << endl;
        return _candies;
    }

    _candies.clear(); 

    vector<string> lines; 

    string temp;
    getline(file_in, temp); // store headerline
    string line;

    while (getline(file_in, line))
    {
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }

    // Use srand and rand for randomization
    for (int i = int(lines.size()) - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);

        // swap
        string tempLine = lines[i];
        lines[i] = lines[j];
        lines[j] = tempLine;
    }

    for ( int i = 0; i < 3; ++i)
    {
        string randomizedLine = lines[i];

        stringstream ss(randomizedLine);

        Candy candy;
        getline(ss, candy.name, '|');
        getline(ss, candy.description, '|');
        getline(ss, candy.effectType, '|');

        string temp1;
        getline(ss, temp1, '|');
        candy.effectValue = stoi(temp1);

        getline(ss, candy.candyType, '|');

        string temp2;
        getline(ss, temp2);
        candy.price = stoi(temp2);

        _candies.push_back(candy);
    }

    file_in.close();
    return _candies;
}


vector<Candy> CandyStore::readCandiesFile(string filename)
{
    vector<Candy> candies;
    ifstream file_in("candies.txt");
    string temp1, temp2;
    Candy candy;

    if (!file_in.is_open())
    {
        cout << "CAN'T OPEN FILE" << endl;
        return candies;
    }

    string temp; 
    getline(file_in, temp); //get rid of header on top of file
    string line;

    while (getline(file_in, line))
    {
        if (line.length() == 0)
        {
            continue;
        }
        else
        {
            stringstream ss(line);

            getline(ss, candy.name, '|');
            getline(ss, candy.description, '|');
            getline(ss, candy.effectType, '|');

            getline(ss, temp1, '|');
            candy.effectValue = stoi(temp1);

            getline(ss, candy.candyType, '|');

            getline(ss, temp2);
            candy.price = stoi(temp2);

            candies.push_back(candy);
        }
    }

    file_in.close();
    return candies;
}

void CandyStore::printCandyAvailable(vector<Candy> candies)
{
    int size = candies.size();
    for (int i = 0; i < size; i++)
    {
        cout << "Name: " << candies[i].name << endl;
        cout << "Description: " << candies[i].description << endl;
        cout << "Effect Type: " << candies[i].effectType << endl;
        cout << "Effect Value: " << candies[i].effectValue << endl;
        cout << "Candy Type: " << candies[i].candyType << endl;
        cout << "Price: " << candies[i].price << endl;
        cout << "---------------------------------" << endl;
    }
}