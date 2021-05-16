
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

   // Copy constructor : returns a shallow copy
   Tile(Tile& other);

   // Set the colour of the tile to given colour
   void setColour(Colour colour);

   // Returns the colour of the tile
   Colour getColour();

   // Set the shape of the tile to given shape
   void setShape(Shape shape);

   // Returns the shape of the tile
   Shape getShape();

   // Prints a tile.
   void printTile();

   // Returns tile as a string.
   std::string toString();

private:
   Colour colour;
   Shape  shape;
};
#endif // ASSIGN2_TILE_H