#include "GameBoard.h"
#include <string>
#include <iostream>

GameBoard::GameBoard() {
    std::vector<Tile*> temp;

    for (int col = 0; col < MAX_DIM; ++col) {
        temp.push_back(nullptr);
	}

    for (int row = 0; row < MAX_DIM; ++row) {
        board.push_back(temp);

	}

    this->row = 0;
    this->col = 0;
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
        if (rowIdx == alphabets[i]) {
            rowIdx = i;
        }
    }

    board[rowIdx][col] = tile;
    return false;
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






