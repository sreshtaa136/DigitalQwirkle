#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"
#include "Tile.h"

class Player {
public:

    // Constructor/deconstructor
    Player(std::string name);
    ~Player();
    
    // Returns the player's name 
    std::string getName();

    // Returns the player's score
    int getScore();

    // Returns the player's hand
    LinkedList* getPlayerHand();

    // Sets the player's score to given score
    void setScore(int score);

    // Sets the player's hand to given hand
    void setPlayerHand(LinkedList* hand);

    // Prints the tiles in a player's hand as 
    void printPlayerHand();

    // Adds the new score to player's previous score
    void incrementScore(int newScore);

    // Set player name to given name
    void setName(std::string name);
  
private:

    // Name and score of a player
    std::string name;
    int score;

    // playerHand is a linked list of all tiles a player currently has
    LinkedList* playerHand;
};

#endif //ASSIGN2_PLAYER_H