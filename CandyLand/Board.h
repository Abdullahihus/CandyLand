#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#define RED "\033[;41m"               /* Red */
#define GREEN "\033[;42m"             /* Green */
#define BLUE "\033[;44m"              /* Blue */
#define MAGENTA "\033[;45m"           /* Magenta */
#define CYAN "\033[;46m"              /* Cyan */
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct drawCard
{
    string color;
    double isdouble;
};

struct Tile
{
    string color;
    string tile_type;
};

class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player_positions[2]; // Array for two players

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    // playerIndex-> Modified to accomaodate two player
    // also check if playerIndex is out of range of two players
    bool setPlayerPosition(int playerIndex, int newPosition); 
    int getPlayerPosition(int playerIndex) const;             

    int getBoardSize() const;
    int getCandyStoreCount() const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int);

    bool movePlayer(int playerIndex, int tileToMoveForward); 
    
    // run effect to moveplayer for special tiles
    void shortcuttile(Board &board, int playerIndex); 
    void GumdropEffect(Board &board, int playerIndex); 

};

#endif
