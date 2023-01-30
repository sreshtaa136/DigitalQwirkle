#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

GameEngine::GameEngine() {

    gameBoard = new GameBoard();
    tileBag = new TileBag();
    gameBoard = new GameBoard();

}

GameEngine::~GameEngine() {
    
    //deleting the players in the players vector
    for(int i = 0; i < players.size(); ++i){
        if(players[i] != nullptr){
            delete players[i];
            players[i] = nullptr;
        }      
    }

    delete tileBag;
    delete gameBoard;

    tileBag = nullptr;
    gameBoard = nullptr;
}

void GameEngine::newGame(std::string player1, std::string player2) {
    
    
    tileBag = new TileBag();
    setPlayers(player1, player2);

    currentPlayer = players[0]->getName();
    players[0]->setPlayerHand(tileBag->createHand());
    players[1]->setPlayerHand(tileBag->createHand());
    printGameState();
    
}

void GameEngine::newGame(std::string player1, std::string player2, std::string player3){
    
    tileBag = new TileBag();

    setPlayers(player1, player2, player3);

    currentPlayer = players[0]->getName();
    players[0]->setPlayerHand(tileBag->createHand());
    players[1]->setPlayerHand(tileBag->createHand());
    players[2]->setPlayerHand(tileBag->createHand());
    printGameState();
}

bool GameEngine::placeTile(char row, int col, Colour colour, Shape shape, 
                           std::string player) {

    Tile* tileToPlace = new Tile(colour,shape);
    bool tilePlaced = false;

    if (player == player1) {

        // Check if tile is in player hand
        if (players[0]->getPlayerHand()->searchTile(tileToPlace) != -1) {

            // Remove the tile from player's hand if placed
            if (gameBoard->placeTile(row, col, tileToPlace)) {
                players[0]->getPlayerHand()->removeTile(colour, shape);

                // When tilebag is not empty, draw tile to player's hand from the bag
                if (tileBag->getBagSize() != 0) {
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    players[0]->getPlayerHand()->addToEnd(tile);
                }
                tilePlaced = true;
            }

        } else {
            std::cerr << "INVALID TILE: cannot place a tile which is not in your hand" 
                      << std::endl;
        }

    } else if (player == player2) {

        // Check if tile is in player hand
        if (players[1]->getPlayerHand()->searchTile(tileToPlace) != -1) {

            // Remove the tile from player's hand if placed
            if (gameBoard->placeTile(row, col, tileToPlace)) {
                players[1]->getPlayerHand()->removeTile(colour, shape);

                // When tilebag is not empty, draw tile to player's hand from the bag
                if (tileBag->getBagSize() != 0) {
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    players[1]->getPlayerHand()->addToEnd(tile);
                }
                tilePlaced = true;
            }

        } else {
            std::cerr << "INVALID TILE: cannot place a tile which is not in your hand" 
                      << std::endl;
        }

    } else if (player == player3) {

        // Check if tile is in player hand
        if (players[2]->getPlayerHand()->searchTile(tileToPlace) != -1) {

            // Remove the tile from player's hand if placed
            if (gameBoard->placeTile(row, col, tileToPlace)) {
                players[2]->getPlayerHand()->removeTile(colour, shape);

                // When tilebag is not empty, draw tile to player's hand from the bag
                if (tileBag->getBagSize() != 0) {
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    players[2]->getPlayerHand()->addToEnd(tile);
                }
                tilePlaced = true;
            }

        } else {
            std::cerr << "INVALID TILE: cannot place a tile which is not in your hand" 
                      << std::endl;
        }
    }
    return tilePlaced;
}

bool GameEngine::replaceTile(Colour colour, Shape shape, std::string player) {

    Tile* tileToReplace = new Tile(colour,shape);
    bool tileReplaced = false;

    if (player == player1) {

        // Check if tile is in player hand
        if (players[0]->getPlayerHand()->searchTile(tileToReplace) != -1) {

            // When tilebag is not empty, replace current tile
            if (tileBag->getBagSize() != 0) {

                // Remove the tile from player's hand and place it back in the tilebag
                players[0]->getPlayerHand()->removeTile(colour, shape);
                tileBag->getTileBag()->addToEnd(tileToReplace);

                Tile* tile = new Tile(*(tileBag->drawTile()));
                players[0]->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
            } else {
                std::cerr << "INVALID MOVE: cannot replace tile because tile bag is empty" 
                          << std::endl;
            }

        } else {
            std::cerr << "INVALID TILE: cannot replace a tile which is not in your hand" 
                      << std::endl;
        }

    } else if (player == player2) {

        // Check if tile is in player hand
        if (players[1]->getPlayerHand()->searchTile(tileToReplace) != -1) {

            // When tilebag is not empty, replace current tile
            if (tileBag->getBagSize() != 0) {

                // Remove the tile from player's hand and place it back in the tilebag
                players[1]->getPlayerHand()->removeTile(colour, shape);
                tileBag->getTileBag()->addToEnd(tileToReplace);

                Tile* tile = new Tile(*(tileBag->drawTile()));
                players[1]->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
                
            } else {
                std::cerr << "INVALID MOVE: cannot replace tile because tile bag is empty" 
                          << std::endl;
            }

        } else {
            std::cerr << "INVALID TILE: cannot replace a tile which is not in your hand" 
                      << std::endl;
        }

    } else if (player == player3) {

        // Check if tile is in player hand
        if (players[2]->getPlayerHand()->searchTile(tileToReplace) != -1) {

            // When tilebag is not empty, replace current tile
            if (tileBag->getBagSize() != 0) {

                // Remove the tile from player's hand and place it back in the tilebag
                players[2]->getPlayerHand()->removeTile(colour, shape);
                tileBag->getTileBag()->addToEnd(tileToReplace);

                Tile* tile = new Tile(*(tileBag->drawTile()));
                players[2]->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
                
            } else {
                std::cerr << "INVALID MOVE: cannot replace tile because tile bag is empty" 
                          << std::endl;
            }

        } else {
            std::cerr << "INVALID TILE: cannot replace a tile which is not in your hand" 
                      << std::endl;
        }
    }
    return tileReplaced;
}

void GameEngine::setPlayers(std::string player1, std::string player2){

    Player* player_1 = new Player(player1);
    Player* player_2 = new Player(player2);
    players.push_back(player_1);
    players.push_back(player_2);

    //setting player names
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = "";

}

void GameEngine::setPlayers(std::string player1, std::string player2, std::string player3){

    Player* player_1 = new Player(player1);
    Player* player_2 = new Player(player2);
    Player* player_3 = new Player(player3);
    players.push_back(player_1);
    players.push_back(player_2);
    players.push_back(player_3);

    //setting player names
    this->player1 = player1;
    this->player2 = player2;
    this->player3 = player3;
}

Player* GameEngine::getPlayer1(){
    return players[0];
}

Player* GameEngine::getPlayer2(){
    return players[1];
}

Player* GameEngine::getPlayer3(){
    return players[2];
}

std::string GameEngine::getPlayer1Name(){
    return player1;
}

std::string GameEngine::getPlayer2Name(){
    return player2;
}

std::string GameEngine::getPlayer3Name(){
    return player3;
}

std::string GameEngine::getCurrentPlayer(){
    return this->currentPlayer;
}

void GameEngine::setCurrentPlayer(std::string playerName){
    this->currentPlayer = playerName;
}

Player* GameEngine::getPlayer(std::string playerName){

    Player* player;

    if (player1 == playerName) {
        player = players[0];
    } else if (player2 == playerName){
        player = players[1];
    } else {
        player = players[2];
    }
    return player;
}

void GameEngine::printGameState(){

    std::cout << "Score for " << player1 <<
    ": " << players[0]->getScore() << "\n";
    std::cout << "Score for " << player2 <<
    ": " << players[1]->getScore() << "\n";

    // checking if there is a third player
    if (player3 != "") {
        std::cout << "Score for " << player3 <<
        ": " << players[2]->getScore() << "\n\n";
    } else {
        std::cout << "\n";
    }

    gameBoard->displayBoard();
    std::cout << " \n";
}

void GameEngine::loadHand(std::string hand, std::string name){

    LinkedList* playerHand = new LinkedList();

    // Count the number of commas.
    int commaCount = 0;
    for (int i = 0; i< (int) hand.size(); ++i) {
        if (hand[i] == ',') {
            ++commaCount;
        }
    }

    int tileCount = (hand.size() - commaCount)/2;
    char tileArray[tileCount*2];
    int count = 0;

    // Add all the tiles to a char array
    for (int i = 0; i< (int) hand.size(); ++i) {
        if (hand[i] != ',') {
            tileArray[count] = hand[i];
            count++;
        }
    }

    count = 0;

    // Populate the player's hand with thier tiles
    for (int i = 0; i<tileCount; ++i) {
        char colour = tileArray[count];
        int shape = tileArray[count + 1] - '0';
        Tile* tile = new Tile(colour, shape);
        playerHand->addToEnd(tile);
        count = count + 2;
    }

    if (player1== name) {
        players[0]->setPlayerHand(playerHand);
    } else if (player2 == name) {
        players[1]->setPlayerHand(playerHand);
    }else if (player3 == name) {
        players[2]->setPlayerHand(playerHand);
    }
}

void GameEngine::saveGame(std::string fileName) {

    // add '.save' extension to the filename
    fileName += ".save";
    std::ofstream outFile;
    outFile.open(fileName);

    if (player3 != "") {
        outFile << "3playermode" << std::endl;
    } else {
        outFile << "2playermode" << std::endl;
    }

    outFile << player1 << std::endl;
    outFile << players[0]->getScore() << std::endl;
    outFile << players[0]->getPlayerHand()->toString() << std::endl;
    outFile << player2 << std::endl;
    outFile << players[1]->getScore() << std::endl;
    outFile << players[1]->getPlayerHand()->toString() << std::endl;

    // checking if there is a third player
    if (player3 != "") {
        outFile << players[2]->getName() << std::endl;
        outFile << players[2]->getScore() << std::endl;
        outFile << players[2]->getPlayerHand()->toString() << std::endl;
    }

    outFile << gameBoard->dimensionsToString() << std::endl;
    outFile << gameBoard->toString() << std::endl;
    outFile << tileBag->getTileBag()->toString() << std::endl;
    outFile << currentPlayer << std::endl;
    outFile.close();
}

bool GameEngine::loadGame(std::string fileName) {

    // Open file for reading
    std::ifstream inFile;
    inFile.open(fileName);
    GameBoard* board = nullptr;

    std::string format;
    std::string player1Name, player1Score, player1Hand;
    std::string player2Name, player2Score, player2Hand;
    std::string player3Name, player3Score, player3Hand;
    std::string boardShape, boardString;
    std::string tileBagString;
    std::string currPlayerName;

    // extract lines from the file
    getline(inFile, format);
    getline(inFile, player1Name);
    getline(inFile, player1Score);
    getline(inFile, player1Hand);
    getline(inFile, player2Name);
    getline(inFile, player2Score);
    getline(inFile, player2Hand);

    // checking if format is 3-player
    if (format == "3playermode") {
        getline(inFile, player3Name);
        getline(inFile, player3Score);
        getline(inFile, player3Hand);
    }

    getline(inFile, boardShape);
    getline(inFile, boardString);
    getline(inFile, tileBagString);
    getline(inFile, currPlayerName);

    bool loadValidated = false;

    if (format == "3playermode") {

        loadValidated = verifyMode(format) && verifyName(player1Name) && verifyName(player2Name) && 
                        verifyName(player3Name) && verifyListString(player1Hand) && 
                        verifyListString(player2Hand) && verifyListString(player3Hand) &&
                        verifyBoardShapeString(boardShape) && verifyBoardString(boardString) &&
                        verifyBoardSize(boardShape) && verifyListString(tileBagString) && 
                        verifyName(currPlayerName);

    } else {

        loadValidated = verifyMode(format) && verifyName(player1Name) && verifyName(player2Name) && 
                        verifyListString(player1Hand) && verifyListString(player2Hand) &&
                        verifyBoardShapeString(boardShape) && verifyBoardString(boardString) &&
                        verifyBoardSize(boardShape) && verifyListString(tileBagString) && 
                        verifyName(currPlayerName);
    }

    // if the format is valid
    if (loadValidated) {

        if (format == "3playermode") {
            // load players -----------------
            this->setPlayers(player1Name, player2Name, player3Name);

            // load player score -------------
            int p3Score = stoi(player3Score);
            players[2]->setScore(p3Score);

            // load player hand---------------
            loadHand(player3Hand, player3Name);

        } else {
            this->setPlayers(player1Name, player2Name);
        }

        // load player score -------------
        int p1Score = stoi(player1Score);
        int p2Score = stoi(player2Score);
        players[0]->setScore(p1Score);
        players[1]->setScore(p2Score);

        // load player hands---------------
        loadHand(player1Hand, player1Name);
        loadHand(player2Hand, player2Name);


        // load board ---------------------
        board = new GameBoard();
        std::stringstream shapeStream(boardShape);
	    std::string line;
	    getline(shapeStream, line, ',');

        // place tiles on board
        if (boardString != "") {
            std::stringstream boardStream(boardString);
            while (boardStream.good()) {
                getline(boardStream, line, ',');
                if (line[0] == ' ') {
                    line.erase(line.begin());}
                
					    
				std::string pos = line.substr(3);
                char r = pos[0];
                int c = stoi(pos.substr(1));

                Tile* tileToPlace = new Tile(line[0],line[1]-'0');
				board->placeTile(r, c, tileToPlace);
			}
		}
        this->gameBoard = board;

        // load tilebag ----------------------
        TileBag* bag = new TileBag(true);
        std::string tiles = tileBagString;
        bag->loadBag(tiles);
        this->tileBag = bag; 

        // load current player ----------------
        this->setCurrentPlayer(currPlayerName);

    } else {
        inFile.close();

        if (board != nullptr)
            delete board;
    } 
    return loadValidated;     
}

bool GameEngine::verifyMode(std::string s){
    bool valid = false;

    if (s == "2playermode" || s == "3playermode") {
        valid = true;
    }
    return valid;
}
     
bool GameEngine::verifyName(std::string s) {
	bool valid = s.length() != 0 ? true : false;

	for (char c : s) {
		if (!isupper(c))
            valid = false;			
	}
	return valid;
}

bool GameEngine::verifyListString(std::string s){
    bool valid = false;
	std::regex r("^([ROYGBP][1-6](, {0,1}[ROYGBP][1-6])*){0,1}$");

	if (regex_match(s, r))
		valid = true;
	
	return valid;
}

bool GameEngine::verifyBoardShapeString(std::string s) {
    bool valid = false;
	std::regex r("^\\d{1,2}, {0,1}\\d{1,2}$");
	if (regex_match(s, r))
		valid = true;
	
	return valid;
}

bool GameEngine::verifyBoardString(std::string s) {
    
    bool valid = false;
	std::regex r("^([ROYGBP][1-6]@[A-Z]\\d{1,2}(, {0,1}[ROYGBP][1-6]@[A-Z]\\d{1,2})*){0,1}$");

	if (regex_match(s, r))
		valid = true;

	return valid;
}

bool GameEngine::verifyBoardSize(std::string s) {

    bool valid = false;
    int rows, cols;
	std::stringstream shapeStream(s);
	std::string line;
	getline(shapeStream, line, ',');

	rows = stoi(line);
	getline(shapeStream, line, ',');

	if (line[0] == ' ')
		line.erase(line.begin());

	cols = stoi(line);

    if (rows == MAX_DIM && cols == MAX_DIM) 
        valid = true;
    
    return valid; 
}