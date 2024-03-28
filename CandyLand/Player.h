#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Candy
{
    string name;
    string description;
    string effectType;
    int effectValue;
    string candyType;
    int price;
};

struct Character
{
    string name;
    int stamina;
    int gold;
    vector<Candy> candies;
};

class Player
{
public:
    Player();
    Player(string, string, int, int, Candy[], const int);

    void setPlayerName(string);
    void setCharacterName(string);
    void setStamina(int);
    void setGold(int);
    void setInventory(vector<Candy>);

    string getPlayerName() const;
    string getCharacterName() const;
    int getStamina() const;
    int getGold() const;
    int getCandyAmount();
    vector<string> getInventory();

    void printStats(int);
    void printInventory();
    bool addCandy(Candy candy);
    bool removeCandy(string candy_name);
    Candy findCandy(string candy_name) const;

    bool hasCandy(string candy_name) const; 
    bool isInventoryFull() const;

private:
    const static int _MAX_CANDY_AMOUNT = 9; // how big inventory can be
    string _playerName;
    string _character_name;
    int _stamina;
    double _gold;
    Candy _inventory[9];
    int _candy_amount;
};

#endif