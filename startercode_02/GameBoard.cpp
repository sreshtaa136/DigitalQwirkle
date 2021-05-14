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

    if (tilesOnBoard == 0) {
        valid = true;
    } 
    else { 
        //upper tile
        if (board[row-1][col] != nullptr && row > 0) {
            
            if(board[row-1][col]->getColour() == tile->getColour() ||
               board[row-1][col]->getShape() == tile->getShape()) {
                   board[row-1][col]->printTile();
                   upValid = true;
            } else { 
                   std::cout << "invalid" << std::endl;}
        } else { 
            std::cout << "null/out of boundS" << std::endl;}

        //down tile
        if (board[row+1][col] != nullptr && row < MAX_DIM) {
            if(board[row+1][col]->getColour() == tile->getColour() ||
               board[row+1][col]->getShape() == tile->getShape()) {
                   downValid = true;
            }
        } else { 
            std::cout << "null/out of boundS" << std::endl;}

    
        //left tile
        if (board[row][col-1] != nullptr && col > 0) {
            if (board[row][col-1]->getColour() == tile->getColour() ||
                board[row][col-1]->getShape() == tile->getShape()) {
                    leftValid = true;
            }
        } else { 
            std::cout << "null/out of boundS" << std::endl;}


        // //right valid
        // if (board[row][col+1] != nullptr && col < MAX_DIM) {
        //     if(board[row][col+1]->getColour() == tile->getColour() ||
        //        board[row][col+1]->getShape() == tile->getShape()) {
        //            rightValid = true;
        //     }
        // } else { 
        //     std::cout << "null/out of boundS" << std::endl;}

        
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






