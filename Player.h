//
// Created by schreibert on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Attack.h"
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
    char currentRoomIcon = '.';

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
    bool doAttack(Computer &targetComputer) const;

    std::vector<Attack *> getAvailableAttacks() const { return availableAttacks; }

    ~Player();
};

#endif // PLAYER_H
