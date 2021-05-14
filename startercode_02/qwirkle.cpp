
#include <iostream>
#include <cctype>
#include <string>
#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"
#include "LinkedList.h"
#include "TileBag.h"
#include "Player.h"
#include "GameBoard.h"
#include "GameEngine.h"
char alphabets[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

bool validateName (std :: string name);
bool qwirkle();
bool endGame(GameEngine* engine);
void newGame(std::string player1, std::string player2);
bool verifyCommand(std::string command);

int main(int argc, char** argv) {

   //TESTING

   // GameEngine* engine = new GameEngine();
   // engine->newGame("A", "B");
   // //engine->printGameState();
   // std::cout << "A's hand: \n";
   // engine->getPlayer1()->printPlayerHand();
   // std::cout << "B's hand: \n";
   // engine->getPlayer2()->printPlayerHand();
   // std::cout << "\n";

   // engine->tileBag->getTileBag()->printList();
   // Tile* tile = engine->getPlayer1()->getPlayerHand()->getTileAtIndex(0);
   // engine->replaceTile(tile->getColour(), tile->getShape(), "A");
   // std::cout << "A's hand: \n";
   // engine->getPlayer1()->printPlayerHand();
   // engine->tileBag->getTileBag()->printList();

   // LinkedList* list = new LinkedList();
   // Tile* t1 = new Tile('Y', 1);
   // Tile* t2 = new Tile('Y', 2);
   // Tile* t3 = new Tile('Y', 3);
   // Tile* t4 = new Tile('Y', 4);
   // //Tile* t5 = new Tile('Y', 1);

   // list->addToEnd(t1);
   // list->addToEnd(t2);
   // list->addToEnd(t3);
   // list->addToEnd(t4);
   // //list->addToEnd(t5);
   // list->printList();

   //std::cout << list->tileCount(t1);
   // list->replaceTile(t1,t4);
   // list->printList();

   // list->switchTiles(t2,t3);
   // list->printList();
   // list->switchTiles(t1,t4);
   // list->printList();

   
   // list->removeTile('Y', 1);
   // list->printList();
   // list->removeTile('Y', 2);
   // list->printList();
   // list->removeTile('Y', 3);
   // list->printList();
   // list->removeTile('Y', 4);
   // list->printList();
   //std::cout << list->getSize();
   //bool check = list->searchTile(t3->getColour(), t3->getShape());

   // std::cout << list->searchTile('Y', 2) << "\n";
   // std::cout << list->searchTile('Y', 3) << "\n";

   // delete list;
   // list = nullptr;

   // TileBag* bag = new TileBag();
   // std::cout << "\n";
   // bag->shuffleBag();
   // bag->tileBag->printList();
   // //bag->tileBag->printCount();
   // bag->createHand();
   // bag->tileBag->printList();
   
   //TESTING ENDS ------------------------------------------
   // LinkedList* list = new LinkedList();
   // Tile* t1 = new Tile('Y', 1);
   // Tile* t2 = new Tile('R', 2);
   // list->addToFront(t1);
   // list->printList();
   // list->addToFront(t2);
   // list->printList();
   
   // GameBoard* g = new GameBoard();
   // Tile* t3 = new Tile('R', 1);
   // Tile* t4 = new Tile('Y', 2);
   

   // g->placeTile('C', 2, t4);
   // g->placeTile('C', 1, t2);
   // g->placeTile('D', 1, t3);
   // g->placeTile('C', 2, t2);
   // g->placeTile('A', 2, t1);



   // //tile->printTile();
   // g->displayBoard();
   // //TESTING ENDS
   std::string a = "replace Y1";
   std::cout << a[0];


   int choice = 0;
   while (choice !=4 ){
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
   
      while (std::cin.fail())
      {
         std::cout << "Invalid Input" << std::endl;
         std::cin.clear();
         std::cin.ignore(256, '\n');
         std::cout << "> ";
         std::cin >> choice;
         ;
      }
      if (choice == 1)
      {
         std::string player1;
         std::string player2;
         std::cout << "\nStarting a New Game \n\n";
         std::cout << "Enter a name for player 1 (uppercase characters only) \n";
         do{
            std::cout << "> "; 
            std::cin >> player1;
         } while (!validateName(player1));

         do{
            std::cout << "\nEnter a name for player 2 (uppercase characters only) \n"
                     << "> ";
            std::cin >> player2;
         } while (!validateName(player2) || (player1 == player2));

         std::cout << "\nLet's Play!\n\n";
         std::cout << player1 << ", it's your turn\n";

         GameEngine* engine = new GameEngine();
         engine->newGame(player1, player2);
         std::string currentPlayer = player1;

         std::cout << "You hand is\n";
         engine->getPlayer2()->getPlayerHand()->printList();
         std::cout << "\n";
         std::string userAction;

            std::cout << "> ";
            std::cin.ignore();
            getline(std::cin, userAction);
            std::cout << userAction << userAction.length();
         while (! verifyCommand (userAction))
         {
            /* code */
            std::cout << "> ";
          //  std::cin.ignore();
            getline(std::cin, userAction);
            std::cout << userAction << userAction.length();
         }
         
         // while(!endGame(engine)){

         //    std::string userAction;
         //    getline(std::cin, userAction);
         //    std::cout << userAction;
         //    //std::cin >> userAction;
        // verifyCommand(userAction);

         //    //user prompt
         //    if(currentPlayer == player1){
         //       currentPlayer = player2;
         //    }else{
         //       currentPlayer = player1;
         //    }
         // }
      }
      else if (choice == 2)
      {
         std::cout << "\nStory so far....\n";
      }
      else if (choice == 3)
      {
         std::cout << "\n----------------------------------\n";
         std::cout << "\n";
         std::cout << "Name : David Aziz \n";
         std::cout << "Student ID : s3825605 \n";
         std::cout << "Email : s3825605@student.rmit.edu.au.edu \n";
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
      else if (choice == 4)
      {
         std::cout << "Goodbye \n";
      }
      else
      {
         std::cout << "\nNot a Valid Choice. \n";
         std::cout << "Choose again.\n\n";
      }
   }
   
}

//to run: 
//make sure you are on starter code dr and run the following in the terminal
//g++ -Wall -Werror -std=c++14 -O -o qwirkle qwirkle.cpp Tile.cpp Node.cpp LinkedList.cpp TileBag.cpp GameBoard.cpp Player.cpp GameEngine.cpp
//g++ -Wall -Werror -std=c++14 -O -o qwirkle qwirkle.cpp Tile.cpp Node.cpp LinkedList.cpp GameBoard.cpp
//./qwirkle
//valgrind --leak-check=full ./qwirkle

bool validateName(std ::string name)
{
   for (int i = 0; i < (int) name.length(); i++)
   {
      int charAsci = name[i];
      if (!((charAsci >= 65) && (charAsci <= 90)))
      {
         std::cout << "\nOnly Letters in UPPERCASE are valid! \n";
         return false;
      }
   }
   return true;
}

 bool verifyCommand(std::string command){
 if (command.length() ==14 || command.length() == 10 ){
    bool foundColour = false ;
    bool foundShape = false;

    if (command.length() == 14)
    {
       std ::string tmp = command.substr(0, 6);

       if (tmp != "place ")
       {
          return false;
       }
       for (int i = 0; i < 6; i++)
       {
          if (command[6] == colours[i])
          {
           foundColour = true;
          }
          int sha = command[7] - '0';
           if (sha== shapes[i])
          {
             foundShape = true;
          }
       }

         if (!(foundColour && foundShape)){

                return false;
         }
         tmp = command.substr(8, 4);

         if (tmp != " at ")
         {
            return false;
         }
         bool foundcol = false;
         bool foundrow = false;
         for (int i = 0; i < 25; i++)
         {
            if (command[12] == alphabets[i])
            {
               foundrow= true;
            }
            int sha = command[13] - '0';
            if (sha == i)
            {
               foundcol = true;
            }
         }

         if (!(foundrow && foundcol))
         {
            return false;
         }
      }

   else {
      std ::string tmp = command.substr(0, 8);

      if (tmp != "replace ")
      {
         return false;
      }
      for (int i = 0; i < 6; i++)
      {
         if (command[8] == colours[i])
         {
            foundColour = true;
         }
         int sha = command[9] - '0';
         if (sha == shapes[i])
         {
            foundShape = true;
         }
      }

      if (!(foundColour && foundShape))
      {

         return false;
      }
   }
 }
 else {

    std::cout << "\n Invalid input \n";
    return false;

 } return true ;
 }
//     
//       bool verify = false;
//    }
//    else if (command[i] = 14){
//       if (command[0]!= "p"){
//          bool verify = false;
//       }
//       if (command[1] != "l"){
//          bool verify = false;
//       }
//       if (command[2] != "a")
//       {
//          bool verify != false;
//       }
//       if (command[3] != "c")
//       {
//          bool verify = false;
//       }
//       if (command[4] != "e")
//       {
//          bool verify = false;
//       }
//       if (command[5] != " ")
//       {
//          bool verify = false;
//       }
//       if (command[6] != Colour)
//       {
//          bool verify = false;
//       }
//       if (command[7] != Shape)
//       {
//          bool verify = false;
//       }
//       if (command[8] == " ")
//       {
//          bool verify = false;
//       }
//       if (command[9] == "a")
//       {
//          bool verify = false;
//       }
//       if (command[10] == "t")
//       {
//          bool verify = false;
//       }
//       if (command[11] == " ")
//       {
//          bool verify = false;
//       }
//       if (command[12] == GameBoard.col)
//       {
//          bool verify = false;
//       }
//       if (command[13] == GameBoard.row)
//       {
//          bool verify = false;
//       }
//    } return verify;
   
//    else if (command[i] != 10){
//       bool verify = false;
//    }
   
//       return verify;
// }
//}
// bool qwirkle(){
//    //check for possible qwirkle

// }
   
//will check if you should end the game
bool endGame(GameEngine* engine){
   bool check = false;
   bool checkHand = engine->getPlayer1()->getPlayerHand()->getSize() == 0 ||
                    engine->getPlayer2()->getPlayerHand()->getSize() == 0;

   if(engine->tileBag->getBagSize() == 0 &&
   checkHand){
      check = true;
   }
   return check;
}

void newGame(std::string player1, std::string player2){

   GameEngine* engine = new GameEngine();
   engine->newGame(player1, player2);
   std::string currentPlayer = player1;

   while(!endGame(engine)){
      //user prompt
      if(currentPlayer == player1){
         currentPlayer = player2;
      }else{
         currentPlayer = player1;
      }
   }
   if(endGame(engine)){
      
      std::cout << "Game over \n";
      std::cout << "Score for " << engine->getPlayer1()->getName() 
      << ": " << engine->getPlayer1()->getScore() << "\n";
      std::cout << "Score for " << engine->getPlayer2()->getName() 
      << ": " << engine->getPlayer2()->getScore() << "\n";

      if(engine->getPlayer1()->getScore() > engine->getPlayer2()->getScore()){
         std::cout << "Player " << engine->getPlayer1()->getName() <<
         " won!\n\n";
      }else{
         std::cout << "Player " << engine->getPlayer2()->getName() <<
         " won!\n\n";
      }
      std::cout << "Goodbye \n";
   }
}
