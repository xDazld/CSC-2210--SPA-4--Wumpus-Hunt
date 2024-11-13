//
// Created by schreibert on 10/29/2024.
//

#include "Attack.h"

#include <algorithm>

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
    auto &defenses = target.get_defenses();  // Get reference to defenses vector

    // Find the firewall defense in the vector
    auto it = std::find_if(defenses.begin(), defenses.end(),
        [](Defense* defense) { return dynamic_cast<Firewall*>(defense) != nullptr; });

    if (it != defenses.end()) {
        // Found a firewall defense, now erase it
        delete *it;  // Free memory of the removed defense
        defenses.erase(it);  // Remove the pointer from the vector
        return true;  // Successfully removed
    }
    return false;  // No firewall found
}

bool TrojanHorse::doAttack(Computer &target) {
    auto &defenses = target.get_defenses();  // Get reference to defenses vector

    // Find the firewall defense in the vector
    auto it = std::find_if(defenses.begin(), defenses.end(),
        [](Defense* defense) { return dynamic_cast<Antivirus*>(defense) != nullptr; });

    if (it != defenses.end()) {
        // Found a firewall defense, now erase it
        delete *it;  // Free memory of the removed defense
        defenses.erase(it);  // Remove the pointer from the vector
        return true;  // Successfully removed
    }
    return false;  // No firewall found
}


bool DatabaseEncryptionKey::doAttack(Computer &target) {
    for (const Service *service: target.get_services()) {
        if (service->get_name() == "SQL") {
            target.setCompromised(true);
            return true;
        }
    }
    return false;
}

void Attack::download(Player *player) {
    this->player = player;
}

bool XSS::doAttack(Computer &target) {
    for (const Service *service: target.get_services()) {
        if (service->get_name() == "HTTP") {
            target.setCompromised(true);
            return true;
        }
    }
    return false;
}

bool EmailSpoof::doAttack(Computer &target) {
    for (const Service *service: target.get_services()) {
        if (service->get_name() == "Email") {
            target.setCompromised(true);
            return true;
        }
    }
    return false;
}
