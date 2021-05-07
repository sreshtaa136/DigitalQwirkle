
//#include "LinkedList.h"

#include <iostream>

//#define EXIT_SUCCESS    0
using namespace std;

int main(int argc, char** argv) {

   //LinkedList* list = new LinkedList();
   

   int choice;
   cout << " Welcome to Qwirkle!\n";
   cout << " -------------------\n";
   cout << " Menu\n";
   cout << " ----\n";
   cout << " 1 - New Game\n";
   cout << " 2 - Load Game\n";
   cout << " 3 - Credits (Show student information) \n";
   cout << " 4 - Quit \n";
   cout << " Enter your Choice: ";

   cin >> choice;
   switch (choice)
   {
   case 1:
      cout << "game start!\n";
      // rest of code here
      break;
   case 2:
      cout << "Story so far....\n";
      // rest of code here
      break;
   case 3:
      cout << "Ahahah, you really think I will help you?\n";
      // rest of code here
      break;
   case 4:
      cout << "End of Program.\n";
      break;
   default:
      cout << "Not a Valid Choice. \n";
      cout << "Choose again.\n";
      cin >> choice;
      break;
   }

   
   //delete list;
   return EXIT_SUCCESS;
}
//to run: 
//make sure you are on starter code dr and run the following in the terminal
//g++ -Wall -Werror -std=c++14 -O -o qwirkle qwirkle.cpp
//./qwirkle