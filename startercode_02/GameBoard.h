#ifndef ASSIGN2_GAMEBOARD_H
#define ASSIGN2_GAMEBOARD_H

#include "Tile.h"
#include <vector>
#include <string>
#define MAX_DIM 26
#define MAX_LINE_SIZE 6
#define QWIRKLE_SCORE 6
#define ONE_TILE_SCORE 1

class GameBoard {
public:

    // Constructor/Deconstructor
    GameBoard();
    ~GameBoard();

    // Returns the board dimensions as a string.
    std::string dimensionsToString();

    /*
    * Places a player's tile on board at given row and column and
    * returns true if the tile is placed.
    */
    bool placeTile(char row, int col, Tile* tile);

    // Returns true if the given position is empty.
    bool isEmptySpace(int row, int col);

    /*
    * Returns true if the position is valid according to qwirkle rules.
    * Checks if:
    * 1. The tile is placed in a line with the same color/shape
    *    (A line is either all one shape or all one color.)
    * 2. There cannot be duplicate tiles in a line in which the current tile
    *    is being placed.
    */
    bool isValidPosition(int row, int col, Tile* tile);

    /*
    * Returns true if there are no duplicates in the given direction.
    * Direction can be above, below, right, left.
    */
    bool checkDuplicates(int row, int col, std::string direction, Tile* tile);
    
    // Returns the number of adjacent tiles above the current position.
    int totalTilesAbove(int row, int col);

    // Returns the number of adjacent tiles below the current position.
    int totalTilesBelow(int row, int col);

    // Returns the number of adjacent tiles to the left of the current position.
    int totalTilesAtLeft(int row, int col);

    // Returns the number of adjacent tiles to the right of the current position.
    int totalTilesAtRight(int row, int col);

    // Returns the number of adjacent tiles in the row of the current position.
    int totalTilesInRow(int row, int col);

    // Returns the number of adjacent tiles in the column of the current position.
    int totalTilesInCol(int row, int col);

    // Returns true if there is a tile above.
    bool hasTileAbove(int row, int col);

    // Returns true if there is a tile below.
    bool hasTileBelow(int row, int col);

    // Returns true if there is a tile at right.
    bool hasTileAtRight(int row, int col);

    // Returns true if there is a tile at left.
    bool hasTileAtLeft(int row, int col);

    /*
    * Returns false if the line is not valid according to qwirkle rules.
    * Lines of more than 6 tiles are not allowed.
    */
    bool checkLine(int row, int col);

    // Returns the points after adding a tile at current position.
    int calculatePoints(char row, int col);

    /*
    * Returns true if a qwirkle is achieved.
    * A qwirkle is whenever you complete a line of 6 tiles.
    */
    bool isQwirkle(int row, int col);

    // Returns the integer value for a character.
    int charToInt(char c);
    
    // Returns true if all tiles at left are same colour/shape.
    bool checkSameColourOrShapeLeft(int row, int col, Tile* tile);

    // Returns true if all tiles at right are same colour/shape.
    bool checkSameColourOrShapeRight(int row, int col, Tile* tile);

    // Returns true if all tiles above are same colour/shape.
    bool checkSameColourOrShapeAbove(int row, int col, Tile* tile);

    // Returns true if all tiles below are same colour/shape.
    bool checkSameColourOrShapeBelow(int row, int col, Tile* tile);

    // Prints the board.
    void displayBoard();

    // Returns board as a string. Used in save game.
    std::string toString();

    
private:
    
    // Characters for row
    char alphabets[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    // Number of tiles currently on board.
    int tilesOnBoard;

    // Positions of tiles in the order they are placed.
    std::vector<std::string> positions;

    // Board : a vector of vectors of tile.
    std::vector<std::vector<Tile*> > board;
};

#endif