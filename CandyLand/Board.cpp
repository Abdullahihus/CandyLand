#include "Board.h"

Board::Board()
{
    resetBoard();
}
void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    // initialize player positions to tile 0 -> we go from 0 to 82
    _player_positions[0] = 0;
    _player_positions[1] = 0;
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }

    Tile target = _tiles[position];

    cout << target.color << " ";

    if (position == _player_positions[0])
    {
        cout << "X";
    }
    else if (position == _player_positions[1])
    {
        cout << "Y";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int playerIndex, int newPosition)
{
    if (playerIndex >= 0 && playerIndex < 2 && newPosition >= 0 && newPosition < _BOARD_SIZE)
    {
        _player_positions[playerIndex] = newPosition;
        return true;
    }
    return false;
}

int Board::getPlayerPosition(int playerIndex) const
{
    if (playerIndex >= 0 && playerIndex < 2)
    {
        return _player_positions[playerIndex];
    }
    return -1; 
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int playerIndex, int tileToMoveForward)
{
    int currentPlayerPosition = _player_positions[playerIndex];
    int newPlayerPosition = tileToMoveForward + currentPlayerPosition;

    if (newPlayerPosition >= 0 && newPlayerPosition < _BOARD_SIZE)
    {
        _player_positions[playerIndex] = newPlayerPosition;
        return true;
    }

    return false;
}

void Board::shortcuttile(Board &board, int playerIndex)
{
    board.movePlayer(playerIndex, 4);
}
void Board::GumdropEffect(Board &board, int playerIndex)
{
    board.movePlayer(playerIndex, -4);
}
