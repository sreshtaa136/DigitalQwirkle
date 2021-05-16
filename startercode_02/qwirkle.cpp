
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

char alphabets[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

// checks if entered player names are valid
bool validateName (std :: string name);
// checks if the conditions for ending a game are satisfied
bool endGame(GameEngine* engine);
// verifies if a given command is valid
bool verifyCommand(std::string command);
// loads a game from the given file and returns false if file is invalid
bool validateLoadGame(std::string fileName, GameEngine* engine);

//valgrind --leak-check=full ./qwirkle

int main(int argc, char** argv) {

   int choice = 0;

   // keep showing the main menu as long as choice = 4
   while (choice !=4 ) {

      std::cout << "\nWelcome to Qwirkle!\n";
      std::cout << "-------------------\n";
      std::cout << "Menu\n";
      std::cout << "----\n";
      std::cout << "1. New Game\n";
      std::cout << "2. Load Game\n";
      std::cout << "3. Credits (Show student information) \n";
      std::cout << "4. Quit \n\n";
      std::cout << "> ";

      std::cin >> choice;

      //checking if input is integer or not
      while (std::cin.fail()) {

         std::cout << "Invalid Input" << std::endl;
         std::cin.clear();
         std::cin.ignore(256, '\n');
         std::cout << "> ";
         std::cin >> choice;
      }
      
      // checker for loading a game
      bool load = false;
      GameEngine *engine = new GameEngine();

      // loading a game 
      if (choice == 2) {

         std::string fileName;

         do {
            
            std::cout << "\nEnter the file name from which load a game\n";
            std::cout << "> ";
            std::cin >> fileName;

         } while (!validateLoadGame(fileName, engine));

         if (fileName == "^D") {
            choice = 4;

         } else {
            load = true;
            std::cout << "\nQwirkle game successfully loaded\n";
            // redirecting to new game to continue playing
            choice = 1;
         }
      }

      // starting a new game
      if (choice == 1) {
         // checker to keep track of player turns
         int turn = 0;

         // checker to check if player enters quit command
         bool quit = false;

         std::string currentPlayer;
         std::string player1;
         std::string player2;
         std::cin.ignore();

         // starts a new game only if load game was not selected
         if (load == false) {

            std::cout << "\nStarting a New Game \n\n";

            do {
               std::cout << "Enter a name for player 1"
                        << "(uppercase characters only) \n";
               std::cout << "> "; 
               getline(std::cin, player1);

            } while (!validateName(player1));

            do {
               std::cout << "\nEnter a name for player 2"
               << "(uppercase characters only) \n"
                        << "> ";
               getline(std::cin, player2);

            } while (!validateName(player2) || (player1 == player2));

            std::cout << "\nLet's Play!\n\n";

            currentPlayer = player1;
            std::cout << currentPlayer << ", it's your turn\n";

            // initialising a new game
            engine->newGame(player1, player2);

            std::cout << "Your hand is\n";
            engine->getPlayer1()->getPlayerHand()->printList();
            std::cout << "\n";
            
         } else {

            // sets the game state according to the loaded game
            currentPlayer = engine->getCurrentPlayer()->getName();
            player1 = engine->getPlayer1()->getName();
            player2 = engine->getPlayer2()->getName();
            turn++;
         }

         // runs as long as game ends or exit command is entered
         while (!endGame(engine) && !quit) {

            // updating the game state and displaying after the first turn
            if (turn != 0) {

               std::cout << "\n";
               std::cout << currentPlayer << ", it's your turn\n";
               engine->printGameState();
               std::cout << "Your hand is\n";
               engine->getPlayer(currentPlayer)->getPlayerHand()->printList();
               //test
               // std::cout << "TileBag size: " 
               //<< engine->tileBag->getBagSize() << std::endl;
               // std::cout << "\n";
            }

            // taking user command (place/replace/save/quit)
            std::cout << "> ";
            std::string userAction;
            getline(std::cin, userAction);
            
            // verifying the format of the command
            while (!verifyCommand(userAction)) {
               std::cout << "\n Invalid input \n";
               std::cout << "> "; 
               getline(std::cin, userAction);
            }

            // checker to check if any command has been executed
            bool executed = false;
            while (!executed) {

               // executing the "place" command
               if (userAction[0] == 'p'){

                  // converting the command into a char array
                  std::string s = userAction;
                  char cstr[s.size() + 1];
                  std::copy(s.begin(), s.end(), cstr);
                  cstr[s.size()] = '\0';

                  int icol;
                  char col;

                  // extracting column number and converting it into integer
                  if (userAction.size() == 14) {
                     col = userAction[13];
                     icol = col - '0'; 

                  } else {
                     std ::string col = userAction.substr(13, 2);
                     icol = std::stoi(col);
                  }

                  // extracting the tile shape and converting it into integer
                  char shape = userAction[7];
                  int ishape = shape - '0';

                  bool place = engine->placeTile(userAction[12], icol, 
                                          userAction[6], ishape, currentPlayer);
                  
                  // asking for input until tile is placed successfully or 
                  // a different command is entered
                  while (!place && userAction[0] == 'p') {
                  
                     std::cout << "\n Invalid tile \n";
                     std::cout << "> ";
                     getline(std::cin, userAction);

                     if (userAction[0] == 'p') {

                        s = userAction;
                        char cstr[s.size() + 1];
                        std::copy(s.begin(), s.end(), cstr);
                        cstr[s.size()] = '\0';

                        if (userAction.size() == 14) {
                           col = userAction[13];
                           icol = col - '0'; 
                        } else {
                           std ::string col = userAction.substr(13, 2);
                           icol = std::stoi(col);
                        } 

                        shape = userAction[7];
                        ishape = shape - '0';
                        place = engine->placeTile(userAction[12], icol, 
                                 userAction[6], ishape, currentPlayer);
                     }
                     
                  }

                  // checking for qwirkle if at all the tile was placed
                  if (place == true) {

                     if (userAction.size() == 14) {
                        col = userAction[13];
                        icol = col - '0'; 

                     } else {
                        std ::string col = userAction.substr(13, 2);
                        icol = std::stoi(col);
                     } 

                     int row = engine->gameBoard->charToInt(userAction[12]);
                     bool qwirkle = engine->gameBoard->isQwirkle(row, icol);

                     if (qwirkle) {
                        std::cout<< "QWIRKLE!!!\n";
                     }
                     
                     int points = engine->gameBoard->calculatePoints(userAction[12], icol);
                     engine->getPlayer(currentPlayer)->incrementScore(points);
                     executed = true;
                     turn++;
                  }                 
               }
               else if (userAction[0] == 'r') {
                  // replacing a tile
                  bool replace = engine->replaceTile(userAction[8], 
                                 userAction[9] - '0', currentPlayer);

                  // asking for input until tile is replaced successfully or
                  // a different command is entered
                  while (!replace && userAction[0] == 'r') {

                     if (engine->tileBag->getBagSize()==0) {
                        std::cout << "\n Cannot replace. Tile bag is empty. "
                                 << "Enter a different command.\n";
                        std::cout << "> ";
                        getline(std::cin, userAction);

                     } else {
                        std::cout << "\n Invalid tile \n";
                        std::cout << "> ";
                        getline(std::cin, userAction);
                     }
                  }

                  if (replace == true) {
                     turn++;
                     executed = true;
                  }

               } else if (userAction[0] == 's') {

                  // saving a game
                  int nameSize = userAction.size() - 5;
                  std ::string fileName = userAction.substr(5, nameSize);
                  engine->saveGame(fileName);
                  std::cout << "\nGame successfully saved.\n";
                  executed = true;
                  
               } else if (userAction[0] == '^') {

                  //quitting the game
                  quit = true;
                  executed = true;
                  choice = 4;
               }
            }
           
            // switching between players as turns change
            if (userAction[0] != 's') {
               if (currentPlayer == player1) {
               
                  engine->setCurrentPlayer(player2);
                  currentPlayer = engine->getCurrentPlayer()->getName();

               } else {
                  
                  engine->setCurrentPlayer(player1);
                  currentPlayer = engine->getCurrentPlayer()->getName();
               }
            }

         }

         // displaying scores and declaring winner when game ends
         if (endGame(engine)) {
            
            std::cout << "Game over \n";
            std::cout << "Score for " << engine->getPlayer1()->getName() 
            << ": " << engine->getPlayer1()->getScore() << "\n";
            std::cout << "Score for " << engine->getPlayer2()->getName() 
            << ": " << engine->getPlayer2()->getScore() << "\n";

            if (engine->getPlayer1()->getScore() > engine->getPlayer2()->getScore()) {
               std::cout << "Player " << engine->getPlayer1()->getName() 
                         << " won!\n\n";

            } else if (engine->getPlayer1()->getScore() == 
                       engine->getPlayer2()->getScore()) {

               std::cout << "Oops! It's a tie! Play again?" << std::endl;

            } else {
               std::cout << "Player " << engine->getPlayer2()->getName() 
                         << " won!\n\n";
            }

            std::cout << "Goodbye \n";

            delete engine;
            engine = nullptr;
         }
      }

      // displaying student information
      if (choice == 3) {
         std::cout << "\n----------------------------------\n";
         std::cout << "\n";
         std::cout << "Name : David Aziz \n";
         std::cout << "Student ID : s3825605 \n";
         std::cout << "Email : s3825605@student.rmit.edu.au \n";
         std::cout << "\n";
         std::cout << "Name : Tanishpreet Kaur \n";
         std::cout << "Student ID : s3825118 \n";
         std::cout << "Email : s3825118@student.rmit.edu.au \n";
         std::cout << "\n";
         std::cout << "Name : Sai Sreshtaa Turaga \n";
         std::cout << "Student ID : s3814571 \n";
         std::cout << "Email : s3814571@student.rmit.edu.au \n";
         std::cout << "\n";
         std::cout << "Name : Rifat Raida Rashid Anannya \n";
         std::cout << "Student ID : s3822511 \n";
         std::cout << "Email : s3822511@student.rmit.edu.au\n";
         std::cout << "\n";
         std::cout << "----------------------------------\n";
      }

      // terminating the program
      if (choice == 4) {
         std::cout << "\nGoodbye \n";
      }
      
      if (choice < 1 || choice > 4) {
         std::cout << "\nNot a Valid Choice. \n";
         std::cout << "Choose again.\n\n";
      }
   } 
}

bool validateLoadGame(std::string fileName, GameEngine* engine){

   bool check = false;

   std::ifstream file(fileName);

   // checking if a file exists
   if (file.fail()) {

      check = false;

   } else {

      bool load = engine->loadGame(fileName);

      // checking if a file is formatted correctly
      if (load) {
         check = true;
      } else {
         check = false;
      }
   }

   if (fileName == "^D") {
      check = true;
   }

   return check;
}


bool validateName(std ::string name)
{
   bool check = true;
   for (int i = 0; i < (int) name.length(); i++) {
      int charAsci = name[i];
      if (!((charAsci >= 65) && (charAsci <= 90)) && check == true) {
         check = false;
      } else if(charAsci == ' ') {
         check = false;
      }
   }
   if (check == false) {
      std::cout << "\nOnly Letters in UPPERCASE WITHOUT SPACES are valid! \n";
   }
   return check;
}

bool verifyCommand(std::string command){

   bool check = true;

   // checking if length exceeds expected number
   if (command.length() == 14 || command.length() == 10 ||
       command.length() == 15) {
      
      // checkers for validating shape and colour
      bool foundColour = false ;
      bool foundShape = false;

      // checking the place command
      if ((command.length() == 14 || command.length() == 15) &&
         command[0] == 'p') {
         std::string tmp = command.substr(0, 6);

         if (tmp != "place ") {
            check = false;
         }

         for (int i = 0; i < 6; i++) {
            if (command[6] == colours[i]) {

            foundColour = true;
            }

            int sha = command[7] - '0';
            if (sha== shapes[i]) {
               foundShape = true;
            }
         }

         if (!(foundColour && foundShape)) {

            check = false;
         }
         
         tmp = command.substr(8, 4);
         if (tmp != " at ") {
            check = false;
         }
         
         bool foundcol = false;
         bool foundrow = false;

         for (int i = 0; i < 26; i++) {
            if (command[12] == alphabets[i]) {
               foundrow= true;
            }

            int icol;
            if (command.length() == 15) {
               std ::string col = command.substr(13, 2);
               icol = std::stoi(col);
            } else {
               icol = command[13] - '0';
            }

            if (icol == i) {
               foundcol = true;
            }
         }

         if (!(foundrow && foundcol)) {
            check = false;
         }

      } else if (command.length() == 10  && command[0] == 'r') {

         // checking the replace command
         std ::string tmp = command.substr(0, 8);

         if (tmp != "replace ") {
            check = false;
         }

         for (int i = 0; i < 6; i++) {
            if (command[8] == colours[i]) {
               foundColour = true;
            }

            int sha = command[9] - '0';
            if (sha == shapes[i]) {
               foundShape = true;
            }
         }

         if (!(foundColour && foundShape)) {
            check = false;
         }
      }

   } else {
      check = false;
   } 

   // checking the save command
   std ::string tmp = command.substr(0, 5);
   if (tmp == "save ") {
      check = true;
   }

   // checking the exit command
   if(command == "^D") {
      check = true;
   }

   return check;
}

//will check if you should end the game
bool endGame(GameEngine* engine) {

   bool check = false;
   bool checkHand = engine->getPlayer1()->getPlayerHand()->getSize() == 0 ||
                    engine->getPlayer2()->getPlayerHand()->getSize() == 0;

   if (engine->tileBag->getBagSize() == 0 && checkHand) {
      check = true;
   }
   
   return check;
}