#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include "TileCodes.h"
#include "TileBag.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Player.h"

class GameEngine{
public:

    void newGame();
    void replaceTile(Colour colour, Shape shape, std::string player);
    void setPlayers(std::string player1, std::string player2);

private:
    Player* player1;
    Player* player2;
    TileBag* tileBag;
};
#endif