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
#include "service.h"

class Computer;
class Attack;

class Network {
private:
    Computer *rooms[6][8]{}; // 2D array of pointers to Computer objects representing rooms
    std::string layout; // Store layout string

public:
    // Constructor to initialize the network
    Network();

    // Method to get the computer at a specific location
    [[nodiscard]] Computer *getComputer(int row, int col) const { return rooms[row][col]; }

    // Method to scan adjacent computers for defenses
    void scan(const Computer *computer) const;

    // Overload the << operator to print the network
    friend std::ostream& operator<<(std::ostream& os, const Network& network);

    ~Network();
};

class Computer {
private:
    std::list<Defense *> defenses; // Vector of pointers to Defense objects
    std::vector<Attack *> loot; // Vector of pointers to Attack objects
    bool compromised{};
    const char icon;
    std::vector<Service *> services;

public:
    explicit Computer(const char icon) : icon(icon) {};

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
    [[nodiscard]] std::vector<Attack *> &get_loot() { return loot;};

    // Get icon.
    [[nodiscard]] char getIcon() const { return icon; }

    // Set the compromised state
    void setCompromised(const bool state) { compromised = state; }

    // Get the compromised state
    [[nodiscard]] bool getCompromised() const { return compromised; }

    // Overload the << operator for Computer to show its status
    friend std::ostream& operator<<(std::ostream& os, const Computer& computer);

    ~Computer();
};

std::ostream& operator<<(std::ostream& os, const Network& network);
std::ostream& operator<<(std::ostream& os, const Computer& computer);

#endif //NETWORK_H
