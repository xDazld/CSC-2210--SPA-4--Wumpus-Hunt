//
// Created by schreibert on 10/29/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>

#include "Player.h"
using namespace std;

class Network;
class Player;

/**
 * The Controller class is responsible for managing the game.
 */
class Controller {
private:
    std::map<std::string, std::string> messages;
    Network *network;
    Player *player;

public:
    Controller(); // Constructor to initialize messages
    void startGame();

    void doTurn(char command) const;

    void showNetwork() const;

    void showHelp();

    void showActions();

    static bool isMove(char command);

    static bool isAttack(char command);

    static bool isMenu(char command);

    static bool isValidCommand(char command);

    string createLayout();

    ~Controller();

    enum DIRECTIONS {
        NORTH = 'N', SOUTH = 'S', EAST = 'E', WEST = 'W'
    };

    enum ATTACKS {
        CODE = 'A', BACKDOOR = 'B', KEY = 'K', TROJAN = 'T', PHISH = 'P', XSS = 'X'
    };

    enum MENU {
        HELP = 'H', MAP = 'M', QUIT = 'Q'
    };
};

#endif // CONTROLLER_H
