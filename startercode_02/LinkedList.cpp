#include "LinkedList.h"

#include <stdexcept>
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
   clear();
}

int LinkedList::getSize(){
   return this->size;
}

void LinkedList::addToFront(Tile* tile){

   if(size == 0){
      Node* node = new Node(tile, nullptr);
      this->head = node;
   }else{
      Node* node = new Node(tile, head);
      this->head = node;
   }
   size++;
}

void LinkedList::addToEnd(Tile* tile){
   
   Node* node = new Node(tile, nullptr);

   if(size == 0){
      this->head = node;
      size++;
   }else{
      
      Node* prevNode = head;
      while(prevNode->getNext() != nullptr){
         prevNode = prevNode->getNext();
      }
      prevNode->setNext(node);
      size++;
   }
}

// returns -1 if tile does not exist
// returns first instance of the tile
int LinkedList::searchTile(Colour colour, Shape shape){
   
   int index = -1;
   Node* currNode = head;

   for (int i = 0; i < size; ++i) {
      if(currNode->getTile()->getColour() == colour &&
      currNode->getTile()->getShape() == shape &&
      index == -1){
         index = i;
      }
      currNode = currNode->getNext();
   }
   return index;
}

// returns -1 if tile does not exist
int LinkedList::searchTile(Tile* tile){
   
   Colour colour = tile->getColour();
   Shape shape = tile->getShape();
   int index = -1;

   Node* currNode = head;
   for (int i = 0; i < size; ++i) {
      if(currNode->getTile()->getColour() == colour &&
      currNode->getTile()->getShape() == shape){
         index = i;
      }
      currNode = currNode->getNext();
   }
   return index;
}

void LinkedList::removeTile(Colour colour, Shape shape){
   
   if(searchTile(colour, shape) != -1){
      int index = searchTile(colour, shape);
      Node* prevNode = head;
      Node* currNode = head->getNext();
      if(index == 0){
         head = head->getNext();
         delete prevNode;
         prevNode = nullptr;
         size--;
      }else{
         for(int i = 0; i < index-1; ++i){
         prevNode = prevNode->getNext();
         currNode = currNode->getNext();
         }
         prevNode->setNext(currNode->getNext());
         delete currNode;
         currNode = nullptr;
         size--;
      }
   }
}

Tile* LinkedList::getTileAtIndex(int index){
   Tile* tile = nullptr;
   if (index < size) {
      if (index == 0) {
         tile = head->getTile();
      }else {
         Node* currNode = head;
         for (int i = 0; i < index; ++i) {
            currNode = currNode->getNext();
         }
         tile = currNode->getTile();
      }
   }
   return tile;
}

//replaces t1 with t2
// void LinkedList::replaceTile(Tile* t1, Tile* t2){

//    int t1_index = searchTile(t1->getColour(), t1->getShape());
//    Tile* tile;

//    if(t1_index != -1){
//       if (t1_index == 0) {
//          tile = head->getTile();
//          tile->setColour(t2->getColour());
//          tile->setShape(t2->getShape());
//       }else {
//          Node* currNode = head;
//          for (int i = 0; i < t1_index; ++i) {
//             currNode = currNode->getNext();
//          }
//          tile = currNode->getTile();
//          tile->setColour(t2->getColour());
//          tile->setShape(t2->getShape());
//       }
//    }
// }

// void LinkedList::switchTiles(Tile* t1, Tile* t2){
   
//    Tile* temp = new Tile(*t1);
//    replaceTile(t1, t2);
//    replaceTile(t2, temp);
// }

int LinkedList::tileCount(Tile* tile){

   Colour colour = tile->getColour();
   Shape shape = tile->getShape();
   int count = 0;

   Node* currNode = head;
   for (int i = 0; i < size; ++i) {
      if(currNode->getTile()->getColour() == colour &&
      currNode->getTile()->getShape() == shape){
         count++;
      }
      currNode = currNode->getNext();
   }
   return count;
}

void LinkedList::clear(){

   Node* currNode = head;
   while(currNode != nullptr){
      Node* nextNode = currNode->getNext();
      delete currNode;
      currNode = nextNode;
   }
}

void LinkedList::printList(){
   Node* currNode = head;
   while(currNode != nullptr){
      currNode->getTile()-> printTile();
      currNode = currNode->getNext();
      if(currNode != nullptr){
         std::cout << ",";
      }
   }
   std::cout << "\n";
}

//TESTING
void LinkedList::printCount(){
   Node* currNode = head;
   while(currNode != nullptr){
      std::cout << tileCount(currNode->getTile());
      currNode = currNode->getNext();
      if(currNode != nullptr){
         std::cout << ",";
      }
   }
   std::cout << "\n";
}