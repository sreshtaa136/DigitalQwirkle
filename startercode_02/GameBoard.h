#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include <vector>
#include <string>
#define MAX_DIM 26
#define QWIRKLE_SCORE 6
#define ONE_TILE_SCORE 1

class GameBoard {
public:

    // Constructor/Deconstructor
    GameBoard();
    ~GameBoard();

    // print the board
    void displayBoard();

    // place player's tile on board at given row and column
    bool placeTile(char row, int col, Tile* tile);

    // check if the given position is empty
    bool isEmptySpace(int row, int col);

    // check if the position is valid according to qwirkle rules
    bool isValidPosition(int row, int col, Tile* tile);

    bool checkDuplicates(int row, int col, std::string direction, Tile* tile);
    
    // calculate adjacent tiles above the current position
    int totalTilesAbove(int row, int col);

    // calculate adjacent tiles below the current position
    int totalTilesBelow(int row, int col);

    // calculate adjacent tiles to the left of the current position
    int totalTilesAtLeft(int row, int col);

    // calculate adjacent tiles to the right of the current position
    int totalTilesAtRight(int row, int col);

    // calculate total adjacent tiles in the row where current position is
    int totalTilesInRow(int row, int col);

    // calculate total adjacent tiles in the column where current position is
    int totalTilesInCol(int row, int col);

    // check adjacent tiles in four directions for given position
    bool hasTileAbove(int row, int col);
    bool hasTileBelow(int row, int col);
    bool hasTileAtRight(int row, int col);
    bool hasTileAtLeft(int row, int col);

    // check if the current line exceeds six tiles
    bool checkLine(int row, int col);

    // calculate the points after adding a tile at current position
    int calculatePoints(char row, int col);

    bool isQwirkle(int row, int col);

    int charToInt(char c);


    
private:
    
    int row;
    int col;
    char alphabets[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int tilesOnBoard;

    // board : a vector of vectors of tile
    std::vector<std::vector<Tile*> > board;

};

#endif