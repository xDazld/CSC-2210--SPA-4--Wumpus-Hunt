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

void Player::doMove(const char command) {
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
        if (newPosition->getCompromised()) {
            currentRoom = newPosition;
            std::cout << "Moved to new computer." << std::endl;
            return true;
        }
        std::cerr << "Unable to move to that computer, not compromised." << std::endl;
        return false;
    }
    addItem(currentRoom->get_loot());
}

void Player::aimAttack(const char command, const char direction) {
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
                default: ;
            }
        }
    } else {
        std::cerr << "Attack not available." << std::endl;
    }
}

bool Player::isAttackAvailable(const char attackType) {
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
        case 'T':
            type = Controller::TROJAN;
            break;
        case 'P':
            type = Controller::PHISH;
            break;
        case 'X':
            type = Controller::XSS;
            break;
        default: ;
    }
    for (const auto &attack: availableAttacks) {
        switch (type) {
            case Controller::CODE:
                if (dynamic_cast<IPSpoof *>(attack)) return true;
                break;
            case Controller::BACKDOOR:
                if (dynamic_cast<Backdoor *>(attack)) return true;
                break;
            case Controller::KEY:
                if (dynamic_cast<DatabaseEncryptionKey *>(attack)) return true;
                break;
            case Controller::TROJAN:
                if (dynamic_cast<TrojanHorse *>(attack)) return true;
                break;
            case Controller::PHISH:
                if (dynamic_cast<EmailSpoof *>(attack)) return true;
                break;
            case Controller::XSS:
                if (dynamic_cast<XSS *>(attack)) return true;
                break;
        }
    }
    return false;
}


// Method to scan adjacent computers for defenses
void Player::scan() const {
    // Check for defenses in computers above, below, to the left, and to the right
    std::cout << "Scanning for defenses and services in adjacent computers..." << std::endl;
    // Output all the defenses and attacks in the computers above, below, to the left, and to the right
    if (Computer *neighbor = currentRoom->getNeighbor(NORTH); neighbor != nullptr) {
        if (neighbor->get_defenses().empty()) {
            std::cout << "Above: ";
            for (const auto &defense: neighbor->get_defenses()) {
                std::cout << defense->get_name() << ' ';
            }
            for (const auto &service: neighbor->get_services()) {
                std::cout << service->get_name() << ' ';
            }
            std::cout << std::endl;
        } else {
            for (Defense *defense: neighbor->get_defenses()) {
                std::cout << defense->get_message() << std::endl;
            }
        }
    }
    if (Computer *neighbor = currentRoom->getNeighbor(SOUTH); neighbor != nullptr) {
        std::cout << "Below: ";
        if (neighbor->get_defenses().empty()) {
            for (const auto &defense: neighbor->get_defenses()) {
                std::cout << defense->get_name() << ' ';
            }
            for (const auto &service: neighbor->get_services()) {
                std::cout << service->get_name() << ' ';
            }
            std::cout << std::endl;
        } else {
            for (Defense *defense: neighbor->get_defenses()) {
                std::cout << defense->get_message() << std::endl;
            }
        }
    }
    if (Computer *neighbor = currentRoom->getNeighbor(WEST); neighbor != nullptr) {
        std::cout << "Left: ";
        if (neighbor->get_defenses().empty()) {
            for (const auto &defense: neighbor->get_defenses()) {
                std::cout << defense->get_name() << ' ';
            }
            for (const auto &service: neighbor->get_services()) {
                std::cout << service->get_name() << ' ';
            }
            std::cout << std::endl;
        } else {
            for (Defense *defense: neighbor->get_defenses()) {
                std::cout << defense->get_message() << std::endl;
            }
        }
    }
    if (Computer *neighbor = currentRoom->getNeighbor(EAST); neighbor != nullptr) {
        std::cout << "Right: ";
        if (neighbor->get_defenses().empty()) {
            for (const auto &defense: neighbor->get_defenses()) {
                std::cout << defense->get_name() << ' ';
            }
            for (const auto &service: neighbor->get_services()) {
                std::cout << service->get_name() << ' ';
            }
            std::cout << std::endl;
        } else {
            for (Defense *defense: neighbor->get_defenses()) {
                std::cout << defense->get_message() << std::endl;
            }
        }
    }
}

void Player::addItem(std::vector<Attack *> attack) {
    availableAttacks.insert(availableAttacks.end(), attack.begin(), attack.end());
}
