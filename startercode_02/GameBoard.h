#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include <vector>
#define MAX_DIM 26

class GameBoard {
public:

GameBoard();
~GameBoard();
int getSize();
void placeTile();
void displayBoard();


private:

char row;
int col;
std::vector<std::vector<Tile*>> board;

};

#endif