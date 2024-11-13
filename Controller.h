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
    string createLayout();

    Controller(); // Constructor to initialize messages
    void startGame();

    [[nodiscard]] bool doTurn(char command) const;

    void showNetwork() const;

    void showHelp();

    void showActions();

    static bool isMove(char command);

    static bool isAttack(char command);

    static bool isMenu(char command);

    static bool isValidCommand(char command);

    ~Controller();

    enum DIRECTIONS {
        NORTH = 'N', SOUTH = 'S', EAST = 'E', WEST = 'W'
    };

    enum ATTACKS {
        BACKDOOR = 'B', IP_SPOOF = 'I',TROJAN = 'T', KEY = 'K' , XSS = 'X', EMAIL_SPOOF = 'E'
    };

    enum MENU {
        HELP = 'H', MAP = 'M', QUIT = 'Q', ATTACK = 'A'
    };
};

#endif // CONTROLLER_H
