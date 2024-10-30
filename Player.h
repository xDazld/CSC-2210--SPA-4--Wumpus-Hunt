//
// Created by schreibert on 10/29/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Attack.h"

class Player {
private:
  std::vector<Attack*> availableAttacks; // Attacks available to the player
};

#endif // PLAYER_H

