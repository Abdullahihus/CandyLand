#include <iostream>
#include "Player.h"
#include "Board.h"

using namespace std;

bool compareStrings(string str1, string str2)
{

    for (int i = 0; i < int(str1.length()); i++)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
        {
            return false;
        }
    }
    return true;
}

Player::Player()
{
    _playerName = "";
    _character_name = "";
    _stamina = 0;
    _gold = 0;
    _candy_amount = 0;

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = Candy();
    }
}

Player::Player(string playerName, string characterName, int stamina, int gold, Candy candies[], const int CANDY_ARR_SIZE)
{
    _playerName = playerName;
    _character_name = characterName;
    _stamina = stamina;
    _gold = gold;
    _candy_amount = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = Candy();
    }

    for (int i = 0; i < CANDY_ARR_SIZE && i < _MAX_CANDY_AMOUNT; i++)
    {
        if (candies[i].name != "" && _candy_amount < _MAX_CANDY_AMOUNT)
        {
            _inventory[_candy_amount] = candies[i];
            _candy_amount++;
        }
    }
}

void Player::setPlayerName(string playerName)
{
    _playerName = playerName;
}
void Player::setCharacterName(string characterName)
{
    _character_name = characterName;
}
void Player::setStamina(int stamina)
{
    _stamina = stamina;
    if (_stamina < 0)
    {
        _stamina = 0;
    }
    if (_stamina > 100)
    {
        _stamina = 100;
    }
}
void Player::setGold(int gold)
{
    _gold = gold;
    if (_gold < 0)
    {
        _gold = 0;
    }
    if (_gold > 100)
    {
        _gold = 100;
    }
}

void Player::setInventory(vector<Candy> candies)
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = candies.at(i);
        _candy_amount++;
    }
}

string Player::getPlayerName() const
{
    return _playerName;
}

string Player::getCharacterName() const
{
    return _character_name;
}
int Player::getStamina() const
{
    return _stamina;
}
int Player::getGold() const
{
    return _gold;
}
int Player::getCandyAmount()
{
    return _candy_amount;
}
vector<string> Player::getInventory() // for out_file use
{
    vector<string> inventory;

    for (int i = 0; i < _candy_amount; i++)
    {
        inventory.push_back(_inventory[i].name);
    }

    return inventory;
}

void Player::printStats(int playerIndex)
{
    cout << "Player name: " << getPlayerName() << endl;
    cout << "Character: " << getCharacterName() << endl;
    cout << "Stamina: " << getStamina() << endl;
    cout << "Gold: " << getGold() << endl;
    cout << "Inventory:";
    printInventory();
    cout << "------------------------------------------" << endl;
}

void Player::printInventory() // helper function for printStats
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (i % 3 == 0)
        {
            cout << endl;
        }
        cout << RED << "[" << _inventory[i].name << "]     " << RESET;
    }
    cout << endl;
}

bool Player::addCandy(Candy candy)
{
    if (_candy_amount < _MAX_CANDY_AMOUNT)
    {
        _inventory[_candy_amount] = candy; 
        _candy_amount++;                   // update candy amount
        return true;
    }
    return false;
}

bool Player::removeCandy(string candy_name)
{
    int size = _MAX_CANDY_AMOUNT;

    for (int i = 0; i < size; i++)
    {
        if (compareStrings(_inventory[i].name, candy_name))
        {
            for (int j = i; j < size - 1; j++)
            {
                _inventory[j] = _inventory[j + 1];
            }

            _inventory[_MAX_CANDY_AMOUNT - 1].name = "";
            _candy_amount--;
            break;
            return true;
        }
    }
    return false;
}

Candy Player::findCandy(string candy_name) const
{
    for (int i = 0; i < _candy_amount; i++)
    {
        if (compareStrings(_inventory[i].name, candy_name)) // find candy name in inventory
        {
            return _inventory[i];
        }
    }
    return Candy();
}

bool Player::hasCandy(string candy_name) const  // wanted a bool return for findCandy
{
    for (int i = 0; i < 9; ++i)
    {
        if (_inventory[i].name == candy_name)
        {
            return true;
        }
    }
    return false;
}

bool Player::isInventoryFull() const
{
    if (_candy_amount >= _MAX_CANDY_AMOUNT)
    {
        return true;
    }
    else
    {
        return false;
    }
}
