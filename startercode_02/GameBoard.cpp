#include "GameBoard.h"
#include <iostream>

GameBoard::GameBoard() {
    for (int row = 0; row < MAX_DIM; ++row) {

        std::vector<Tile*> temp;
        for (int col = 0; col < MAX_DIM; ++col) {
            temp.push_back(nullptr);
	    }
        board.push_back(temp);
	}

    this->row = 0;
    this->col = 0;
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
    //check if tile space is empty and move is valid according to qwirkle rules
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

            // Check if either the colour or shape are same for adjacent tile
            if (board[row-1][col]->getColour() == tile->getColour() ||
                board[row-1][col]->getShape() == tile->getShape()) {
                    upValid = true;
            } 

            // Check if it has any duplicate tile above it
            if (checkDuplicates(row, col, "above")) {
                    upValid = false;
            } 
        }
        
        if (hasTileBelow(row, col)) {

            ++neighbour;

            // Check if either the colour or shape are same for adjacent tile
            if (board[row+1][col]->getColour() == tile->getColour() ||
                board[row+1][col]->getShape() == tile->getShape()) {
                    downValid = true;
            }

            // Check if it has any duplicate tile below it
            if (checkDuplicates(row, col, "down")) {
                    downValid = false;
            } 
        }
        
        if (hasTileAtLeft(row, col)) {

            ++neighbour;

            // Check if either the colour or shape are same for adjacent tile
            if (board[row][col-1]->getColour() == tile->getColour() ||
                board[row][col-1]->getShape() == tile->getShape()) {
                    leftValid = true;
            }

            // Check if it has any duplicate tile to the left 
            if (checkDuplicates(row, col, "left")) {
                    leftValid = false;
            } 
        }

        if (hasTileAtRight(row, col)) {

            ++neighbour;

            // Check if either the colour or shape are same for adjacent tile
            if (board[row][col+1]->getColour() == tile->getColour() ||
                board[row][col+1]->getShape() == tile->getShape()) {
                    rightValid = true;
            }

            // Check if it has any duplicate tile to the right
            if (checkDuplicates(row, col, "right")) {
                    rightValid = false;
            } 
           
        }

        // there must be at least one adjacent tile for move to be valid
        // should not have more than two adjacent tiles
        if ((upValid || downValid || rightValid || leftValid) && neighbour <= 2) {
            valid = true;
        }
    }
    

    return valid;
}

bool GameBoard::checkDuplicates(int row, int col, std::string direction) {
    bool duplicateFound = false;

    if (direction.compare("right") == 0) {
        while (hasTileAtRight(row, col)) {
             if (board[row][col+1]->getColour() == board[row][col]->getColour() &&
                 board[row][col+1]->getShape() == board[row][col]->getShape()) {
                     duplicateFound = true;
            }

        ++col;
        }
    } else if (direction.compare("left") == 0) {
        while (hasTileAtLeft(row, col)) {
             if (board[row][col-1]->getColour() == board[row][col]->getColour() &&
                 board[row][col-1]->getShape() == board[row][col]->getShape()) {
                     duplicateFound = true;
            }

        --col;
        }
    } else if (direction.compare("above") == 0) {
        while (hasTileAtRight(row, col)) {
             if (board[row-1][col]->getColour() == board[row][col]->getColour() &&
                 board[row-1][col]->getShape() == board[row][col]->getShape()) {
                     duplicateFound = true;
            }

        --row;
        }
    } else if (direction.compare("below") == 0) {
        while (hasTileAtRight(row, col)) {
             if (board[row+1][col]->getColour() == board[row][col]->getColour() &&
                 board[row+1][col]->getShape() == board[row][col]->getShape()) {
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

    if (totalTilesInRow(row, col) > QWIRKLE_SCORE || 
        totalTilesInCol(row, col) > QWIRKLE_SCORE) {
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

    if(tilesOnBoard == 0) {
        score = ONE_TILE_SCORE;
    } else {
        if (!checkLine(rowIdx, col) && !isQwirkle(rowIdx, col)) {
            rowScore = totalTilesInRow(rowIdx, col);
            colScore = totalTilesInCol(rowIdx, col);

            if (rowScore == ONE_TILE_SCORE || colScore == ONE_TILE_SCORE) {
                score = rowScore + colScore - 1;
            }
            else {
                score = rowScore + colScore;
            }
            
        }
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






