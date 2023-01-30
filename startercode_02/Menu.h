#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"
#include "LinkedList.h"
#include "TileBag.h"
#include "Player.h"
#include "GameBoard.h"
#include "GameEngine.h"

#define START     "0"
#define NEWGAME   "1"
#define LOADGAME  "2"
#define CREDITS   "3"
#define QUIT      "4"


class Menu{
public:

    Menu();
    ~Menu();

    // takes input from the user and calls the respective 
    // functions depending on their choice
    void takeInput();

    // checks if entered player names are valid
    bool validatePlayerName (std::string name);

    // checks if the conditions for ending a game are satisfied
    bool endGame(bool threePlayer);

    // verifies if a given command is valid
    bool validateCommand(std::string command);

    //displays menu and it's options
    void displayMenu(std::string choice);

    //validates user choice
    // mode = true when user enters game mode
    bool validateChoice(std::string choice, bool mode);

    // loads a game from the given file and returns false if file is invalid
    // or the game fails to load
    bool validateLoadGame(std::string fileName);

    bool loadGame();

    bool newGame(bool load, bool threePlayer);


private:

    char alphabets[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    char lowerAlphabets[26] = {'a',	'b', 'c', 'd', 'e',	'f', 'g', 'h', 'i',	'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',	'x', 'y', 'z'};

    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    GameEngine* engine;

};
#endif //ASSIGN2_MENU_H