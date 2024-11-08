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

bool IPSpoof::doAttack(Computer &target) {
    Defense *dummy_firewall = new Firewall();
    const size_t removed_count = target.get_defenses().remove(dummy_firewall);
    delete dummy_firewall;
    return removed_count != 0;
}

bool TrojanHorse::doAttack(Computer &target) {
    Defense *dummy_antivirus = new Firewall();
    const size_t removed_count = target.get_defenses().remove(dummy_antivirus);
    delete dummy_antivirus;
    return removed_count != 0;
}


bool DatabaseEncryptionKey::doAttack(Computer &target) {
    return false;
}

void Attack::download(Player *player) {
    this->player = player;
}

bool XSS::doAttack(Computer &target) {
    return false;
}

bool EmailSpoof::doAttack(Computer &target) {
    return false;
}
