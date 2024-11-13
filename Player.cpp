//
// Created by schreibert on 10/29/2024.
//

#include "Player.h"
#include "Controller.h"
#include "Network.h"

Player::Player(Computer *startComputer, Network *network)
    : currentRoom(startComputer),
      network(network) {
    for (int i = 0; i < 5; i++) {
        availableAttacks.push_back(new EmailSpoof());
    }
    for (int i = 0; i < 5; i++) {
        availableAttacks.push_back(new XSS());
    }
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
    } else {
        if (newPosition->getCompromised() && newPosition->getIcon()!='!') {
            currentRoom->setIcon(currentRoomIcon);
            currentRoom = newPosition;
            currentRoomIcon = currentRoom->getIcon();
            currentRoom->setIcon('+');
            addItem(currentRoom->get_loot());
            std::cout << "Moved to new computer." << std::endl;
        } else if (newPosition->getIcon()=='!') {
            bool loseGame = true;
            return loseGame;
        } else {
            std::cerr << "Unable to move to that computer, not compromised." << std::endl;
        }
    }
    return false;
}

void Player::addItem(vector<Attack *> loot) {
    for (const auto* item : loot) {
        std::cout << "You found a " << item->get_name() << " attack." << std::endl;
    }
    availableAttacks.insert(availableAttacks.end(), loot.begin(), loot.end());
}

bool Player::aimAttack(const char command, const char direction) {
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
            bool success = false;
            switch (command) {
                case Controller::BACKDOOR:
                    success = doAttack<Backdoor>(*targetComputer);
                    break;
                case Controller::IP_SPOOF:
                    success = doAttack<IPSpoof>(*targetComputer);
                    break;

                case Controller::KEY: {
                    success = doAttack<DatabaseEncryptionKey>(*targetComputer);
                    if (success) {
                        return true;
                    }
                }
                case Controller::TROJAN:
                    success = doAttack<TrojanHorse>(*targetComputer);
                    break;

                case Controller::EMAIL_SPOOF:
                    success = doAttack<EmailSpoof>(*targetComputer);
                    break;

                case Controller::XSS:
                    success = doAttack<XSS>(*targetComputer);
                    break;

                default: {
                    cerr << "Invalid attack type." << endl;
                };
            }
            if (success) {
                cout << "Target compromised." << endl;
            } else {
                cout << "Attack failed." << endl;
            }
        }
    } else {
        std::cerr << "Attack not available." << std::endl;
    }
    return false;
}

bool Player::isAttackAvailable(const char attackType) {
    Controller::ATTACKS type = {};
    switch (attackType) {
        case 'I':
            type = Controller::IP_SPOOF;
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
        case 'E':
            type = Controller::EMAIL_SPOOF;
            break;
        case 'X':
            type = Controller::XSS;
            break;
        default:
            cerr << "Invalid attack" << endl;
    }
    for (const auto &attack: availableAttacks) {
        switch (type) {
            case Controller::IP_SPOOF:
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
            case Controller::EMAIL_SPOOF:
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
        std::cout << "Above: ";
        if (neighbor->get_defenses().empty()) {
            for (const auto &defense: neighbor->get_defenses()) {
                std::cout << defense->get_name() << ' ';
            }
            for (const auto &service: neighbor->get_services()) {
                std::cout << service->get_port() << ' ';
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
                std::cout << service->get_port() << ' ';
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
                std::cout << service->get_port() << ' ';
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
                std::cout << service->get_port() << ' ';
            }
            std::cout << std::endl;
        } else {
            for (Defense *defense: neighbor->get_defenses()) {
                std::cout << defense->get_message() << std::endl;
            }
        }
    }
}

template<typename T>
bool Player::doAttack(Computer &targetComputer) {
    // Instantiate the specific attack type (e.g., Backdoor)
    Attack *attack = new T();
    for (auto it = availableAttacks.begin(); it != availableAttacks.end(); ++it) {
        if ((*it)->get_name() == attack->get_name()) {
            // Perform the attack action
            bool success = attack->doAttack(targetComputer);
            delete attack; // Clean up dynamically created attack instance

            if (success) {
                // Update the target computer's state
                targetComputer.setCompromised(true);
                targetComputer.setIcon('Z');

                // Remove the used attack from availableAttacks
                delete *it;              // Free memory for the attack object
                availableAttacks.erase(it); // Remove the pointer from the vector
            }
            return success;
        }
    }
    delete attack; // Clean up if the attack was not found or not successful
    return false;
}

Player::~Player() {
    for (const Attack *attack: availableAttacks) {
        delete attack;
    }
}
