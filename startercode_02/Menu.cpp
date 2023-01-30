#include "Menu.h"

Menu::Menu(){
    engine = new GameEngine();
}

Menu::~Menu(){
    delete engine;
    engine = nullptr;
}

void Menu::takeInput(){

   std::string choice = START;

   // keep showing the main menu as long as choice = 4
   while (choice != QUIT) {

       displayMenu(START);

       do{
           std::cout << "> ";
           getline(std::cin, choice);
        } while (!validateChoice(choice, false));

        bool load = false;
        
        if (choice == "^D") {
            choice = QUIT;
        }

        // loading a game 
        if (choice == LOADGAME) {      

            load = loadGame(); 
            if (load) {
               choice = NEWGAME;
            } else {
               choice = QUIT;
            }
        }

        // starting a new game
        if (choice == NEWGAME) {

            std::string mode = "1";
            bool threePlayer = false;

            if (!load) {
                //presenting new game options
                displayMenu(NEWGAME);
                do{
                    std::cout << "> ";
                    getline(std::cin, mode);

                } while (!validateChoice(mode, true));
            }

            // checking which mode was selected
            // 1 for 2 player, 2 for 3 player
            if (mode == "^D") {
                choice = QUIT;

            } else if (mode == "2"){

                threePlayer = true;
                //checker to see if game ended
                bool end = newGame(load, threePlayer);
                if(end){
                    choice = QUIT;
                }

            } else {

                bool end = false;
                if (engine->getPlayer3Name() != "") {
                    threePlayer = true;
                    end = newGame(load, threePlayer);
                } else {
                    threePlayer = false;
                    end = newGame(load, threePlayer);
                }
                
                if (end) {
                    choice = QUIT;
                }
            }
        }

        // displaying student information
        if (choice == CREDITS) {
            displayMenu(CREDITS);
        }

        // terminating the program
        if (choice == QUIT) {
            displayMenu(QUIT);
        }
    }  
}

bool Menu::newGame(bool load, bool threePlayer){

    // checker to keep track of player turns
    int turn = 0;

    // checker to check if player enters quit command
    bool quit = false;

    std::string currentPlayer;
    std::string player1;
    std::string player2;
    std::string player3 = "";

    // starts a new game only if load game was not selected
    if (load == false) {

        std::cout << "\nStarting a New Game \n\n";

        do {
            std::cout << "Enter a name for player 1"
                    << "(uppercase characters only) \n";
            std::cout << "> "; 
            getline(std::cin, player1);
            
        } while (!validatePlayerName(player1));

        if (player1 == "^D") {
            quit = true;
        }

        if (!quit) {

            do {
                std::cout << "\nEnter a name for player 2"
                << "(uppercase characters only) \n"
                        << "> ";
                getline(std::cin, player2);
                if(player1 == player2){
                    std::cerr << "\nINVALID NAME: players cannot have the same name"
                    << std::endl;
                }
            } while (!validatePlayerName(player2) || (player1 == player2));
            
            if (player2 == "^D") {
                quit = true;
            }
        }

        if (!quit && threePlayer) {

            do {
                std::cout << "\nEnter a name for player 3"
                << "(uppercase characters only) \n"
                        << "> ";
                getline(std::cin, player3);

                if (player1 == player3 || player2 == player3) {
                    std::cerr << "\nINVALID NAME: players cannot have the same name"
                    << std::endl;
                }

            } while (!validatePlayerName(player2) || (player1 == player3) || (player2 == player3));
            
            if (player3 == "^D") {
                quit = true;
            }
        }

        if (!quit) {

            std::cout << "\nLet's Play!\n\n";

            currentPlayer = player1;
            std::cout << currentPlayer << ", it's your turn\n";

            // initialising a new game
            if (threePlayer) {
                engine->newGame(player1, player2, player3);
            } else {
                engine->newGame(player1, player2);
            }

            //TEST LINE
            //std::cout << "\nTileBag size: " << engine->tileBag->getBagSize() << std::endl;

            std::cout << "Your hand is\n";
            engine->getPlayer1()->getPlayerHand()->printList();
            std::cout << "\n";
        }

    } else {
        // sets the game state according to the loaded game
        currentPlayer = engine->getCurrentPlayer();
        player1 = engine->getPlayer1()->getName();
        player2 = engine->getPlayer2()->getName();
        
        if (threePlayer) {
            player3 = engine->getPlayer3Name();
        }
        turn++;
    }

    // runs as long as game ends or exit command is entered
    if (!quit) {
        while (!endGame(threePlayer) && !quit) {

            currentPlayer = engine->getCurrentPlayer();
            // updating the game state and displaying after the first turn
            if (turn != 0) {

                std::cout << "\n";
                std::cout << currentPlayer << ", it's your turn\n";
                engine->printGameState();
                std::cout << "Your hand is\n";
                engine->getPlayer(currentPlayer)->getPlayerHand()->printList();
                //test
                // std::cout << "TileBag size: " 
                // << engine->tileBag->getBagSize() << std::endl;
                std::cout << "\n";
            }

            std::string userAction;

            // taking user command (place/replace/save/quit)
            // and verifying the format of the command
            do{
                std::cout << "> ";
                getline(std::cin, userAction);

            } while (!validateCommand(userAction));

            // checker to check if any command has been executed
            bool executed = false;
            while (!executed) {

                //checker to ensure command is valid
                bool commandValid = validateCommand(userAction);
                
                // executing the "place" command
                if (userAction[0] == 'p') {

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
                    while ((!place && userAction[0] == 'p') || !commandValid) {
                    
                        std::cout << "> ";
                        getline(std::cin, userAction);

                        if (userAction[0] == 'p' && validateCommand(userAction)) {

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
                            std::cout<< "\nQWIRKLE!!!\n";
                        }
                        
                        int points = engine->gameBoard->calculatePoints(userAction[12], icol);
                        engine->getPlayer(currentPlayer)->incrementScore(points);
                        executed = true;
                        turn++;
                    }                 
                }
                else if (userAction[0] == 'r') {

                    commandValid = validateCommand(userAction);
                    // replacing a tile
                    if (commandValid) {

                        bool replace = engine->replaceTile(userAction[8], 
                                        userAction[9] - '0', currentPlayer);

                        // asking for input until tile is replaced successfully or
                        // a different command is entered or
                        // command is invalid
                        while ((!replace && userAction[0] == 'r') || !commandValid) {

                            std::cout << "> ";
                            getline(std::cin, userAction);
                            commandValid = validateCommand(userAction);

                            if (userAction[0] == 'r' && commandValid) {
                                replace = engine->replaceTile(userAction[8], 
                                        userAction[9] - '0', currentPlayer);
                            }
                        }
                        if (replace == true) {
                            turn++;
                            executed = true;
                        }
                    }

                } else if (userAction[0] == 's') {

                    commandValid = validateCommand(userAction);

                    // saving a game
                    if (commandValid) {
                        int nameSize = userAction.size() - 5;
                        std ::string fileName = userAction.substr(5, nameSize);
                        engine->saveGame(fileName);
                        std::cout << "\nGame successfully saved.\n";
                        executed = true;
                    }
                    
                } else if (userAction[0] == '^') {

                    commandValid = validateCommand(userAction);
                    //quitting the game
                    if (commandValid) {
                        quit = true;
                        executed = true;
                    }
                }
            }
            
            // switching between players as turns change
            if (userAction[0] != 's') {

                if (currentPlayer == player1) {          
                    engine->setCurrentPlayer(player2);
                } else if (currentPlayer == player2) {
                    
                    if (threePlayer) {
                        engine->setCurrentPlayer(player3);                   
                    } else {
                        engine->setCurrentPlayer(player1);                   
                    }

                } else if (currentPlayer == player3) {          
                    engine->setCurrentPlayer(player1);               
                }
            }
        }


        // displaying scores and declaring winner when game ends
        if (endGame(threePlayer) && !quit) {
        
            std::cout << "\nGame over \n";
            std::cout << "Score for " << engine->getPlayer1()->getName() 
            << ": " << engine->getPlayer1()->getScore() << "\n";
            std::cout << "Score for " << engine->getPlayer2()->getName() 
            << ": " << engine->getPlayer2()->getScore() << "\n";
            if (threePlayer) {
                std::cout << "Score for " << engine->getPlayer3Name() 
                << ": " << engine->getPlayer3()->getScore() << "\n";
            }
            
            if (engine->getPlayer1()->getScore() > engine->getPlayer2()->getScore()) {

                if (threePlayer) {
                    if (engine->getPlayer1()->getScore() > engine->getPlayer3()->getScore()) {
                        std::cout << "Player " << engine->getPlayer1()->getName() 
                            << " won!\n";
                    }
                } else {
                    std::cout << "Player " << engine->getPlayer1()->getName() 
                            << " won!\n";
                }

            } else if (engine->getPlayer1()->getScore() == engine->getPlayer2()->getScore()) {

                if (threePlayer) {
                    if ((engine->getPlayer1()->getScore() == engine->getPlayer3()->getScore()) &&
                    (engine->getPlayer2()->getScore() == engine->getPlayer3()->getScore())) {
                        std::cout << "Oops! It's a tie! Play again?" << std::endl;
                    }
                } else {
                    std::cout << "Oops! It's a tie! Play again?" << std::endl;
                }

            } else if (engine->getPlayer2()->getScore() > engine->getPlayer1()->getScore()) {

                if (threePlayer) {
                    if(engine->getPlayer2()->getScore() > engine->getPlayer3()->getScore()){
                        std::cout << "Player " << engine->getPlayer2()->getName() 
                            << " won!\n";
                    }
                } else {
                    std::cout << "Player " << engine->getPlayer2()->getName() 
                            << " won!\n";
                }

            }
            if (threePlayer) {
                if ((engine->getPlayer3()->getScore() > engine->getPlayer1()->getScore()) &&
                (engine->getPlayer3()->getScore() > engine->getPlayer2()->getScore())) {
                std::cout << "Player " << engine->getPlayer3Name()
                            << " won!\n";
                }
            }
            quit = true;       
        }
    }
    return quit;
}

bool Menu::loadGame(){

    std::string fileName;
    bool load;

    do {
        std::cout << "\nEnter the file name from which load a game\n";
        std::cout << "> ";
        std::cin >> fileName;
        std::cin.ignore();
    } while (!validateLoadGame(fileName));

    if (fileName == "^D") {
        load = false;
    } else {
        load = true;
        std::cout << "\nQwirkle game successfully loaded\n";      
    }
    return load;
}

bool Menu::validateLoadGame(std::string fileName){
    
    bool checkFile = false;
    std::ifstream file(fileName);

    // checking if the EOF character was entered
    if (fileName != "^D") {
        // checking if a file exists
        if (file.fail()) {
            checkFile = false;
            std::cerr << "\nCANNOT OPEN FILE: please enter a valid file name"
                    << std::endl;
        } else {

            bool load = engine->loadGame(fileName);
            // checking if a file is formatted correctly
            if (load) {
                checkFile = true;
            } else {
                checkFile = false;
                std::cerr << "\nCANNOT LOAD GAME: file is not formatted correctly"
                        << std::endl;
            }
        }
    } else {
        checkFile = true;
    }
    return checkFile;
}

bool Menu::validateChoice(std::string choice, bool mode){

    bool check = true;
    bool alphabet = false;

    if (choice.size() > 1) {
        check = false;
        if ((choice[0] != ' ') && (choice[choice.size()-1] != ' ') && choice != "^D") {
            std::cerr << "\nINVALID INPUT: check input and try again"
                      << std::endl;
        }
    }
    if (choice[0] == ' ' || choice[choice.size()-1] == ' ') {
        check = false;
        std::cerr << "\nINVALID INPUT: input cannot have spaces"
                  << std::endl;
    }

    if (check == true) {
        for (int i = 0; i < 26; i++) {
            if (choice[0] == alphabets[i] || choice[0] == lowerAlphabets[i]) {
                alphabet = true;
                check = false;
            }
        }
        if (alphabet == true) {
            std::cerr << "\nINVALID INPUT: choice must only be an integer between 1 and 4"
                      << std::endl;
        } else {
            int temp = choice[0] - '0';

            if (mode == false) {
                if((temp < 1) || (temp > 4)){
                    check = false;
                    std::cerr << "\nINPUT OUT OF RANGE: choice must only be an integer between 1 and 4"
                            << std::endl;
                }
            } else {
                if ((temp < 1) || (temp > 2)) { 
                    check = false;
                    std::cerr << "\nINPUT OUT OF RANGE: choice must either be 1 or 2"
                            << std::endl;
                }
            }
        }
    }
    if (choice == "^D") {
        check = true;
    }
    return check;
}

void Menu::displayMenu(std::string choice){

    if (choice == START)
    {                                                        
        // std::cout << "  ______     ____    __    ____  __  .______      __  ___  __       _______     \n";
        // std::cout << " /  __  \\    \\   \\  /  \\  /   / |  | |   _  \\    |  |/  / |  |     |   ____|    \n";
        // std::cout << "|  |  |  |    \\   \\/    \\/   /  |  | |  |_)  |   |  '  /  |  |     |  |__       \n";
        // std::cout << "|  |  |  |     \\            /   |  | |      /    |    <   |  |     |   __|      \n";
        // std::cout << "|  `--'  '--.   \\    /\\    /    |  | |  |\\  \\----|  .  \\  |  `----.|  |____     \n";
        // std::cout << " \\_____\\_____\\   \\__/  \\__/     |__| | _| `._____|__|\\__\\ |_______||_______|    \n\n";

        
        std::cout << " .----------------. .----------------. .----------------. .----------------. .----------------. .----------------. .----------------. \n";
        std::cout << "| .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |\n";
        std::cout << "| |    ___       | | | _____  _____ | | |     _____    | | |  _______     | | |  ___  ____   | | |   _____      | | |  _________   | |\n";
        std::cout << "| |  .'   '.     | | ||_   _||_   _|| | |    |_   _|   | | | |_   __ \\    | | | |_  ||_  _|  | | |  |_   _|     | | | |_   ___  |  | |\n";
        std::cout << "| | /  .-.  \\    | | |  | | /\\ | |  | | |      | |     | | |   | |__) |   | | |   | |_/ /    | | |    | |       | | |   | |_  \\_|  | |\n";
        std::cout << "| | | |   | |    | | |  | |/  \\| |  | | |      | |     | | |   |  __ /    | | |   |  __'.    | | |    | |   _   | | |   |  _|  _   | |\n";
        std::cout << "| | \\  `-'  \\_   | | |  |   /\\   |  | | |     _| |_    | | |  _| |  \\ \\_  | | |  _| |  \\ \\_  | | |   _| |__/ |  | | |  _| |___/ |  | |\n";
        std::cout << "| |  `.___.\\__|  | | |  |__/  \\__|  | | |    |_____|   | | | |____| |___| | | | |____||____| | | |  |________|  | | | |_________|  | |\n";
        std::cout << "| |              | | |              | | |              | | |              | | |              | | |              | | |              | |\n";
        std::cout << "| '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |\n";
        std::cout << " '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' \n\n";
                                                                                                                                                                                                                                                                                   
        std::cout << "\nWelcome!\n";
        std::cout << "-------------------\n";
        std::cout << "Menu\n";
        std::cout << "----\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. Credits (Show student information) \n";
        std::cout << "4. Quit \n\n";

    } else if (choice == CREDITS) {

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

    } else if(choice == NEWGAME) {

        std::cout << "\nENTER '1' FOR 2 PLAYER MODE" << std::endl;
        std::cout << "ENTER '2' FOR 3 PLAYER MODE\n" << std::endl;

    } else if (choice == QUIT) {
        std::cout << "\nGoodbye" << std::endl;
    }
}
    
bool Menu::validatePlayerName (std::string name){

    bool check = true;
    if (name != "^D") {
        for (int i = 0; i < (int) name.length(); i++) {
            int charAsci = name[i];
            if (!((charAsci >= 65) && (charAsci <= 90)) && check == true) {
                check = false;
            } else if (charAsci == ' ') {
                check = false;
            }
        }
    } else {
        check = true;
    }

    if (check == false) {
        std::cerr << "\nOnly Letters in UPPERCASE WITHOUT SPACES are valid!\n"
                  << std::endl;
    }
    return check;
}
    
bool Menu::endGame(bool threePlayer){

    bool check = false;
    bool checkHand = false;

    // checks if one of player hands is empty
    if (threePlayer) {
        checkHand = engine->getPlayer1()->getPlayerHand()->getSize() == 0 ||
                    engine->getPlayer2()->getPlayerHand()->getSize() == 0 ||
                    engine->getPlayer3()->getPlayerHand()->getSize() == 0;

    } else {
        checkHand = engine->getPlayer1()->getPlayerHand()->getSize() == 0 ||
                    engine->getPlayer2()->getPlayerHand()->getSize() == 0;
    }
    
    // checking if both hand and tilebag are 0
    if (engine->tileBag->getBagSize() == 0 && checkHand) {
        check = true;
    }
    return check;
}
    
bool Menu::validateCommand(std::string command){

    bool checkCommand = true;

    //checker to ensure command length is valid
    bool checkLength = command.length() == 14 || command.length() == 10 ||
                        command.length() == 15;

    // checking for the save command
    std ::string save = command.substr(0, 5);
    bool isSave = false;
    if (save == "save ") {
        isSave = true;
    }

    //checker for checking spaces in command
    bool spaceCheck = false;
    //ensuring there are no spaces in the command
    if ((command[0] == ' ' || command[command.size()-1] == ' ')) {
        spaceCheck = true;
        checkCommand = false;
        std::cerr << "\nINVALID COMMAND: possible spelling/format error\n"
                    << "COMMANDS ALLOWED: place, replace, save, ^D"
                    << std::endl;
    }

    // checking if length exceeds expected number
    if (checkLength && (!spaceCheck) && !isSave) {
        
        // checkers for validating shape and colour
        bool foundColour = false ;
        bool foundShape = false;

        //checker for validating format
        bool formatError = false;     

        // checking the place command
        if ((command.length() == 14 || command.length() == 15) &&
            command[0] == 'p') {

            std::string tmp = command.substr(0, 6);

            if (tmp != "place ") {
                checkCommand = false;
                formatError = true;
            }

            tmp = command.substr(8, 4);
            if (tmp != " at ") {
                checkCommand = false;
                formatError = true;
            }

            if (checkCommand == true) { 
                //checking if colour and shape are valid
                for (int i = 0; i < 6; i++) {

                    if (command[6] == colours[i]) {
                        foundColour = true;
                    }
                    
                    int shape = command[7] - '0';
                    if (shape== shapes[i]) {
                        foundShape = true;
                    }
                }
            }
            
            //checking if row and column are valid
            bool foundcol = false;
            bool foundrow = false;
            //checking if a column is a letter
            bool colCheck = true;

            if (checkCommand == true) {
                
                for (int i = 0; i < 26; i++) {

                    if (command[12] == alphabets[i]) {
                        foundrow= true;
                    }
                    if (command[13] == alphabets[i]) {
                        colCheck = false;
                    }
                    if (command.length() == 15) {
                        if (command[14] == alphabets[i]) {
                            colCheck = false;
                        }
                    }
                }

                if (colCheck == true) {
                    int icol;
                    //extracting column from command
                    if (command.length() == 15) {
                        std ::string col = command.substr(13, 2);
                        icol = std::stoi(col);
                    } else {
                        icol = command[13] - '0';
                    }
                    if ((icol >=0)&&(icol <=25)) {
                        foundcol = true;
                    }
                }           
            }

            if (!(foundrow && foundcol)) {
                checkCommand = false;          
            }
            if (!(foundColour && foundShape)) {
                checkCommand = false;
            }

            if (formatError) {
                std::cerr << "\nCOMMAND CANNOT BE EXECUTED: check if the command has spelling errors/ extra spaces"
                          << std::endl;
            } else if ((!(foundColour && foundShape)) && (!(foundrow && foundcol))){
                std::cerr << "\nCOMMAND CANNOT BE EXECUTED: check if entered tile and entered coordinates are valid"
                          << std::endl;
            } else if (!(foundrow && foundcol)){
                std::cerr << "\nCOMMAND CANNOT BE EXECUTED: check if entered coordinates are valid"
                          << std::endl;
            } else if (!(foundColour && foundShape)){
                std::cerr << "\nCOMMAND CANNOT BE EXECUTED: check if entered tile is valid"
                          << std::endl;
            }

        } else if (command.length() == 10  && command[0] == 'r' && (!spaceCheck)) {

            // checking the replace command
            std ::string tmp = command.substr(0, 8);

            if (tmp != "replace ") {
                checkCommand = false;
            }

            for (int i = 0; i < 6; i++) {
                if (command[8] == colours[i]) {
                    foundColour = true;
                }
                int shape = command[9] - '0';
                if (shape == shapes[i]) {
                    foundShape = true;
                }
            }

            if (!(foundColour && foundShape)) {
                checkCommand = false;
                std::cerr << "\nCOMMAND CANNOT BE EXECUTED: check if entered tile is valid"
                          << std::endl;
            }

        } else {

            checkCommand = false;
            std::cerr << "\nINVALID COMMAND: possible spelling/format error\n"
                      << "COMMANDS ALLOWED: place, replace, save, ^D"
                      << std::endl;
        }

    } else if (isSave){
        checkCommand = true;
    } else if (command == "^D"){
        checkCommand = true;
    } else {
        if (!spaceCheck) {
            checkCommand = false;
            std::cerr << "\nINVALID COMMAND: possible spelling/format error\n"
                      << "COMMANDS ALLOWED: place, replace, save, ^D"
                      << std::endl;
        }
    }
    return checkCommand;
}