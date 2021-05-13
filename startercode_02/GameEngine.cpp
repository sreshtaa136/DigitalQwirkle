#include "GameEngine.h"

#include <iostream>

void GameEngine::newGame(){
    tileBag = new TileBag();
    tileBag->shuffleBag();
}

//remove the tile from player's hand and update hand 
void GameEngine::replaceTile(Colour colour, Shape shape, std::string player){

    if(player == player1->getName()){
        player1->getPlayerHand()->removeTile(colour, shape);
        Tile* tile = new Tile(*(tileBag->drawTile()));
        player1->getPlayerHand()->addToEnd(tile);
    }else if(player == player2->getName()){
        player2->getPlayerHand()->removeTile(colour, shape);
        Tile* tile = new Tile(*(tileBag->drawTile()));
        player2->getPlayerHand()->addToEnd(tile);
    }
}

void GameEngine::setPlayers(std::string player1, std::string player2){
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
}