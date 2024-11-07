//
// Created by schreibert on 10/29/2024.
//

#ifndef NETWORK_H
#define NETWORK_H


#include <iostream>
#include <list>
#include <vector>
#include "Attack.h"
#include "Defense.h"

class Computer;
class Attack;

class Network {
private:
    Computer *rooms[6][8]{}; // 2D array of pointers to Computer objects representing rooms
    std::string layout;    // Store layout string

public:
    // Constructor to initialize the network
    Network(std::string layout);

    // Method to print the map of the network
    void map() const;

    // Overload the << operator to print the network
    friend std::ostream& operator<<(std::ostream& os, const Network& network);
};

class Computer {
private:
    std::list<Defense *> defenses; // Vector of pointers to Defense objects
    std::vector<Attack*> loot;      // Vector of pointers to Attack objects
    bool compromised{};

public:
    Computer() = default;

    // Function to enter a room and check if it's compromised
    bool enterRoom();

    // Set the compromised state
    void setCompromised(bool state) { compromised = state; }

    // Check if the computer is compromised
    [[nodiscard]] bool isCompromised() const { return compromised; }

    // Overload the << operator for Computer to show its status
    friend std::ostream& operator<<(std::ostream& os, const Computer& computer);

    [[nodiscard]] std::list<Defense *> &get_defenses() {
        return defenses;
    }
};

std::ostream& operator<<(std::ostream& os, const Network& network);
std::ostream& operator<<(std::ostream& os, const Computer& computer);

#endif //NETWORK_H
