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

/**
 * The Player class is responsible for managing the player's actions and inventory.
 */
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
    void doMove(char command);

    void aimAttack(char command, char direction);

    bool isAttackAvailable(char attackType);

    void scan() const;

    void addItem(std::vector<Attack *> attack);

    template <typename T>
    void doAttack(Computer &targetComputer) const {
        for (auto availableAttack: availableAttacks) {
            if (auto attack = dynamic_cast<T *>(availableAttack)) {
                // Perform the Backdoor attack action here
                attack->doAttack(targetComputer);
                delete attack; // Optional: If managing memory dynamically
            }
        }
    }
};

#endif // PLAYER_H
