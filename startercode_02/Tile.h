
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:

   // Constructor/Desctructor
   Tile(Colour colour, Shape shape);
   ~Tile();

   //copy constructor
   Tile(Tile& other);

   void setColour(Colour colour);
   Colour getColour();

   void setShape(Shape shape);
   Shape getShape();

   void printTile();
   std::string toString();

   Colour colour;
   Shape  shape;
};
#endif // ASSIGN2_TILE_H