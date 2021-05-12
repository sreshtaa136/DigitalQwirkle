#include "LinkedList.h"

#include <stdexcept>
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
   delete head;
   head = nullptr;
}

int LinkedList::getSize(){
   return this->size;
}

void LinkedList::addToFront(Tile* tile){
   if(size == 0)
   {
      Node* node = new Node(tile, nullptr);
      this->head = node;

   }else{
      Node* node = new Node(tile, head);
      this->head = node;
   }
   size++;
}

void LinkedList::addToEnd(Tile* tile){
   //while()
   
}

Tile* LinkedList::getTileAtIndex(int index){
   return nullptr;
}

void LinkedList::remove(int index){

}

//Contract: Elements should exist in the list to be deleted.
void LinkedList::remove_front(){

}

void LinkedList::remove_back(){

}

void LinkedList::clear(){

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