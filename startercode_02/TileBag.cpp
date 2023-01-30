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

    // the list of tiles in order
    LinkedList* orderedTileBag = new LinkedList();
    char colour;
    int shape;
    int count = 0;

    //Populate the ordered tilebag with 2 tiles of each type
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

    //testing
    
    // for (int i = 0; i <6; ++i) {
    //     colour = colours[i];
    //     for (int j = 0; j <6; ++j) {
    //         shape = shapes[j];
    //         Tile* tile = new Tile(colour, shape);
    //         orderedTileBag->addToEnd(tile);
    //     }
    // }
    
    return orderedTileBag;

    delete orderedTileBag;
    orderedTileBag = nullptr;
}

void TileBag::shuffleBag() {

    // populating the tilebag with shuffled tiles
    int min = 0;
    int max = 72-1;

    LinkedList* orderedTileBag = createBag();

    std::random_device engine;
	std::uniform_int_distribution<int> uniform_dist(min, max);
    
    while (tileBag->getSize() != orderedTileBag->getSize()) {

        int randIndex1 = uniform_dist(engine);
       
        Tile* tile1 = new Tile(*orderedTileBag->getTileAtIndex(randIndex1));
        if (tileBag->tileCount(tile1) < 2) {
            tileBag->addToEnd(tile1);
        }
    }

    //Testing
    //populating the tilebag with the same order of shuffling every time
    //int max = 36 - 1;

    // std::default_random_engine engine(28);
	// std::uniform_int_distribution<int> uniform_dist(min, max);
    
    // while(tileBag->getSize() != orderedTileBag->getSize()){
     
    //     int randIndex1 = uniform_dist(engine);
       
    //     Tile* tile1 = new Tile(*orderedTileBag->getTileAtIndex(randIndex1));
    //     if(tileBag->tileCount(tile1) < 1){
    //         tileBag->addToEnd(tile1);
    //     }
    // }
}

void TileBag::loadBag(std::string tiles) {

    // count of no.of commas
    int commaCount = 0;
    for(int i = 0; i< (int) tiles.size(); ++i) {
        if(tiles[i] == ','){
            ++commaCount;
        }
    }

    int tileCount = (tiles.size() - commaCount)/2;
    char tileArray[tileCount*2];
    int count = 0;

    // populating array with tiles without commas
    for (int i = 0; i< (int) tiles.size(); ++i) {
        if (tiles[i] != ',') {
            tileArray[count] = tiles[i];
            count++;
        }
    }

    // adding the tiles to the tilebag
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