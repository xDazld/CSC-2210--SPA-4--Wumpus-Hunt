//
// Created by schreibert on 10/29/2024.
//

#include "Player.h"
#include "Network.h"

Player::Player(Computer *startComputer, Network *network)
    : currentRoom(startComputer),
      network(network) {
    std::vector<Attack *> availableAttacks;
}

bool Player::doMove(const char command) {
    Direction move_direction = {};
    switch (command) {
        case 'N':
            move_direction = NORTH;
            break;
        case 'S':
            move_direction = SOUTH;
            break;
        case 'E':
            move_direction = EAST;
            break;
        case 'W':
            move_direction = WEST;
            break;
        default:
            std::cerr << "Invalid move direction.";
    }
    if (Computer *newPosition = currentRoom->getNeighbor(move_direction);
        newPosition == nullptr) {
        std::cerr << "No connection in that direction" << std::endl;
        return false;
    } else {
        currentRoom = newPosition;
        std::cout << "Moved to new computer." << std::endl;
        return true;
    }
}

bool Player::doAttack(char command) {
    //todo implement attack
    return true;
}
