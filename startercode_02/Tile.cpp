#include "Tile.h"
#include <iostream>

Tile::Tile(Colour c, Shape s){
    this->colour = c;
    this->shape = s;
}

Tile::~Tile(){
    
}

void Tile::setColour(Colour c){
    this->colour = c;
}

Colour Tile::getColour(){
    return this->colour;
}

void Tile::setShape(Shape s){
    this->shape = s;
}

Shape Tile::getShape(){
    return this->shape;
}