#include "Menu.h"

int main(int argc, char** argv) {

   Menu* menu = new Menu();
   menu->takeInput();

   delete menu;
   menu = nullptr;
   
}