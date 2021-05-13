#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>
#include "LinkedList.h"
#include "Tile.h"

class Player {
public:

    // constructor/deconstructor
    Player(std::string name);
    ~Player();
    
    // get the player's name, score and hand
    std::string getName();
    int getScore();
    LinkedList* getPlayerHand();

    // set the player's score and hand
    void setScore(int score);
    void setPlayerHand(LinkedList* hand);

    // add up the player's score
    void incrementScore(int newScore);

    // player action : replace a tile in playerHand
    void replaceTile(Tile* tileToReplace, Tile* newTile);
  
private:

    // name and score of a player
    std::string name;
    int score;

    // playerHand is an ordered linked list of all tiles a player currently has
    LinkedList* playerHand;

};

#endif