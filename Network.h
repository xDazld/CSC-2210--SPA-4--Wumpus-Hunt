//
// Created by schreibert on 10/29/2024.
//

#ifndef NETWORK_H
#define NETWORK_H


#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "Attack.h"
#include "Defense.h"
#include "service.h"

class Computer;
class Attack;

enum Direction { NORTH, SOUTH, EAST, WEST };

class Network {
private:
    Computer *rooms[6][8]{}; // 2D array of pointers to Computer objects representing rooms
    std::string layout; // Store layout string

public:
    // Constructor to initialize the network
    explicit Network(std::string layout);

    // Overload the << operator to print the network
    friend std::ostream &operator<<(std::ostream &os, const Network &network);

    [[nodiscard]] Computer *getStart() const;

    ~Network();
};

class Computer {
private:
    std::list<Defense *> defenses; // Vector of pointers to Defense objects
    std::vector<Attack *> loot; // Vector of pointers to Attack objects
    bool compromised = false;
    const char icon;
    std::vector<Service *> services;
    std::map<Direction, Computer *> neighbors;

public:
    explicit Computer(char icon);

    // Add/Set service to the computer
    void addService(Service *service) { services.push_back(service); }

    // Get services
    [[nodiscard]] std::vector<Service *> &get_services() { return services; }

    // Add/Set defense to the computer
    void addDefense(Defense *defense) { defenses.push_back(defense); }

    // Add/Set attack to the computer
    void addAttack(Attack *attack) { loot.push_back(attack); }

    // Get defenses
    [[nodiscard]] std::list<Defense *> &get_defenses() { return defenses; }

    // Get loot
    [[nodiscard]] std::vector<Attack *> &get_loot() { return loot; };

    // Get icon.
    [[nodiscard]] char getIcon() const { return icon; }

    // Set the compromised state
    void setCompromised(const bool state) { compromised = state; }

    // Get the compromised state
    [[nodiscard]] bool getCompromised() const { return compromised; }

    // Overload the << operator for Computer to show its status
    friend std::ostream &operator<<(std::ostream &os, const Computer &computer);

    void setNeighbor(const Direction direction, Computer *neighbor) {
        neighbors[direction] = neighbor;
    }

    Computer *getNeighbor(const Direction direction) {
        return neighbors[direction];
    }

    ~Computer();
};

std::ostream &operator<<(std::ostream &os, const Network &network);

std::ostream &operator<<(std::ostream &os, const Computer &computer);

#endif //NETWORK_H
