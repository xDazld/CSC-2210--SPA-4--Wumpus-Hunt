//
// Created by schreibert on 10/29/2024.
//

#include "Player.h"
#include "Controller.h"
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

void Player::aimAttack(char command, char direction) {
    if (isAttackAvailable(command)) {
        Direction attackDirection = {};
        switch (direction) {
            case 'N':
                attackDirection = NORTH;
            break;
            case 'S':
                attackDirection = SOUTH;
            break;
            case 'E':
                attackDirection = EAST;
            break;
            case 'W':
                attackDirection = WEST;
            break;
            default:
                std::cerr << "Invalid input.";
        }
        if (Computer *targetComputer = currentRoom->getNeighbor(attackDirection);
            targetComputer == nullptr) {
            std::cerr << "No connection found to attack" << std::endl;
            } else {
                switch (command) {
                    case Controller::BACKDOOR: {
                        doAttack<Backdoor>(*targetComputer);
                    }
                    case Controller::CODE: {
                        doAttack<IPSpoof>(*targetComputer);
                    }
                    case Controller::KEY: {
                        doAttack<DatabaseEncryptionKey>(*targetComputer);
                    }
                }
            }
    } else {
        std::cerr << "Attack not available." << std::endl;
    }
}

bool Player::isAttackAvailable(char attackType) {
    Controller::ATTACKS type = {};
    switch (attackType) {
        case 'A':
            type = Controller::CODE;
        break;
        case 'B':
            type = Controller::BACKDOOR;
        break;
        case 'K':
            type = Controller::KEY;
        break;
    }
    for (const auto& attack : availableAttacks) {
        switch (type) {
            case Controller::CODE:
                if (dynamic_cast<IPSpoof*>(attack)) return true;
            break;
            case Controller::BACKDOOR:
                if (dynamic_cast<Backdoor*>(attack)) return true;
            break;
            case Controller::KEY:
                if (dynamic_cast<DatabaseEncryptionKey*>(attack)) return true;
            break;
        }
    }
    return false;
}
