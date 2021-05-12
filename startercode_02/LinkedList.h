
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include "Tile.h"


class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int getSize();
   void addToFront(Tile* tile);
   void addToEnd(Tile* tile);
   Tile* getTileAtIndex(int index);
   void remove(int index);
   //Contract: Elements should exist in the list to be deleted.
   void remove_front();
   void remove_back();
   void clear();
   void printList();

private:
   Node* head;
   int size;
};
#endif // ASSIGN2_LINKEDLIST_H