#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"
#include <string>
//#include "TileBag.h"

class LinkedList {
public:
   
   // Constructor/Deconstructor
   LinkedList();
   ~LinkedList();

   // Returns the size of the linked list.
   int getSize();

   // Adds the given tile to the front of the list.
   void addToFront(Tile* tile);

   // Adds the given tile to the back of the list.
   void addToEnd(Tile* tile);

   // Removes the given tile from the list.
   void removeTile(Colour colour, Shape shape);

   // Returns the index of first instance of a tile using shape and colour
   // Returns -1 if tile not found.
   int searchTile(Colour colour, Shape shape);

   // Returns the index of first instance of a tile using shape and colour
   // Returns -1 if tile not found.
   int searchTile(Tile* tile);

   // Removes all the tiles from the list.
   void clear();

   // Prints the list.
   void printList();

   // Returns the list as a string of tiles.
   std::string toString();

   // Returns a tile at given index.
   Tile* getTileAtIndex(int index);

   // Helper: returns the number of tiles in the list.
   int tileCount(Tile* tile);

private:
   Node* head;
   int size;
};
#endif // ASSIGN2_LINKEDLIST_H