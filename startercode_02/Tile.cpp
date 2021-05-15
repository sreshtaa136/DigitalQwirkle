#include "Tile.h"
#include <iostream>

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

Tile::~Tile() {
    
}

//shallow copy
Tile::Tile(Tile& other) :
    colour(other.colour),
    shape(other.shape)
{}

void Tile::setColour(Colour colour) {
    this->colour = colour;
}

Colour Tile::getColour() {
    return this->colour;
}

void Tile::setShape(Shape shape) {
    this->shape = shape;
}

Shape Tile::getShape() {
    return this->shape;
}

void Tile::printTile() {
    std::cout << this->colour;
    std::cout << this->shape;
}

std::string Tile::toString() {
    std::string colourStr;
    colourStr = colour;
    std::string shapeStr = std::to_string(shape);
    return colourStr + shapeStr;
}