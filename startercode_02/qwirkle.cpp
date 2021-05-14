
#include <iostream>
#include <cctype>

#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"
#include "LinkedList.h"
#include "GameBoard.h"


bool validateName (std :: string name);
int main(int argc, char** argv) {

   //TESTING
   LinkedList* list = new LinkedList();
   Tile* t1 = new Tile('Y', 1);
   Tile* t2 = new Tile('R', 2);
   list->addToFront(t1);
   list->printList();
   list->addToFront(t2);
   list->printList();
   
   GameBoard* g = new GameBoard();
   Tile* t3 = new Tile('R', 1);
   Tile* t4 = new Tile('Y', 2);
   

   g->placeTile('C', 2, t4);
   g->placeTile('C', 1, t2);
   g->placeTile('D', 1, t3);
   g->placeTile('C', 2, t2);
   g->placeTile('A', 2, t1);



   //tile->printTile();
   g->displayBoard();
   //TESTING ENDS
 

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
         std::string name1;
         std::string name2;
         std::cout << "\nStarting a New Game \n\n";
         std::cout << "Enter a name for player 1 (uppercase characters only) \n"
         << "> ";
         do{
            std::cout << "> "; 
            std::cin >> name1;
         } while (!validateName(name1));

         do{
            std::cout << "\nEnter a name for player 2 (uppercase characters only) \n"
                     << "> ";
            std::cin >> name2;
         } while (!validateName(name2));

         std::cout << "\nLet's Play!\n";
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
         std::cout << "Email : s3825605@student.rmit.edu.au.edu> \n";
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
//g++ -Wall -Werror -std=c++14 -O -o qwirkle qwirkle.cpp Tile.cpp Node.cpp LinkedList.cpp GameBoard.cpp
//./qwirkle

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
   