#include <iostream>
#include <cstdlib> // For rand() function
#include "Game.h"

using namespace std;

Game::Game()
{
    board = Board();
    players.push_back(Player());
    players.push_back(Player());
    CandyStore candyStore;
}

void Game::startGame()
{
    addCandyStore(board);
    ChooseCharacters();
}

bool Game::compareStrings(string str1, string str2)
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

void Game::displayCharacterAvailable(Character character) // helper function for printCharacters
{
    cout << "Character: " << character.name << endl;
    cout << "Stamina: " << character.stamina << endl;
    cout << "Gold: " << character.gold << endl;

    cout << "Candies: ";
    int size = character.candies.size();
    for (int i = 0; i < size; i++)
    {
        if (i % 3 == 0)
        {
            cout << endl;
        }
        cout << "[" << character.candies[i].name << "]     ";
    }
    cout << endl;

    cout << "-----------------------------------------------" << endl;
}

void Game::printCharacters(vector<Character> characters)
{
    int size = characters.size();
    for (int i = 0; i < size; i++)
    {
        displayCharacterAvailable(characters.at(i));
    }
}

vector<Character> Game::loadcharacters(string out_filename)
{
    vector<Character> characters;
    ifstream out_file_in(out_filename);
    string temp1, temp2;

    if (!out_file_in.is_open())
    {
        cout << "out_File doesn't exist" << endl;
        return characters;
    }

    string temp;
    getline(out_file_in, temp); // get rid of header on top of out_file
    string line;

    while (getline(out_file_in, line))
    {
        if (line.length() == 0)
        {
            continue;
        }
        else
        {
            Character character;

            stringstream ss(line);

            getline(ss, character.name, '|');
            getline(ss, temp1, '|');
            character.stamina = stoi(temp1);

            getline(ss, temp2, '|');
            character.gold = stoi(temp2);

            getline(ss, line, '\n');
            stringstream candy(line);
            string candyName;
            while (getline(candy, candyName, ','))
            {
                Candy candies;
                candies.name = candyName;
                character.candies.push_back(candies);
            }

            characters.push_back(character);
        }
    }

    out_file_in.close();
    return characters;
}

void Game::removeCharacter(vector<Character> &characters, string &characterName)
{
    for (int i = 0; i < int(characters.size()); i++)
    {
        if (characters.at(i).name == characterName)
        {
            for (int j = i; j < int(characters.size()) - 1; j++)
            {
                characters.at(j) = characters.at(j + 1);
            }
            characters.pop_back();
            break;
        }
    }
}
vector<Player> Game::setCharacter(vector<Player> players, vector<Character> characters)
{
    if (characters.size() < 2)
    {
        cout << "Not enough characters selected" << endl;
        return players;
    }
    for (int i = 0; i < 2; i++)
    {
        players.at(i).setCharacterName(characters.at(i).name);
        players.at(i).setGold(characters.at(i).gold);
        players.at(i).setStamina(characters.at(i).stamina);
        players.at(i).setInventory(characters.at(i).candies);
    }

    return players;
}

void Game::ChooseCharacters()
{
    int participants;
    string playerName;
    vector<Character> characters;
    vector<Player> players;
    vector<Character> selectedCharacter;
    string chosenCharacterName;

    characters = loadcharacters("characters.txt");

    cout << GREEN << "Welcome to the game of candyland." << RESET << endl;
    do
    {
        cout << "Enter the number of participants (2 required)" << endl;
        cin >> participants;

        if (participants != 2)
        {
            cout << "Please choose 2 participants." << endl;
        }
    } while (participants != 2);

    for (int i = 0; i < participants; i++)
    {
        Player player;
        players.push_back(player);
    }

    for (int i = 0; i < participants; i++)
    {
        cout << "Enter player " << i + 1 << " name:" << endl;
        cin.clear();
        cin.ignore(100000, '\n');
        cin >> playerName;

        players.at(i).setPlayerName(playerName);

        cout << GREEN << "Awesome! Here is a list of characters a player can select from:" << RESET << endl;
        printCharacters(characters);
        // choose character
        cout << GREEN << "Choose a character you would like to play as" << RESET << endl;
        cin >> chosenCharacterName;

        bool found = false;
        for (int j = 0; j < int(characters.size()); j++)
        {
            //
            if (compareStrings(characters.at(j).name, chosenCharacterName))
            {
                selectedCharacter.push_back(characters.at(j));
                found = true;

                // remove character chosen by first player
                removeCharacter(characters, chosenCharacterName);
                break;
            }
        }

        if (!found)
        {
            cout << "You chose wrong try again." << endl;
            i--;
        }

        if (found)
        {
            char choice;
            cout << BLUE << "Do you want to visit the store(Y = Yes, N = No)" << RESET << endl;
            cin >> choice;

            vector<Candy> candies;
            candies = candystore.loadCandy("candies.txt");

            if (choice == 'N' || choice == 'n')
            {
                continue;
            }
            else if (choice == 'Y' || choice == 'y')
            {
                firstStore(candies, players, participants);
            }
        }
    }
    players = setCharacter(players, selectedCharacter);

    turns(players, board);
}

void Game::firstStore(vector<Candy> candies, vector<Player> &players, int playerIndex)
{
    string candyToReplace;
    string candyToBuy;
    Candy foundCandy;
    Candy swapCandy;
    char option2;

    if (players[playerIndex].isInventoryFull())
    {
        cout << RED << "YOU HAVE THE MAXIMUM AMOUNT OF CANDY" << RESET << endl;
    }
    // crashes at the which candy do you want to switch for some reason.

        cout << "DO YOU WANT TO SWITCH CANDY(Y = Yes, N = NO)" << endl;
        cin >> option2;

        if (option2 == 'N' || option2 == 'n')
        {
            return;
        }

        cout << "Which candy do you want to switch" << endl;

        players[playerIndex].printInventory();
        getline(cin, candyToReplace);

        foundCandy = players[playerIndex].findCandy(candyToReplace);

        if (foundCandy.name == candyToReplace)
        {
            players[playerIndex].removeCandy(candyToReplace);
            cout << "Here are the candies you can buy." << endl;
            candies = candystore.loadCandy("candies.txt");
            candystore.printCandyAvailable(candies);

            cout << "NOW YOU WILL BUY A CANDY. Which candy do you want to buy now" << endl;
            getline(cin, candyToBuy);

            for (int i = 0; i < int(candies.size()); i++)
            {
                if (candies[i].name == candyToBuy)
                {
                    swapCandy = candies[i];
                    break;
                }
            }

            int price = swapCandy.price;
            if (players[playerIndex].getGold() < price)
            {
                cout << "You don't have enough gold" << endl;
            }
        }
    

    else
    {
        players[playerIndex].setGold(players[playerIndex].getGold() - swapCandy.price);
        players[playerIndex].addCandy(swapCandy);
    }
}

void Game::displayMenu()
{
    cout << "Please select a menu option:" << endl;
    cout << "1. Draw a card" << endl;
    cout << "2. Use candy" << endl;
    cout << "3. Show player stats" << endl;
}

void Game::playTurn(vector<Player> &players, int playerIndex)
{

    int choice;

    // Display the menu
    displayMenu();

    while (choice < 1 || choice > 3)
    {
        cout << "Enter your choice" << endl;

        cin >> choice;

        // Check if the input is a valid integer and within the allowed range
        if (cin.fail() || choice < 1 || choice > 3)
        {
            cin.clear();
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
        else
        {
            break; // Exit the loop if a valid choice is entered
        }
    }

    switch (choice)
    {
    case 1:
        drawAndMovePlayer(playerIndex, board, players);
        break;
    case 2:
        UseCandy(players, playerIndex);
        break;
    case 3:
        for (int i = playerIndex; i == playerIndex; i++)
        {
            cout << "player " << i + 1 << " stats are" << endl;
            players.at(i).printStats(playerIndex);
        }
        playTurn(players, playerIndex);
        break;
    default:
        cout << "Invalid choice" << endl;
    }
}

void Game::turns(vector<Player> &players, Board &board)
{
    int participants = 2;
    int currentPlayerIndex = 0;
    // have to draw green to win at the end
    while (board.getPlayerPosition(currentPlayerIndex) < board.getBoardSize() - 1)
    {
        handleSameTile(board, currentPlayerIndex, players);

        cout << CYAN << "It's " << players[currentPlayerIndex].getPlayerName() << "'s turn" << RESET << endl;
        playTurn(players, currentPlayerIndex);

        if (board.getPlayerPosition(currentPlayerIndex) >= 82)
        {
            cout << RED << "Congratulations! " << players[currentPlayerIndex].getPlayerName() << " .You reached the Candy Castle and won the game!" << RESET << endl;
            players[currentPlayerIndex].printStats(currentPlayerIndex);
            writeToFile(players);
            return;
        }

        // Switch to the next player
        currentPlayerIndex = (currentPlayerIndex + 1) % participants;
    }
}

void Game::drawAndMovePlayer(int playerIndex, Board &board, vector<Player> &players)
{
    const int COLOR_COUNT = 9;
    const drawCard CARDS[COLOR_COUNT] = {{"MAGENTA", 0}, {"GREEN", 0}, {"BLUE", 0}, {"MAGENTA", 0}, {"GREEN", 0}, {"BLUE", 0}, {"DOUBLE MAGENTA", 1}, {"DOUBLE GREEN", 1}, {"DOUBLE BLUE", 1}};

    // Simulate drawing a color
    int randomIndex = rand() % COLOR_COUNT;
    drawCard drawCard = CARDS[randomIndex];

    cout << players[playerIndex].getPlayerName() << ". YOU GOT " << drawCard.color << ". Your game piece advances to the " << drawCard.color << " tile" << endl;

    int moveBy = 0;

    // If the drawn card is not a double and has the color MAGENTA, GREEN, or BLUE,
    // move the player based on their current position modulo 3.
    // The moveBy value depends on the color and position.
    if (drawCard.isdouble == 0 && drawCard.color == "MAGENTA")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 3;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 2;
        }
        else
        {
            moveBy = 1;
        }
    }
    else if (drawCard.isdouble == 0 && drawCard.color == "GREEN")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 1;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 3;
        }
        else
        {
            moveBy = 2;
        }
    }
    else if (drawCard.isdouble == 0 && drawCard.color == "BLUE")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 2;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 1;
        }
        else
        {
            moveBy = 3;
        }
    }
    // If the drawn card is a double and has the color MAGENTA, GREEN, or BLUE,
    // move the player based on their current position modulo 3 + color to go to.
    // The moveBy value depends on the color and position.
    else if (drawCard.isdouble == 1 && drawCard.color == "DOUBLE MAGENTA")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 6;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 5;
        }
        else
        {
            moveBy = 4;
        }
    }
    else if (drawCard.isdouble == 1 && drawCard.color == "DOUBLE GREEN")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 4;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 6;
        }
        else
        {
            moveBy = 5;
        }
    }
    else if (drawCard.isdouble == 1 && drawCard.color == "DOUBLE BLUE")
    {
        if (board.getPlayerPosition(playerIndex) % 3 == 0)
        {
            moveBy = 5;
        }
        else if (board.getPlayerPosition(playerIndex) % 3 == 1)
        {
            moveBy = 4;
        }
        else
        {
            moveBy = 6;
        }
    }

    int move = moveBy;
    board.movePlayer(playerIndex, move);
    cout << "New position: " << board.getPlayerPosition(playerIndex) << endl;
    board.displayBoard();

    CheckIfPlayerIsOnCandyStore(board, playerIndex, players);
    hiddenTreasure(players, playerIndex, board);
    handleCalamity(players, playerIndex);

    // special tiles. 25% for each happening
    if (rand() % 4 == 0)
    {
        // move forward 4 moves and if 4 tiles from the end you win
        cout << "YOU LANDED ON A SPECIAL TILE " << players[playerIndex].getPlayerName() << ".......  THIS CAN BE GOOD OR BAD :)" << endl;

        int randTriger = rand() % 4;

        if (randTriger == 0)
        {
            cout << "You landed on a SHORTCUT TILE. *****LUCKY*****" << endl;
            cout << "You have been blessed with 4 moves" << endl;

            if (board.getPlayerPosition(playerIndex) == 78)
            {
                board.shortcuttile(board, playerIndex);
                board.displayBoard();
                cout << "Congratulations!" << players[playerIndex].getPlayerName() << "You reached the Candy Castle and won the game!" << endl;
                players[playerIndex].printStats(playerIndex);
                writeToFile(players);
                return;
            }

            board.shortcuttile(board, playerIndex);
            board.displayBoard();
        }
        else if (randTriger == 1)
        {
            // you can go again
            cout << "Your landed on an ICE CREAM STOP TILE: ******YOU CAN GO AGAIN*****" << endl;
            cout << players[playerIndex].getPlayerName() << " goes again" << endl;
            playTurn(players, playerIndex);
        }
        else if (randTriger == 2)
        {
            // 4 tiles back and and lose 5-10 gold
            cout << "You landed on a GUMDROP FOREST TILE. *****UNLUCKY******" << endl;
            cout << "You have been cursed to move 4 tiles back ***********  :)" << endl;
            if (board.getPlayerPosition(playerIndex) < 4)
            {
                cout << "YOU ARE BACK TO THE START" << endl;
                board.movePlayer(playerIndex, -4);
            }
            board.GumdropEffect(board, playerIndex);

            int randGold = rand() % 6 + 5;
            players[playerIndex].setGold(players[playerIndex].getGold() - randGold);
            cout << "UNFORTUNATELY YOU HAVE MOVED BACK 4 SPACES AND LOST " << randGold << " Gold" << endl;
            board.displayBoard();
        }
        else
        {
            // back to previous position and lose immunity candy
            cout << "You landed on a Gingerbread House Tile. *****UNLUCKY*****" << endl;
            cout << "you move back by " << -moveBy << endl;
            board.movePlayer(playerIndex, -moveBy);
            board.displayBoard();
            string candy[3] = {"Bubblegum Blast", "Sparkling Sapphire", "Caramel Comet"};
            int randIndex = rand() % 3;
            string randCandy = candy[randIndex];

            if (players[playerIndex].hasCandy(randCandy))
            {
                cout << "You are losing a random Immunity candy"
                     << " I am taking.... " << randCandy << endl;
                cout << GREEN << RESET << endl;
                players[playerIndex].removeCandy(randCandy);
            }
            else
            {
                cout << "You are lucky you don't have an immunity candy " << players[playerIndex].getPlayerName() << " cause i was going to snatch it away from you" << endl;
            }
        }
    }
}

void Game::UseCandy(vector<Player> &players, int playerIndex)
{
    Candy candyFound;
    string candy;
    vector<Candy> candies;
    cout << "Here are the candeis you can buy." << endl;
    candies = candystore.readCandiesFile("candies.txt");

    players[playerIndex].printInventory();
    cout << "Enter a candy you wish to use (Enter Exact Same As Inventory)" << endl;
    cin.ignore(10000, '\n');
    getline(cin, candy);

    // Find the candy in the player's inventory
    candyFound = players[playerIndex].findCandy(candy);
    if (candyFound.name == candy)
    {
        cout << "FOUND YOUR CANDY" << endl;
    }
    else
    {
        cout << "NOT FOUND" << endl;
        cout << "You don't have " << candy << " in your inventory." << endl;
        playTurn(players, playerIndex);
        return;
    }
    // store candy struct values in foundcandy to use
    for (int i = 0; i < int(candies.size()); i++)
    {
        if (compareStrings(candyFound.name, candies.at(i).name))
        {
            candyFound = candies.at(i);
            break;
        }
    }

    // Check the type of candy and perform corresponding actions
    if (candyFound.candyType == "magical")
    {
        cout << "You have used " << candy << ". You have boosted your stamina." << endl;
        int staminaGain = candyFound.effectValue;
        players[playerIndex].setStamina(players[playerIndex].getStamina() + staminaGain);
        // Remove the used candy from the player's inventory
        players[playerIndex].removeCandy(candy);
        cout << players[playerIndex].getPlayerName() << " has gained " << staminaGain << endl;
    }
    else if (candyFound.candyType == "poison")
    {
        // since you are effecting other player
        int otherplayer = (playerIndex + 1) % 2;
        cout << "You have used " << candy << ". Your opponent will lose some stamina." << endl;
        int staminaLoss = candyFound.effectValue;
        players[otherplayer].setStamina(players[otherplayer].getStamina() - staminaLoss);
        cout << players[otherplayer].getPlayerName() << " has lost " << staminaLoss << " stamina." << endl;
        players[playerIndex].removeCandy(candy);
    }
    else if (candyFound.candyType == "immunity")
    {
        cout << "Something was suposed to happen" << endl;
        // if you have an immunity
        // protect against mild and medium poison venom vortex and lucky licorice
    }

    // Continue with the player's turn
    playTurn(players, playerIndex);
}

void Game::addCandyStore(Board &board)
{
    int position1 = 6;
    board.addCandyStore(position1);

    int position2 = 40;
    board.addCandyStore(position2);

    int position3 = 68;
    board.addCandyStore(position3);
}

void Game::CheckIfPlayerIsOnCandyStore(Board &board, int playerIndex, vector<Player> &players)
{
    // Check for CandyStore at position 6, 40, and 68
    vector<int> candyStorePositions = {6, 40, 68};
    vector<Candy> candies;

    for (int i = 0; i < int(candyStorePositions.size()); i++)
    {
        if (board.isPositionCandyStore(candyStorePositions[i]) && board.getPlayerPosition(playerIndex) == candyStorePositions[i])
        {
            cout << RED << "***********************YOU LANDED ON A CANDYSTORE***************************" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
            cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << RESET << endl;

            handleLandOnCandyStore(candies, playerIndex, players);
            break;
        }
    }
}

void Game::handleLandOnCandyStore(vector<Candy> &candies, int playerIndex, vector<Player> &players)
{
    string candyToAdd;
    string candyToReplace;
    string candyToBuy;
    Candy add_candy;
    Candy foundCandy;
    Candy swapCandy;
    char option;
    char option2;
    cout << "Do you want to visit the store( N = NO, anythingelse for yes)" << endl;
    cin >> option;
    if (option == 'N' || option == 'n')
    {
        return;
    }

    cout << "Here are the candeis you can buy." << endl;
    candies = candystore.loadCandy("candies.txt");
    candystore.printCandyAvailable(candies);
    // check if inventory is full then exeucte swap to buy candy
    if (players[playerIndex].isInventoryFull())
    {
        cout << "Your inventory is full" << endl;
        cout << "DO YOU WANT TO SWITCH CANDY(N = NO, anythingelse for yes)" << endl;
        cin >> option2;

        if (option2 == 'N' || option2 == 'n')
        {
            return;
        }

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Which candy do you want to switch" << endl;
        cout << endl;
        players[playerIndex].printInventory();
        getline(cin, candyToReplace);

        foundCandy = players[playerIndex].findCandy(candyToReplace);
        // cout << GREEN << "EXECUTED" << RESET << endl;
        if (compareStrings(foundCandy.name, candyToReplace))
        {
            players[playerIndex].removeCandy(candyToReplace);
            cout << "Her is your updated inventory" << endl;
            players[playerIndex].printInventory();

            cout << "NOW YOU WILL BUY A CANDY. Which candy do you to buy now" << endl;
            getline(cin, candyToBuy);

            for (int i = 0; i < int(candies.size()); i++)
            {
                if (compareStrings(candyToBuy, candies.at(i).name))
                {
                    swapCandy = candies.at(i);
                    break;
                }
            }
            // cout << RED << "EXECUTED" << RESET << endl;
            // check if they have enough gold to buy
            int price = swapCandy.price;

            if (players[playerIndex].getGold() > price)
            {
                players[playerIndex].setGold(players[playerIndex].getGold() - swapCandy.price);
                players[playerIndex].addCandy(swapCandy);
            }
            else
            {
                cout << "you don't have eneough gold" << endl;
                cout << "you blundered on your math no more buying for you. BETTER LUCK NEXT TIME" << endl;
            }
        }
        else
        {
            cout << "You don't have the candy" << endl;
        }
    }
    else
    {
        cout << "Here are the candeis you can buy." << endl;
        candystore.printCandyAvailable(candies);
        cout << "Which candy do you want" << endl;
        getline(cin, candyToAdd);
        for (int i = 0; i < 3; i++)
        {
            if (candyToAdd == candies[i].name)
            {
                add_candy = candies[i];
                break;
            }
        }
        // check if they have enough gold to buy

        int price = add_candy.price;
        if (players[playerIndex].getGold() < price)
        {
            cout << "you don't have eneough gold" << endl;
        }
        else
        {
            players[playerIndex].setGold(players[playerIndex].getGold() - add_candy.price);
            players[playerIndex].addCandy(add_candy);
            cout << "Candy added to your inventory" << endl;
            cout << endl;
        }
    }
}
void Game::handleSameTile(Board &board, int playerIndex, vector<Player> &players)
{
    // if they are on the same tile
    // modify index to fit the right person
    if (board.getPlayerPosition(0) == board.getPlayerPosition(1) && board.getPlayerPosition(0) != 0)
    {
        cout << "you are on the same tile" << endl;
        int otherPerson = (playerIndex + 1) % 2;

        int randAmount = (rand() % (30 - 5 + 1) + 5);

        players[otherPerson].setGold(players[otherPerson].getGold() - randAmount);

        cout << "Player " << players[otherPerson].getPlayerName() << " is losing " << randAmount << " of gold" << endl;

        // the player who landed first gets pushed back one tile
        board.movePlayer(playerIndex, -1);
        board.displayBoard();
    }
}
void Game::hiddenTreasure(vector<Player> &players, int playerIndex, Board &board)
{
    int pos1 = rand() % 83;
    int pos2 = rand() % 83;
    int pos3 = rand() % 83;
    // Check if the player is on a hidden treasure tile
    if (board.getPlayerPosition(playerIndex) == pos1 || board.getPlayerPosition(playerIndex) == pos2 || board.getPlayerPosition(playerIndex) == pos3)
    {
        cout << "YOU LANDED ON A HIDDEN TREASURE TILE. IM ROLLING YOUR CHANCES " << players[playerIndex].getPlayerName() << endl;
        hiddenHelper(players, playerIndex);
    }
}

void Game::hiddenHelper(vector<Player> &players, int playerIndex)
{
    // randtrigger is the percent of which hidden tile will hapen
    int randTrigger = rand() % 10;
    vector<QuestionAnswer> riddles;
    riddles = readRiddleFile("riddles.txt");
    if (randTrigger >= 0 && randTrigger < 3) // 30% chance for Stamina Refill
    {
        cout << "You need to answer these two riddles correctly or you lose the hidden treasure." << endl;
        if (riddleQuestion(riddles))
        {
            cout << "YAY. You landed on a STAMINA REFILL. *****LUCKY*****" << endl;
            int randStamina = (rand() % (30 - 10 + 1) + 10);
            cout << "You have been blessed with " << randStamina << " stamina." << endl;
            players[playerIndex].setStamina((players[playerIndex].getStamina() + randStamina));
        }
        else
        {
            cout << "You failed to solve the riddles. Hidden treasure lost." << endl;
        }
    }
    else if (randTrigger == 4) // 10% chance for Gold Windfall
    {
        cout << "You need to answer these two riddles correctly or you lose the hidden treasure." << endl;
        if (riddleQuestion(riddles))
        {
            cout << "YAY. You landed on Gold Windfall. ";
            int randomGold = (rand() % (40 - 20 + 1) + 20);
            cout << "You have been blessed with " << randomGold << " gold." << endl;
            players[playerIndex].setGold((players[playerIndex].getGold() + randomGold));
        }
        else
        {
            cout << "You failed to solve the riddles. Hidden treasure lost." << endl;
        }
    }
    else if (randTrigger >= 7 && randTrigger < 10) // 30% chance of jellybean vigor
    {
        if (riddleQuestion(riddles))
        {
            int randomChance = rand() % 100;
            if (randomChance < 70)
            {
                cout << "You Aquired JellyBean of Vigor. You will get 50 points of stamina" << endl;
                players[playerIndex].setStamina(players[playerIndex].getStamina() + 50);
                if (players[playerIndex].getStamina() > 100)
                {
                    cout << "You have full stamina better luck next time" << endl;
                }
            }
            else
            {
                if (riddleQuestion(riddles))
                {
                    cout << "You are supposed to get a random treauser";
                    // this doesn't work;
                    // hiddenTreasure(players, playerIndex, board);
                }
            }
        }
    }
}

// Function to read the out_file, extract questions and answers, and store them
vector<QuestionAnswer> Game::readRiddleFile(string out_filename)
{
    vector<QuestionAnswer> quizList;

    ifstream out_file(out_filename);

    if (!out_file.is_open())
    {
        cout << "Error: Could not open the out_file." << endl;
        return quizList;
    }

    string line;
    while (getline(out_file, line))
    {
        stringstream lineStream(line);

        QuestionAnswer quiz;
        getline(lineStream, quiz.question, '|');
        getline(lineStream, quiz.answer, '|');

        quizList.push_back(quiz);
    }

    out_file.close();
    return quizList;
}

// Function to run the quiz and return ture if passed
bool Game::riddleQuestion(vector<QuestionAnswer> quizList)
{
    bool allCorrect = true; // Assume all questions are correct initially

    int randRiddle = rand() % 4; // pick random quesiton

    QuestionAnswer quiz = quizList[randRiddle];

    cout << "Question: " << quiz.question << endl;

    string userAnswer;
    cout << "Your Answer: ";
    cin.ignore(1000, '\n');
    getline(cin, userAnswer);

    bool isCorrect = (userAnswer == quiz.answer);

    if (isCorrect)
    {
        cout << "Correct!" << endl;
    }
    else
    {
        cout << "Incorrect. The correct answer is: " << quiz.answer << endl;
    }

    cout << "---------------------" << endl;

    // Update the overall correctness
    if (!isCorrect)
    {
        allCorrect = false;
    }

    return allCorrect;
}

void Game::handleCalamity(vector<Player> &players, int playerIndex)
{
    int randNumber = rand() % 100;
    if (randNumber > 80)
    {
        cout << "A calamity has struck you " << players[playerIndex].getPlayerName() << endl;

        int randTriger = rand() % 100;

        if (randTriger >= 70) // 30% chance of happening
        {
            cout << "YOU RAN INTO CANDY BANDITS" << endl;
            cout << "OH NO CANDY BANDITS HAVE SWIPED YOUR GOLD COINS" << endl;
            int randGold = rand() % 10 + 1;
            players[playerIndex].setGold(players[playerIndex].getGold() - randGold);
            cout << "you lost " << randGold << " gold." << endl;
        }
        else if (randTriger >= 35 && randTriger < 40) // 5% chance of happening
        {
            cout << "Oh no you got lost in the LOLLIPOP LABYRINTH! But you can recover if you win a game of ROCK PAPER SCISSORS." << endl;
            if (playRockPaperScissors())
            {
                playTurn(players, playerIndex);
            }
            else
            {
                cout << "You lose a turn." << endl;
            }
        }
        else if (randTriger < 15) // 15% chance of happening
        {
            cout << "Watch out a candy Avalanche has struck!" << endl;
            cout << "but you can recover the damage if you win a game of ROCK PAPER SCISSORS" << endl;
            int randomstaminaLost = rand() % (10 - 5 + 1) + 5;
            players[playerIndex].setStamina(players[playerIndex].getStamina() - randomstaminaLost);
            if (playRockPaperScissors())
            {
                cout << "You recovered everything" << endl;
                players[playerIndex].setStamina(players[playerIndex].getStamina() + randomstaminaLost);
            }
            else
            {
                cout << "You lost a turn and " << randomstaminaLost << "Stamina" << endl;
            }
        }
        else // 10% chance of happening
        {
            cout << "Oops! you are stuck in a sticky taffy trap" << endl;
            string magicalCandy[3] = {"Mystic Marshmallow", "Frosty Fizz", "Crimson Crystal"};
            for (int i = 0; i < 3; i++)
            {
                if (players[playerIndex].hasCandy(magicalCandy[i]))
                {
                    cout << "You have a magical candy so you regained the turn" << endl;
                    break;
                }
            }
        }
    }
}
// check RPS choices
bool Game::isValidInput(char choice)
{
    return (choice == 'r' || choice == 'p' || choice == 's');
}
// play against randomchoice/robot
bool Game::playRockPaperScissors()
{
    char playerChoice;
    bool flag = true;

    do
    {
        cout << "Enter your choice (r, p, s): ";
        cin.ignore(1000, '\n');
        cin >> playerChoice;
    } while (!isValidInput(playerChoice));

    do
    {

        char robotChoices[3] = {'r', 'p', 's'};
        char robotChoice = robotChoices[rand() % 3];

        if (playerChoice == robotChoice)
        {
            cout << "It's a tie! Let's play again." << endl;
            do
            {
                cout << "Enter your choice (r, p, s): ";
                cin.ignore(1000, '\n');
                cin >> playerChoice;
            } while (!isValidInput(playerChoice));

            flag = true; // run game again in case of tie.
        }
        else if ((playerChoice == 'r' && robotChoice == 's') ||
                 (playerChoice == 'p' && robotChoice == 'r') ||
                 (playerChoice == 's' && robotChoice == 'p'))
        {
            cout << "You win!" << endl;
            flag = false;
        }
        else
        {
            cout << "Robot wins!" << endl;
            flag = false;
            return false;
        }
    } while (flag);

    return true; // Continue playing
}

// out_file
void Game::writeToFile(vector<Player> &players)
{
    ofstream out_file("results.txt", ios::app); // make file if it doesn't exist
    if (out_file.is_open())
    {
        for (int i = 0; i < 2; i++)
        {
            out_file << "Player: " << players[i].getPlayerName() << endl;
            out_file << "Character Name: " << players[i].getCharacterName() << endl;
            out_file << "Stamina: " << players[i].getStamina() << endl;
            out_file << "Gold: " << players[i].getGold() << endl;

            vector<string> candies = players[i].getInventory();
            out_file << "Candies: ";
            for (int j = 0; j < int(candies.size()); j++)
            {
                out_file << candies[j];
                if (j != int(candies.size() - 1))
                {
                    out_file << ", ";
                }
            }
            out_file << endl;
        }
        out_file.close();
    }
}
