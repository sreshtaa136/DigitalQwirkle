#include "GameEngine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void GameEngine::newGame(std::string player1, std::string player2){
    
    gameBoard = new GameBoard();
    tileBag = new TileBag();
    setPlayers(player1, player2);
    currentPlayer = this->player1;
    this->player1->setPlayerHand(tileBag->createHand());
    this->player2->setPlayerHand(tileBag->createHand());
    printGameState();
    std::cout << "TileBag size: " << tileBag->getBagSize() << std::endl;
}

//place tile, remove the tile from player's hand and update hand 
bool GameEngine::placeTile(char row, int col, Colour colour, Shape shape, std::string player){
    
    Tile* tileToPlace = new Tile(colour,shape);
    bool tilePlaced = false;

    if(player == player1->getName()){
        if(player1->getPlayerHand()->searchTile(tileToPlace) != -1){
            if(gameBoard->placeTile(row, col, tileToPlace)){
                player1->getPlayerHand()->removeTile(colour, shape);
                if(tileBag->getBagSize() != 0){
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    player1->getPlayerHand()->addToEnd(tile);
                    tilePlaced = true;
                }
            }
        }
    }else if(player == player2->getName()){
        if(player2->getPlayerHand()->searchTile(tileToPlace) != -1){
            if(gameBoard->placeTile(row, col, tileToPlace)){
                player2->getPlayerHand()->removeTile(colour, shape);
                if(tileBag->getBagSize() != 0){
                    Tile* tile = new Tile(*(tileBag->drawTile()));
                    player2->getPlayerHand()->addToEnd(tile);
                    tilePlaced = true;
                }
            }
        }
    }
    return tilePlaced;
}

bool GameEngine::replaceTile(Colour colour, Shape shape, std::string player){

    Tile* tileToReplace = new Tile(colour,shape);
    bool tileReplaced = false;

    if(player == player1->getName()){
        if(player1->getPlayerHand()->searchTile(tileToReplace) != -1){
            player1->getPlayerHand()->removeTile(colour, shape);
            tileBag->getTileBag()->addToEnd(tileToReplace);
            if(tileBag->getBagSize() != 0){
                Tile* tile = new Tile(*(tileBag->drawTile()));
                player1->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
            }
        }
    }else if(player == player2->getName()){
        if(player2->getPlayerHand()->searchTile(tileToReplace) != -1){
            player2->getPlayerHand()->removeTile(colour, shape);
            tileBag->getTileBag()->addToEnd(tileToReplace);
            if(tileBag->getBagSize() != 0){
                Tile* tile = new Tile(*(tileBag->drawTile()));
                player2->getPlayerHand()->addToEnd(tile);
                tileReplaced = true;
            }
        }
    }
    return tileReplaced;
}

void GameEngine::setPlayers(std::string player1, std::string player2){
    this->player1 = new Player(player1);
    this->player2 = new Player(player2);
}

Player* GameEngine::getPlayer1(){
    return this->player1;
}

Player* GameEngine::getPlayer2(){
    return this->player2;
}

Player* GameEngine::getCurrentPlayer(){
    return this->currentPlayer;
}

void GameEngine::setCurrentPlayer(std::string playerName){
    this->currentPlayer = getPlayer(playerName);
}

Player* GameEngine::getPlayer(std::string playerName){

    Player* player;
    if(player1->getName() == playerName){
        player = player1;
    }else{
        player = player2;
    }
    return player;
}

void GameEngine::printGameState(){

    //std::cout << " \n";
    std::cout << "Score for " << player1->getName() <<
    ": " << player1->getScore() << "\n";
    std::cout << "Score for " << player2->getName() <<
    ": " << player2->getScore() << "\n\n";
    gameBoard->displayBoard();
    std::cout << " \n";
}

void GameEngine::loadHand(std::string hand, std::string name){

    LinkedList* playerHand = new LinkedList();
    
    int commaCount = 0;
    for(int i = 0; i<(int)hand.size(); ++i){
        if(hand[i] == ','){
            ++commaCount;
        }
    }

    int tileCount = (hand.size() - commaCount)/2;
    char tileArray[tileCount*2];
    int count = 0;

    for(int i = 0; i<(int)hand.size(); ++i){
        if(hand[i] != ','){
            tileArray[count] = hand[i];
            count++;
        }
    }

    count = 0;
    for(int i = 0; i<tileCount; ++i){
        char colour = tileArray[count];
        int shape = tileArray[count + 1] - '0';
        Tile* tile = new Tile(colour, shape);
        playerHand->addToEnd(tile);
        count = count + 2;
    }

    if(player1->getName() == name){
        this->player1->setPlayerHand(playerHand);
    }else if(player2->getName() == name){
        this->player2->setPlayerHand(playerHand);
    }

}

void GameEngine::saveGame(std::string fileName) {

    fileName += ".save";
    std::ofstream outFile;
    outFile.open(fileName);

    outFile << player1->getName() << std::endl;
    outFile << player1->getScore() << std::endl;
    outFile << player1->getPlayerHand()->toString() << std::endl;
    outFile << player2->getName() << std::endl;
    outFile << player2->getScore() << std::endl;
    outFile << player2->getPlayerHand()->toString() << std::endl;
    outFile << gameBoard->dimensionsToString() << std::endl;
    outFile << gameBoard->toString() << std::endl;
    outFile << tileBag->getTileBag()->toString() << std::endl;
    outFile << currentPlayer->getName() << std::endl;

    outFile.close();
}

void GameEngine::loadGame(std::string fileName) {

    //fileName += ".save";

    // Open file for reading
    std::ifstream inFile;
    inFile.open(fileName);
    GameBoard* board = nullptr;

    std::string player1Name, player1Score, player1Hand;
    std::string player2Name, player2Score, player2Hand;
    std::string boardShape, boardString;
    std::string tileBagString;
    std::string currPlayerName;

    // extract lines from file
    getline(inFile, player1Name);
    getline(inFile, player1Score);
    getline(inFile, player1Hand);
    getline(inFile, player2Name);
    getline(inFile, player2Score);
    getline(inFile, player2Hand);
    getline(inFile, boardShape);
    getline(inFile, boardString);
    getline(inFile, tileBagString);
    getline(inFile, currPlayerName);

    bool loadValidated = verifyName(player1Name) && verifyName(player2Name) && 
                         verifyListString(player1Hand) && verifyListString(player2Hand) &&
                         verifyBoardShapeString(boardShape) && verifyBoardString(boardString) &&
                         verifyBoardSize(boardShape) && verifyListString(tileBagString) && 
                         verifyName(currPlayerName);

    // if the format is valid
    if (loadValidated) {

        // load players

        this->setPlayers(player1Name, player2Name);

        int p1Score = stoi(player1Score);
        int p2Score = stoi(player2Score);

        player1->setScore(p1Score);
        player2->setScore(p2Score);

        // load player hands
        loadHand(player1Hand, player1Name);
        loadHand(player2Hand, player2Name);

        // load board
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
                int c = pos[1] - '0';

                Tile* tileToPlace = new Tile(line[0],line[1]-'0');
				board->placeTile(r, c, tileToPlace);
			}
		}

        this->gameBoard = board;

        // load tilebag
        TileBag* bag = new TileBag(true);
        std::string tiles = tileBagString;
        bag->loadBag(tiles);
        this->tileBag = bag;

        // load current player
        this->setCurrentPlayer(currPlayerName);
    }
    else {
        if(board != nullptr)
            delete board;

        std::cerr << "The file is not formatted correctly! Can't load game!" << std::endl;
    }
        
}
   
    

bool GameEngine::verifyName(std::string s) {

	bool valid = s.length() != 0 ? true : false;

	for (char c : s ) {

		if (!isupper(c)){
            valid = false;
        }			
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