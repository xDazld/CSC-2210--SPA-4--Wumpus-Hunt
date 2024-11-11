//
// Created by schreibert on 10/29/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>

#include "Network.h"
#include "Player.h"
using namespace std;

class Controller {
    private:
        std::map<std::string, std::string> messages;
        Network* network;
        Player* player;

    public:
        Controller(); // Constructor to initialize messages
        void startGame();
        bool doTurn(char command);
        void showNetwork();
        void showHelp();
        void showError();
        void showActions();
        bool isMove(char command);
        bool isAttack(char command);
        bool isMenu(char command);
        bool isValidCommand(const char command);
        string createLayout();
        ~Controller();

        enum DIRECTIONS {
            NORTH = 'N', SOUTH = 'S', EAST = 'E', WEST = 'W'
        };
        enum ATTACKS {
            CODE = 'C', BACKDOOR = 'B', KEY = 'K'
        };
        enum MENU {
            HELP = 'H', MAP = 'M', QUIT = 'Q'
        };
};

#endif // CONTROLLER_H

