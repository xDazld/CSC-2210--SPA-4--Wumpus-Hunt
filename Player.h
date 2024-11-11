//
// Created by schreibert on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Network.h"

class Attack;
class Computer;
class Network;

class Player {
private:
    std::vector<Attack *> availableAttacks; // Attacks available to the player
    Computer *currentRoom;
    Network *network;

public:
    Player(Computer *startComputer, Network *network);

    void set_current_room(Computer *current_room) {
        this->currentRoom = current_room;
    }
    bool doMove(char command);
    bool doAttack(char command);
};

#endif // PLAYER_H
