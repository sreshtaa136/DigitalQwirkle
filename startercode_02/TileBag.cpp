#include "TileBag.h"
#include <random>
#include <iostream>

//The order of the tile bag is determined when generating a new game. 
//When a tile is drawn from the bag, it is taken from the front of the linked list. 
//If tiles are added to the bag, they are added to the end of the linked list.
//You will need to devise your own algorithm to “shuffle” the bag of tiles to 
//create a “random” initial order.
//6 tiles are drawn from the tile bag and placed in the 1st player’s hand. 
//Then 6 tiles are drawn from the tile bag and placed in the 2nd player’s hand.


TileBag::TileBag(){

    tileBag = new LinkedList();
    shuffleBag();
}

TileBag::~TileBag(){
    delete tileBag;
    tileBag = nullptr;
}

LinkedList* TileBag::getTileBag(){
    return this->tileBag;
}

int TileBag::getBagSize(){
    return tileBag->getSize();
}

LinkedList* TileBag::createBag(){

    LinkedList* orderedTileBag = new LinkedList();
    char colour;
    int shape;
    int count = 0;

    while(count != 2){
      for(int i = 0; i <6; ++i){
            colour = colours[i];
            for(int j = 0; j <6; ++j){
                shape = shapes[j];
                Tile* tile = new Tile(colour, shape);
                orderedTileBag->addToEnd(tile);
            }
        }
      count++;
    }
    // tileBag->printList();
    // tileBag->printCount();
    return orderedTileBag;
    // delete orderedTileBag;
    // orderedTileBag = nullptr;
}

void TileBag::shuffleBag(){

    int min = 0;
    int max = TILEBAG_MAX_SIZE - 1;

    LinkedList* orderedTileBag = createBag();

    //bag with shuffled tiles
    //LinkedList* shuffledBag = new LinkedList();

    std::random_device engine;
	std::uniform_int_distribution<int> uniform_dist(min, max);
    
    while(tileBag->getSize() != orderedTileBag->getSize()){
     
        int randIndex1 = uniform_dist(engine);
       
        Tile* tile1 = new Tile(*orderedTileBag->getTileAtIndex(randIndex1));
        if(tileBag->tileCount(tile1) < 2){
            tileBag->addToEnd(tile1);
        }
        //delete tileBag;
        //tileBag = shuffledBag;
    }
}

Tile* TileBag::drawTile(){

    Tile* tile = new Tile(*tileBag->getTileAtIndex(0));
    tileBag->removeTile(tile->getColour(), tile->getShape());
    return tile;
}

LinkedList* TileBag::createHand(){

    LinkedList* playerHand = new LinkedList();

    while(playerHand->getSize() != 6){
        playerHand->addToEnd(drawTile());
    }

    //playerHand->printList();
    return playerHand;
}