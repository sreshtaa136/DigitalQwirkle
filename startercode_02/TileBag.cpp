#include "TileBag.h"
#include <random>
#include <iostream>

TileBag::TileBag() {
    tileBag = new LinkedList();
    shuffleBag();
}

TileBag::TileBag(bool shuffle) {

    tileBag = new LinkedList();
}

TileBag::~TileBag() {
    delete tileBag;
    tileBag = nullptr;
}

LinkedList* TileBag::getTileBag() {
    return this->tileBag;
}

int TileBag::getBagSize() {
    return tileBag->getSize();
}

void TileBag::setTileBag(LinkedList* tileBag) {
    this->tileBag = tileBag;
}

LinkedList* TileBag::createBag() {
    LinkedList* orderedTileBag = new LinkedList();
    char colour;
    int shape;
    int count = 0;

    // Populate the tilebag with 2 of each type
    while (count != 2) {
      for (int i = 0; i <6; ++i) {
            colour = colours[i];
            for (int j = 0; j <6; ++j) {
                shape = shapes[j];
                Tile* tile = new Tile(colour, shape);
                orderedTileBag->addToEnd(tile);
            }
        }
      count++;
    }
    
    return orderedTileBag;
    // delete orderedTileBag;
    // orderedTileBag = nullptr;
}

void TileBag::shuffleBag() {
    int min = 0;
    int max = TILEBAG_MAX_SIZE - 1;

    LinkedList* orderedTileBag = createBag();

    std::random_device engine;
	std::uniform_int_distribution<int> uniform_dist(min, max);
    
    while (tileBag->getSize() != orderedTileBag->getSize()) {
        int randIndex1 = uniform_dist(engine);
       
        Tile* tile1 = new Tile(*orderedTileBag->getTileAtIndex(randIndex1));
        if (tileBag->tileCount(tile1) < 2) {
            tileBag->addToEnd(tile1);
        }
        //delete tileBag;
        //tileBag = shuffledBag;
    }

    //Testing
    // std::default_random_engine engine(28);
	// std::uniform_int_distribution<int> uniform_dist(min, max);
    // while(tileBag->getSize() != orderedTileBag->getSize()){
     
    //     int randIndex1 = uniform_dist(engine);
       
    //     Tile* tile1 = new Tile(*orderedTileBag->getTileAtIndex(randIndex1));
    //     if(tileBag->tileCount(tile1) < 2){
    //         tileBag->addToEnd(tile1);
    //     }
    //     //delete tileBag;
    //     //tileBag = shuffledBag;
    // }

}

void TileBag::loadBag(std::string tiles) {

    int commaCount = 0;
    for(int i = 0; i< (int) tiles.size(); ++i) {
        if(tiles[i] == ','){
            ++commaCount;
        }
    }

    int tileCount = (tiles.size() - commaCount)/2;
    char tileArray[tileCount*2];
    int count = 0;

    for (int i = 0; i< (int) tiles.size(); ++i) {
        if (tiles[i] != ',') {
            tileArray[count] = tiles[i];
            count++;
        }
    }

    count = 0;
    for (int i = 0; i<tileCount; ++i) {
        char colour = tileArray[count];
        int shape = tileArray[count + 1] - '0';
        Tile* tile = new Tile(colour, shape);
        tileBag->addToEnd(tile);
        count = count + 2;
    }
}

Tile* TileBag::drawTile() {
    Tile* tile = new Tile(*tileBag->getTileAtIndex(0));
    tileBag->removeTile(tile->getColour(), tile->getShape());
    return tile;
}

LinkedList* TileBag::createHand() {
    LinkedList* playerHand = new LinkedList();

    while (playerHand->getSize() != 6) {
        playerHand->addToEnd(drawTile());
    }
    return playerHand;
}

