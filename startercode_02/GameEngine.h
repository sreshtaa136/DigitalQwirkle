#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include "TileCodes.h"
#include "TileBag.h"
#include "Tile.h"
#include "LinkedList.h"
#include "Player.h"
#include "GameBoard.h"

#define MAX_DIM 26

class GameEngine{
public:
    

    GameEngine();
    ~GameEngine();

    /*
    * Initializes a new game.
    * 1. Create a new board and tilebag.
    * 2. Set up two players.
    * 3. Print the game state.
    */
    void newGame(std::string player1, std::string player2);

    /*
    * Returns true if the tile has been placed.
    * A tile is placed only if the tile is in the player's hand.
    * Updates the player's hand back to 6 tiles if the tilebag is not empty.
    */
    bool placeTile(char row, int col, Colour colour, Shape shape, std::string player);

    // Sets players for a game.
    void setPlayers(std::string player1, std::string player2);

    // Prints the game status to the console.
    void printGameState();

    /*
    * Returns true if the tile has been replaced.
    * A tile is replaced only if the tile is in the player's hand.
    * Replaces and removes the tile from hand and places it back to the tilebag.
    */
    bool replaceTile(Colour colour, Shape shape, std::string player);

    // Saves the current game details with the given filename.
    void saveGame(std::string fileName);

    // Loads a saved game from the given file, and returns false if wrongly formatted
    bool loadGame(std::string fileName);

    // Getters for players in the game.
    Player* getPlayer1();
    Player* getPlayer2();

    // Getter and setter for current player.
    Player* getCurrentPlayer();
    void setCurrentPlayer(std::string playerName);

    // Get player using player name.
    Player* getPlayer(std::string playerName);

    // Extract the given player's hand 
    void loadHand(std::string hand, std::string name);

    // Set the tilebag.
    void setTileBag(TileBag* tileBag);

    // Validators for the format of file to be loaded
    bool verifyName(std::string s);
    bool verifyListString(std::string s);
    bool verifyBoardShapeString(std::string s);
    bool verifyBoardString(std::string s);
    bool verifyBoardSize(std::string s);

    TileBag* tileBag;
    GameBoard* gameBoard;

private:

    Player* player1;
    Player* player2;
    Player* currentPlayer;
    
};
#endif