#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "TileCodes.h"
#include "Tile.h"
#include "LinkedList.h"

#define TILEBAG_MAX_SIZE    72

class TileBag {
public:

   TileBag();
   ~TileBag();

   //LinkedList* orderedTileBag;
   LinkedList* tileBag;
   int bagSize;

   LinkedList* createBag();
   void shuffleBag();

private:
    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
};
#endif // ASSIGN2_TILE_H