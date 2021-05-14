#include "GameBoard.h"
#include <string>
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
    int rowIdx = 0;

    for (int i = 0; i < MAX_DIM; ++i) {
        if (row == alphabets[i]) {
            rowIdx = i;
        }
    }

    //check if tile space is empty
    if (isEmptySpace(rowIdx, col) && isValidMove(rowIdx, col, tile)) 
    {
        board[rowIdx][col] = tile;
        tilesOnBoard++;
    }
    else { std::cout << "error" << std::endl; }
    
    return false;
}

bool GameBoard::isEmptySpace(int row, int col) {
    bool empty = false;

    if(board[row][col] == nullptr) {
        empty = true;
    }
    
    return empty;
}

bool GameBoard::isValidMove(int row, int col, Tile* tile) {

    bool valid = false;
    bool rightValid = false;
    bool leftValid = false;
    bool upValid = false;
    bool downValid = false;

    // if it's the first tile
    if (tilesOnBoard == 0) {
        valid = true;

    } else { 

        // Check if row is in bounds
        if (row > 0) {

            // Check if there is a tile above
            if (board[row-1][col] != nullptr) {

                // Check if either the colour or shape are same
                if (board[row-1][col]->getColour() == tile->getColour() ||
                    board[row-1][col]->getShape() == tile->getShape()) {
                        upValid = true;
                } 

                // Check if it is a duplicate tile
                if (board[row-1][col]->getColour() == tile->getColour() &&
                    board[row-1][col]->getShape() == tile->getShape()) {
                        upValid = false;
                } 
            }
        }
        
        // Check if row is in bounds
        if (row < MAX_DIM-1) {

            // Check if there is a tile below
            if (board[row+1][col] != nullptr) {

                // Check if either the colour or shape are same
                if (board[row+1][col]->getColour() == tile->getColour() ||
                    board[row+1][col]->getShape() == tile->getShape()) {
                       downValid = true;
                }

                // Check if it is a duplicate tile
                if (board[row+1][col]->getColour() == tile->getColour() &&
                    board[row+1][col]->getShape() == tile->getShape()) {
                        downValid = false;
                } 
            } 
        }
        
        // Check if column is in bounds
        if (col > 0) {

            // Check if there is a tile to the left
            if (board[row][col-1] != nullptr) {

                // Check if either the colour or shape are same
                if (board[row][col-1]->getColour() == tile->getColour() ||
                    board[row][col-1]->getShape() == tile->getShape()) {
                        leftValid = true;
                }

                // Check if it is a duplicate tile
                if (board[row][col-1]->getColour() == tile->getColour() &&
                    board[row][col-1]->getShape() == tile->getShape()) {
                        leftValid = false;
                } 
            } 
        }

        // Check if column is in bounds
        if (col < MAX_DIM-1) {

            // Check if there is a tile to the right
            if (board[row][col+1] != nullptr) {

                // Check if either the colour or shape are same
                if (board[row][col+1]->getColour() == tile->getColour() ||
                    board[row][col+1]->getShape() == tile->getShape()) {
                        rightValid = true;
                }

                // Check if it is a duplicate tile
                if (board[row][col+1]->getColour() == tile->getColour() &&
                    board[row][col+1]->getShape() == tile->getShape()) {
                        rightValid = false;
                } 
            } 
        }

        // there must be at least one adjacent tile for move to be valid
        valid = upValid || downValid || rightValid || leftValid;
     
    }

    return valid;
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






