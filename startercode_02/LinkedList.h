
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"
//#include "TileBag.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int getSize();
   void addToFront(Tile* tile);
   void addToEnd(Tile* tile);
   //Tile* getTileAtIndex(int index);
   void removeTile(Colour colour, Shape shape);
   //bool doesTileExist(Colour colour, Shape shape);
   int searchTile(Colour colour, Shape shape);
   int searchTile(Tile* tile);
   //Contract: Elements should exist in the list to be deleted.
   //void remove_front();
   //void remove_back();
   void clear();
   void printList();

   //void replaceTile(Tile* t1, Tile* t2);
   Tile* getTileAtIndex(int index);
   //void switchTiles(Tile* t1, Tile* t2);
   int tileCount(Tile* tile);

   //testing
   void printCount();

private:
   Node* head;
   int size;
};
#endif // ASSIGN2_LINKEDLIST_H