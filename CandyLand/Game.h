#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Player.h"
#include "Board.h"
#include "CandyStore.h"

// structure to store questions and answers
struct QuestionAnswer
{
    string question;
    string answer;
};

using namespace std;
class Game
{
private:
    Board board;
    vector<Player> players;
    CandyStore candystore;

public:
    Game();
    void startGame();

    bool compareStrings(string str1, string str2);

    void displayCharacterAvailable(Character character);
    void printCharacters(vector<Character> characters);
    vector<Character> loadcharacters(string filename);
    void removeCharacter(vector<Character> &characters, string &characterName);
    vector<Player> setCharacter(vector<Player> players, vector<Character> characters);
    void ChooseCharacters();

    void firstStore(vector<Candy> candies, vector<Player> &players, int playerIndex);

    void displayMenu();

    void playTurn(vector<Player> &players, int); // game turn
    void turns(vector<Player> &players, Board &board);
    void drawAndMovePlayer(int playerIndex, Board &board, vector<Player> &players);

    void UseCandy(vector<Player> &players, int playerIndex);

    void addCandyStore(Board &board);
    void CheckIfPlayerIsOnCandyStore(Board &board, int playerIndex, vector<Player> &players);
    void handleLandOnCandyStore(vector<Candy> &candies, int playerIndex, vector<Player> &players);

    void handleSameTile(Board &board, int playerIndex, vector<Player> &players);

    void hiddenTreasure(vector<Player> &players, int playerIndex, Board &board);
    void hiddenHelper(vector<Player> &players, int playerIndex);
    vector<QuestionAnswer> readRiddleFile(string filename);
    bool riddleQuestion(vector<QuestionAnswer> qaList);

    void handleCalamity(vector<Player> &players, int playerIndex);
    bool isValidInput(char choice);
    bool playRockPaperScissors();

    void writeToFile(vector<Player> &players);
};
#endif
