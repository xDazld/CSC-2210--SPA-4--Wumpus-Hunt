//
// Created by schreibert on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Network.h"

class Attack;
class Computer;

class Player {
private:
    int row, col;
    std::vector<Attack *> availableAttacks; // Attacks available to the player
    Computer *currentRoom;
    Network *network;

public:
    Player(int startRow, int startCol, Network *network);
    void set_current_room(Computer *current_room) {
        this->currentRoom = current_room;
    }
    bool doMove(char command);
    bool aimAttack(char command, char direction);

    template <typename T>
    bool hasAttackOfType() const {
        if (availableAttacks.empty()) {
            return false; // No attacks available
        }
        for (auto *attack : availableAttacks) {
            if (dynamic_cast<T *>(attack) != nullptr) {
                return true; // Found an attack of the specified type
            }
        }
        return false; // No attack of the specified type found
    }
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
