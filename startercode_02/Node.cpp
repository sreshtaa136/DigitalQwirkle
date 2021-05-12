#include "Node.h"
#include <stdexcept>
#include <iostream>

Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::~Node(){
   delete tile;
   tile = nullptr;
   next = nullptr;
}

Node::Node(Node& other)
{
   tile = new Tile(*other.tile);
   next = new Node(*other.next);
}

void Node::setTile(Tile* tile){
   this->tile = tile;
}

Tile* Node::getTile(){
   return this->tile;
}

void Node::setNext(Node* node){
   this->next = node;
}

Node* Node::getNext(){
   return this->next;
}