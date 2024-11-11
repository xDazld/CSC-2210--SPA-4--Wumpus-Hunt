//
// Created by schreibert on 10/29/2024.
//

#include "Player.h"
#include "Network.h"

Player::Player(int startRow, int startCol, Network *network) 
  : row(startRow), col(startCol), currentRoom(network->getComputer(startRow, startCol)) {
    std::vector<Attack *> availableAttacks;
}
bool Player::doMove(char command) {
// move from the current room to a neighboring room depedning on the direction
  return true;
}

bool Player::doAttack(char command) {
  return true;
}
