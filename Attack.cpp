//
// Created by schreibert on 10/29/2024.
//

#include "Attack.h"

bool Backdoor::doAttack(Computer &target) {
    if (location == nullptr) {
        location = &target;
    } else {
        player->set_current_room(location);
        std::cout << "You returned to a previously compromised computer";
    }
    return true;
}

bool Spoof::doAttack(Computer &target) {
    return false;
}

bool DatabaseEncryptionKey::doAttack(Computer &target) {
    return false;
}

void Attack::download(Player *player) {
    this->player = player;
}
