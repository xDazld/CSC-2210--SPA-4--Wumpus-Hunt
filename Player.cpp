//
// Created by schreibert on 10/29/2024.
//

#include "Player.h"

#include "Controller.h"
#include "Network.h"

Player::Player(int startRow, int startCol, Network *network) 
  : row(startRow), col(startCol), currentRoom(network->getComputer(startRow, startCol)) {
    availableAttacks = {};
}
bool Player::doMove(char direction) {
  int newRow = row, newCol = col;
    switch (direction) {
        case 'N': newRow--; break; // Move north (up)
        case 'S': newRow++; break; // Move south (down)
        case 'E': newCol++; break; // Move east (right)
        case 'W': newCol--; break; // Move west (left)
    }

    // Check if the new position is within grid bounds
    if (newRow >= 0 && newRow < 6 && newCol >= 0 && newCol < 8) {
        // Move to the new room
        currentRoom = network->getComputer(newRow, newCol);
        row = newRow;
        col = newCol;
        std::cout << "Moved to new room at (" << row << ", " << col << ")" << std::endl;
        return true;
    } else {
        std::cout << "Cannot move in that direction!" << std::endl;
        return false; // Move failed due to out-of-bounds
    }
}

bool Player::aimAttack(char command, char direction) {
    int attackRow = row,  attackCol = col;
    switch (direction) {
        case 'N': attackRow--; break; // Move north (up)
        case 'S': attackRow++; break; // Move south (down)
        case 'E': attackCol++; break; // Move east (right)
        case 'W': attackCol--; break; // Move west (left)
    }
    if (attackRow >= 0 && attackRow < 6 && attackCol >= 0 && attackCol < 8) {
        Computer* targetComputer = network->getComputer(attackRow, attackCol);
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
    } else {
        std::cout << "Cannot Attack in that direction!" << std::endl;
        return false; // attack failed due to out-of-bounds
    }
}
