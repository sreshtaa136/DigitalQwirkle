#include "GameBoard.h"
#include <iostream>

GameBoard::GameBoard() {
    std::vector<Tile*> temp;
    for (int col = 0; col < MAX_DIM; ++col) {
            temp.push_back(nullptr);
	}

    for (int row = 0; row < MAX_DIM; ++row) {
        board.push_back(temp);
	}

    this->tilesOnBoard = 0;
}

GameBoard::~GameBoard() {
    for (int row = 0; row < (int) board.size(); ++row) {
		for (int col = 0; col < (int) board[row].size(); ++col) {
			if (board[row][col] != nullptr) {
                delete board[row][col];
            }
		}
	}
}

bool GameBoard::placeTile(char row, int col, Tile* tile) {
    int rowIdx = charToInt(row);
    bool place = false;

    // check the following conditions
    // 1. the tile space is empty
    // 2. the position is valid according to qwirkle rules
    // 3. a single line does not have more than 6 tiles
    if (isEmptySpace(rowIdx, col) && isValidPosition(rowIdx, col, tile) && !checkLine(rowIdx, col)) 
    {
        board[rowIdx][col] = tile;
        ++tilesOnBoard;
        place = true;
    }
    else { std::cout << "error" << std::endl; }
    
    return place;
}

bool GameBoard::isEmptySpace(int row, int col) {
    bool empty = false;

    if(board[row][col] == nullptr) {
        empty = true;
    }
    
    return empty;
}

bool GameBoard::isValidPosition(int row, int col, Tile* tile) {
    bool valid = false;
    bool rightValid = false;
    bool leftValid = false;
    bool upValid = false;
    bool downValid = false;
    int neighbour = 0;

    // if it's the first tile
    if (tilesOnBoard == 0) {
        valid = true;

    } else { 

        if (hasTileAbove(row, col)) {
            ++neighbour;

            // Check if either the colour or shape are same for adjacent tiles
            if (checkSameColourOrShapeAbove(row, col, tile)) {
                upValid = true;
            }

            // Check if it has any duplicate tile above it
            if (checkDuplicates(row, col, "above", tile)) {
                upValid = false;
            } 
        }
        
        if (hasTileBelow(row, col)) {
            ++neighbour;

            // Check if either the colour or shape are same for adjacent tiles
            if (checkSameColourOrShapeBelow(row, col, tile)) {
                downValid = true;
            }

            // Check if it has any duplicate tile below it
            if (checkDuplicates(row, col, "below", tile)) {
                downValid = false;
            } 
        }
        
        if (hasTileAtLeft(row, col)) {
            ++neighbour;

            // Check if either the colour or shape are same for adjacent tiles
            if (checkSameColourOrShapeLeft(row, col, tile)) {
                leftValid = true;
            }

            // Check if it has any duplicate tile to the left 
            if (checkDuplicates(row, col, "left", tile)) {
                leftValid = false;
            } 
        }

        if (hasTileAtRight(row, col)) {
            ++neighbour;

            // Check if either the colour or shape are same for adjacent tile
            if (checkSameColourOrShapeRight(row, col, tile)) {
                rightValid = true;
            }

            // Check if it has any duplicate tile to the right
            if (checkDuplicates(row, col, "right", tile)) {
                rightValid = false;
            } 
           
        }

        bool oneMatching = upValid || downValid || rightValid || leftValid;

        bool twoMatching = (upValid && downValid) || (rightValid && leftValid) ||
                           (upValid && rightValid) || (upValid && leftValid) ||
                           (downValid && rightValid) || (downValid && leftValid);

        bool threeMatching = (upValid && downValid && rightValid) ||
                             (downValid && rightValid && leftValid) ||
                             (rightValid && leftValid && upValid) ||
                             (upValid && downValid && leftValid);

        bool fourMatching = upValid && downValid && rightValid && leftValid;

        // when there is only when adjacent tile
        if (neighbour == 1 && oneMatching) {
            valid = true;
        }

        // when there are two adjacent tiles
        if (neighbour == 2 && twoMatching) {
            valid = true;
        }

        // when there are three adjacent tiles
        if (neighbour == 3 && threeMatching) {
            valid = true;
        }

        // when there are four adjacent tiles
        if(neighbour == 4 && fourMatching) {
            valid = true;
        }  
    }

    return valid;
}

bool GameBoard::checkSameColourOrShapeLeft(int row, int col, Tile* tile) {
    bool same = false;

    // Check if adjacent tile's colour is same
    if (hasTileAtLeft(row, col)) {
        if (board[row][col-1]->getColour() == tile->getColour()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same colour
            if(hasTileAtLeft(row, col-1)) {
                if (board[row][col-2]->getColour() != board[row][col-1]->getColour()) {
                    same = false;
                }
            }
        } 

        // Check if adjacent tile's shape is same
        else if (board[row][col-1]->getShape() == tile->getShape()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same shape
            if(hasTileAtLeft(row, col-1)) {
                if (board[row][col-2]->getShape() != board[row][col-1]->getShape()) {
                    same = false;
                }
            }
        }
    }
    return same;
}

bool GameBoard::checkSameColourOrShapeRight(int row, int col, Tile* tile) {
    bool same = false;

    // Check if adjacent tile's colour is same
    if (hasTileAtRight(row, col)) {
        if (board[row][col+1]->getColour() == tile->getColour()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same colour
            if(hasTileAtRight(row, col+1)) {
                if (board[row][col+2]->getColour() != board[row][col+1]->getColour()) {
                    same = false;
                }
            }
        } 

        // Check if adjacent tile's shape is same
        else if (board[row][col+1]->getShape() == tile->getShape()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same shape
            if(hasTileAtRight(row, col+1)) {
                if (board[row][col+2]->getShape() != board[row][col+1]->getShape()) {
                    same = false;
                }
            }
        }
    }
    return same;
}

bool GameBoard::checkSameColourOrShapeAbove(int row, int col, Tile* tile) {
    bool same = false;

    // Check if adjacent tile's colour is same
    if (hasTileAbove(row, col)) {
        if (board[row-1][col]->getColour() == tile->getColour()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same colour
            if(hasTileAbove(row-1, col)) {
                if (board[row-2][col]->getColour() != board[row-1][col]->getColour()) {
                    same = false;
                }
            }
        } 

        // Check if adjacent tile's shape is same
        else if (board[row-1][col]->getShape() == tile->getShape()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same shape
            if(hasTileAbove(row-1, col)) {
                if (board[row-2][col]->getShape() != board[row-1][col]->getShape()) {
                    same = false;
                }
            }
        }
    }
    return same;
}

bool GameBoard::checkSameColourOrShapeBelow(int row, int col, Tile* tile) {
    bool same = false;

    // Check if adjacent tile's colour is same
    if (hasTileBelow(row, col)) {
        if (board[row+1][col]->getColour() == tile->getColour()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same colour
            if(hasTileBelow(row+1, col)) {
                if (board[row+2][col]->getColour() != board[row+1][col]->getColour()) {
                    same = false;
                }
            }
        } 

        // Check if adjacent tile's shape is same
        else if (board[row+1][col]->getShape() == tile->getShape()) {
            same = true;

            // Check if the tile next to the adjacent tile is also the same shape
            if(hasTileBelow(row+1, col)) {
                if (board[row+2][col]->getShape() != board[row+1][col]->getShape()) {
                    same = false;
                }
            }
        }
    }
    return same;
}

bool GameBoard::checkDuplicates(int row, int col, std::string direction, Tile* tile) {
    bool duplicateFound = false;

    if (direction.compare("right") == 0) {

        // check all tiles at right for a duplicate
        while (hasTileAtRight(row, col)) {
             if (board[row][col+1]->getColour() == tile->getColour() &&
                 board[row][col+1]->getShape() == tile->getShape()) {
                     duplicateFound = true;
            }
            ++col;
        }
    } else if (direction.compare("left") == 0) {

        // check all tiles at left for a duplicate
        while (hasTileAtLeft(row, col)) {
             if (board[row][col-1]->getColour() == tile->getColour() &&
                 board[row][col-1]->getShape() == tile->getShape()) {
                     duplicateFound = true;
            }
            --col;
        }
    } else if (direction.compare("above") == 0) {

        // check all tiles above for a duplicate
        while (hasTileAbove(row, col)) {
             if (board[row-1][col]->getColour() == tile->getColour() &&
                 board[row-1][col]->getShape() == tile->getShape()) {
                     duplicateFound = true;
            }
            --row;
        }
    } else if (direction.compare("below") == 0) {

        // check all tiles below for a duplicate
        while (hasTileBelow(row, col)) {
             if (board[row+1][col]->getColour() == tile->getColour() &&
                 board[row+1][col]->getShape() == tile->getShape()) {
                     duplicateFound = true;
            }
            ++row;
        }
    }

    return duplicateFound;
}

int GameBoard::totalTilesAbove(int row, int col) {
    int numAbove = 0;

    while(hasTileAbove(row, col)) {
        --row;
        ++numAbove;
    }

    return numAbove;
}

int GameBoard::totalTilesBelow(int row, int col) {
    int numBelow = 0;

    while(hasTileBelow(row, col)) {
        ++row;
        ++numBelow;
    }

    return numBelow;
}

int GameBoard::totalTilesAtLeft(int row, int col) {
    int numLeft = 0;

    while(hasTileAtLeft(row, col)) {
        --col;
        ++numLeft;
    }
    
    return numLeft;
}

int GameBoard::totalTilesAtRight(int row, int col) {
    int numRight = 0;

    while(hasTileAtRight(row, col)) {
        ++col;
        ++numRight;
    }

    return numRight;
}

int GameBoard::totalTilesInRow(int row, int col) {
    return totalTilesAbove(row, col) + totalTilesBelow(row, col) + 1;
}

int GameBoard::totalTilesInCol(int row, int col) {
    return totalTilesAtLeft(row, col) + totalTilesAtRight(row, col) + 1;
}

bool GameBoard::hasTileAbove(int row, int col) {
    bool hasTileAbove = false;

    // Check the row is in bound
    if (row > 0) {

        // Check if there is a tile above
        if (board[row-1][col] != nullptr) {
            hasTileAbove = true;
        }
    }
    return hasTileAbove;
}

bool GameBoard::hasTileBelow(int row, int col) {
    bool hasTileBelow = false;

    // Check the row is in bound
    if (row < MAX_DIM-1) {

        // Check if there is a tile below
        if (board[row+1][col] != nullptr) {
            hasTileBelow = true;
        }
    }
    return hasTileBelow;
}

bool GameBoard::hasTileAtLeft(int row, int col) {
    bool hasTileAtLeft = false;

    // Check the column is in bound
    if (col > 0) {

        // Check if there is a tile at left
        if (board[row][col-1] != nullptr) {
            hasTileAtLeft = true;
        }
    }
    return hasTileAtLeft;
}

bool GameBoard::hasTileAtRight(int row, int col) {
    bool hasTileAtRight = false;

    // Check the column is in bound
    if (col < MAX_DIM-1) {

        // Check if there is a tile at right
        if (board[row][col+1] != nullptr) {
            hasTileAtRight = true;
        }
    }
    return hasTileAtRight;
}


bool GameBoard::checkLine(int row, int col) {
    bool lineNotValid = false;

    if (totalTilesInRow(row, col) > MAX_LINE_SIZE || 
        totalTilesInCol(row, col) > MAX_LINE_SIZE) {
            lineNotValid = true;
    }

    return lineNotValid;
}


bool GameBoard::isQwirkle(int row, int col) {
    bool qwirkle = false;

    if (totalTilesInRow(row, col) == QWIRKLE_SCORE || 
        totalTilesInCol(row, col) == QWIRKLE_SCORE) {
            qwirkle = true;
    }

    return qwirkle;
}

int GameBoard::calculatePoints(char row, int col) {

    int rowIdx = charToInt(row);
    int rowScore = 0;
    int colScore = 0;
    int score = 0;

    // first tile
    if(tilesOnBoard == 0) {
        score = ONE_TILE_SCORE;
    } else {

        // if it is not a qwirkle
        if (!isQwirkle(rowIdx, col)) {
            rowScore = totalTilesInRow(rowIdx, col);
            colScore = totalTilesInCol(rowIdx, col);

            // if tile linked in a col or a row, not both
            if (rowScore == ONE_TILE_SCORE || colScore == ONE_TILE_SCORE) {

                // the current tile is only counted once
                score = rowScore + colScore - 1;
            }
            else {

                // the current tile is counted twice
                score = rowScore + colScore;
            }
            
        }

        // bonus points for qwirkle
        else {
            if (totalTilesInRow(rowIdx, col) == QWIRKLE_SCORE) {
                score += QWIRKLE_SCORE;
            }
            if (totalTilesInCol(rowIdx, col) == QWIRKLE_SCORE) {
                score += QWIRKLE_SCORE;
            }             
        }
    }

    return score;
}

int GameBoard::charToInt(char c) {
    int num = 0;

    for (int i = 0; i < MAX_DIM; ++i) {
        if (c == alphabets[i]) {
            num = i;
        }
    }
    return num;
}

void GameBoard::displayBoard() {
    char seperator = '|';

    std::cout << "   ";
    
    for (int i = 0; i < MAX_DIM; ++i) {
        if (i < 10) 
            std::cout << i << "  ";
        else 
            std::cout << i << " ";
    }

    std::cout << "\n" << "  --------------------"
              << "------------------------------"
              << "-----------------------------"
              << std::endl;

    for (int i = 0; i < MAX_DIM; ++i) {
        std::cout << alphabets[i] << " " << seperator;
        
        for (int col = 0; col < MAX_DIM; ++col) {
            if (board[i][col] != nullptr) {
                board[i][col]->printTile();
                std::cout << seperator;
            } else {
                std::cout << "  " << seperator; }
                    
        }
            
        std::cout << "\n";
    }      
}