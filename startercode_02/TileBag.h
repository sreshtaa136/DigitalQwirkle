#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "TileCodes.h"
#include "Tile.h"
#include "LinkedList.h"

#define TILEBAG_MAX_SIZE    72

class TileBag {
public:
   // Default constructor
   TileBag();

   // Contructor for tilebag with no shuffling
   TileBag(bool shuffle);

   // Deconstructor
   ~TileBag();

   /*
    * Returns a tilebag containing 72 tiles.
    * Contains tiles in 6 colors and with 6 different shapes and 2 of each type.
    */
   LinkedList* createBag();

   // Shuffles the bag of tiles to create a “random” initial order
   void shuffleBag();

   // Creates and returns a player's hand from tilebag
   LinkedList* createHand();

   // Draws and returns a tile from the tilebag
   Tile* drawTile();

   // Returns the tilebag.
   LinkedList* getTileBag();

   // Returns the size of the tilebag.
   int getBagSize();

   // Helper: extracts the tilebag for loading a game.
   void loadBag(std::string tiles);

   // Sets the tilebag to the given tilebag
   void setTileBag(LinkedList* tileBag);

private:

    LinkedList* tileBag;
    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
};
#endif // ASSIGN2_TILE_H