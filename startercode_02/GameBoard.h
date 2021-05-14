#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include <vector>
#define MAX_DIM 26

class GameBoard {
public:

    // Constructor/Deconstructor
    GameBoard();
    ~GameBoard();

    // print the board
    void displayBoard();

    bool placeTile(char row, int col, Tile* tile);
    bool isEmptySpace(int row, int col);
    bool isValidMove(int row, int col, Tile* tile);
    
private:
    
    int row;
    int col;
    char alphabets[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int tilesOnBoard;

    // board : a vector of vectors of tile
    std::vector<std::vector<Tile*>> board;

};

#endif