#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include "Player.h"
#include "Board.h"
#include <iostream>

using namespace std;

class CandyStore
{
private:
    vector<Candy> _candies;
    int _candy_amount = 3;

public:
    CandyStore();
    CandyStore(vector<Candy>);

    vector<Candy> loadCandy(string); // loading random three candies from file to candystore

    vector<Candy> readCandiesFile(string filename); // reading whole candies file to (for comparisons)

    void printCandyAvailable(vector<Candy> CandyStore);
};
#endif