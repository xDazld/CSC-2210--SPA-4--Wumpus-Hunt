//
// Created by schreibert on 10/29/2024.
//

#ifndef NETWORK_H
#define NETWORK_H


#include <vector>
#include "Attack.h"
#include "Defense.h"

class Computer;

// Define the Network class as per the UML diagram
class Network {
private:
    Computer* rooms[7][7]; // 2D array of pointers to Computer objects representing rooms

public:
    // Scans the network starting from a specified computer
    void scan(Computer& current);
};

// Define the Computer class
class Computer {
private:
    std::vector<Defense*> defenses; // Vector of pointers to Defense objects
    std::vector<Attack*> loot;      // Vector of pointers to Attack objects
    bool compromised;

public:
    Computer() : compromised(false) {}

    // Function to enter a room and check if it's compromised
    bool enterRoom();
};



#endif //NETWORK_H
