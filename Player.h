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

    void aimAttack(char command, Direction direction);

    template <typename T>
    void doAttack(Computer &targetComputer) const {
        for (auto it = availableAttacks.begin(); it != availableAttacks.end(); ++it) {
            if (auto attack = dynamic_cast<T*>(*it)) {
                // Perform the Backdoor attack action here
                attack->doAttack(targetComputer);
                delete attack; // Optional: If managing memory dynamically
            }
        }
    }
};

#endif // PLAYER_H
