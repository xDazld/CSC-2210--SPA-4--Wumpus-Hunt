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

    bool aimAttack(char command, char direction);

    bool isAttackAvailable(char attackType);

    void scan() const;

    void addItem(std::vector<Attack *> attack);

    template <typename T>
    bool doAttack(Computer &targetComputer) const {
        Attack *attack = new T();
        for (const auto availableAttack: availableAttacks) {
            if (availableAttack->get_name() == attack->get_name()) {
                // Perform the Backdoor attack action here
                const bool success = attack->doAttack(targetComputer);
                delete attack; // Optional: If managing memory dynamically
                if (success) {
                    targetComputer.setCompromised(true);
                    targetComputer.setIcon('Z');
                }
                return success;
            }
        }
        return false;
    }

    ~Player();
};

#endif // PLAYER_H
