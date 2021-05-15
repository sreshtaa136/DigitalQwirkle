#include "GameEngine.h"

#include <iostream>
#include <fstream>

void GameEngine::newGame(std::string player1, std::string player2){
    
    gameBoard = new GameBoard();
    tileBag = new TileBag();
    setPlayers(player1, player2);
    currentPlayer = this->player1;
    this->player1->setPlayerHand(tileBag->createHand());
    this->player2->setPlayerHand(tileBag->createHand());
    printGameState();
    std::cout << "TileBag size: " << tileBag->getBagSize() << std::endl;
}

//place tile, remove the tile from player's hand and update hand 
bool GameEngine::placeTile(char row, int col, Colour colour, Shape shape, std::string player){
    
    Tile* tileToPlace = new Tile(colour,shape);
    bool tilePlaced = false;

    if(player == player1->getName()){
        if(player1->getPlayerHand()->searchTile(tileToPlace) != -1){
            if(gameBoard->placeTile(row, col, tileToPlace)){
                player1->getPlayerHand()->removeTile(colour, shape);
                if(tileBag->getBagSize() != 0){
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    player1->getPlayerHand()->addToEnd(tile);
                    tilePlaced = true;
                }
            }
        }
    }else if(player == player2->getName()){
        if(player2->getPlayerHand()->searchTile(tileToPlace) != -1){
            if(gameBoard->placeTile(row, col, tileToPlace)){
                player2->getPlayerHand()->removeTile(colour, shape);
                if(tileBag->getBagSize() != 0){
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    player2->getPlayerHand()->addToEnd(tile);
                    tilePlaced = true;
                }
            }
        }
    }
    return tilePlaced;
}

bool GameEngine::replaceTile(Colour colour, Shape shape, std::string player){

    Tile* tileToReplace = new Tile(colour,shape);
    bool tileReplaced = false;

    if(player == player1->getName()){
        if(player1->getPlayerHand()->searchTile(tileToReplace) != -1){
            player1->getPlayerHand()->removeTile(colour, shape);
            tileBag->getTileBag()->addToEnd(tileToReplace);
            if(tileBag->getBagSize() != 0){
                Tile* tile = new Tile(*(tileBag->drawTile()));
                player1->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
            }
        }
    }else if(player == player2->getName()){
        if(player2->getPlayerHand()->searchTile(tileToReplace) != -1){
            player2->getPlayerHand()->removeTile(colour, shape);
            tileBag->getTileBag()->addToEnd(tileToReplace);
            if(tileBag->getBagSize() != 0){
                Tile* tile = new Tile(*(tileBag->drawTile()));
                player2->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
            }
        }
    }
    return tileReplaced;
}

void GameEngine::setPlayers(std::string player1, std::string player2){
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
}

Player* GameEngine::getPlayer1(){
    return this->player1;
}

Player* GameEngine::getPlayer2(){
    return this->player2;
}

Player* GameEngine::getCurrentPlayer(){
    return this->currentPlayer;
}

void GameEngine::setCurrentPlayer(std::string playerName){
    this->currentPlayer = getPlayer(playerName);
}

Player* GameEngine::getPlayer(std::string playerName){

    Player* player;
    if(player1->getName() == playerName){
        player = player1;
    }else{
        player = player2;
    }
    return player;
}

void GameEngine::printGameState(){

    //std::cout << " \n";
    std::cout << "Score for " << player1->getName() <<
    ": " << player1->getScore() << "\n";
    std::cout << "Score for " << player2->getName() <<
    ": " << player2->getScore() << "\n\n";
    gameBoard->displayBoard();
    std::cout << " \n";
}

bool GameEngine::saveGame(std::string fileName, std::string currentPlayer) {
    bool gameSaved = false;

    fileName += ".save";
    std::ofstream outFile;
    outFile.open(fileName);

    outFile << player1->getName() << std::endl;
    outFile << player1->getScore() << std::endl;
    outFile << player1->getPlayerHand()->toString() << std::endl;
    outFile << player2->getName() << std::endl;
    outFile << player2->getScore() << std::endl;
    outFile << player2->getPlayerHand()->toString() << std::endl;
    outFile << gameBoard->dimensionsToString() << std::endl;
    outFile << gameBoard->toString() << std::endl;
    outFile << tileBag->getTileBag()->toString() << std::endl;
    outFile << currentPlayer << std::endl;

    outFile.close();
}