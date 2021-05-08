
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
      string name1;
      string name2;
      cout << "Starting a New Game \n";
      cout << "Enter a name for player 1 (uppercase characters only) \n";
      // rest of code here
     
      cin >> name1;
      cout << "Enter a name for player 1 (uppercase characters only) \n";
      cin >> name2;
      cout << "Let's Play!\n";

      break;
   case 2:
      cout << "Story so far....\n";
      // rest of code here
      break;
   case 3:
      cout << "----------------------------------\n";
      cout << "\n";
      cout << "Name : David Aziz \n";
      cout << "Student ID : s3825605 \n";
      cout << "Email : s3825605@student.rmit.edu.au.edu> \n";
      cout << "\n";
      cout << "Name : Tanishpreet Kaur \n";
      cout << "Student ID : s3825118 \n";
      cout << "Email : s3825118@student.rmit.edu.au \n";
      cout << "\n";
      cout << "Name : Sai Sreshtaa Turaga \n";
      cout << "Student ID : s3814571 \n";
      cout << "Email : s3814571@student.rmit.edu.au \n";
      cout << "\n";
      cout << "Name : Rifat Raida Rashid Anannya \n";
      cout << "Student ID : s3822511 \n";
      cout << "Email : s3822511@student.rmit.edu.au\n";
      cout << "\n";
      cout << "----------------------------------\n";

      // rest of code here

      break;
   case 4:
      cout << "\n";
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