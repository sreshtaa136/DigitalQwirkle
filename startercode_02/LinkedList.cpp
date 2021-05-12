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

}

void LinkedList::addToEnd(Tile* tile){

}

Tile* LinkedList::getTileAtIndex(int index){

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