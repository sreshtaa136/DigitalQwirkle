#include "Tile.h"
#include <iostream>

Tile::Tile(Colour colour, Shape shape){
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile(){
    
}

//shallow copy
Tile::Tile(Tile& other) :
    colour(other.colour),
    shape(other.shape)
{}

void Tile::setColour(Colour colour){
    this->colour = colour;
}

Colour Tile::getColour(){
    return this->colour;
}

void Tile::setShape(Shape shape){
    this->shape = shape;
}

Shape Tile::getShape(){
    return this->shape;
}