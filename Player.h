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

    void set_current_room(Computer *current_room);

    bool doMove(char command);

    void addItem(std::vector<Attack *> loot);

    bool aimAttack(char command, char direction);

    bool isAttackAvailable(char attackType);

    void scan() const;

    template <typename T>
    bool doAttack(Computer &targetComputer);

    std::vector<Attack *> getAvailableAttacks() const { return availableAttacks; }

    ~Player();
};

#endif // PLAYER_H
