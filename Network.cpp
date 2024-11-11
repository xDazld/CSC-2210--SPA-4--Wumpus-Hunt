//
// Created by schreibert on 10/29/2024.
//

#include "Network.h"

#include <iostream>

#include "WumpDB.h"

Computer::Computer(const char icon) : icon(icon) {
    // Add services to the computer
    switch (rand() % 2) {
        case 0:
            addService(new HTTPServer());
            break;
        case 1:
            addService(new EmailServer());
            break;
        default: ;
    }

    // Add attack to the computer
    if (icon == '?') {
        switch (rand() % 6) {
            case 0:
                addAttack(new Backdoor());
                break;
            case 1:
                addAttack(new IPSpoof());
                break;
            case 2:
                addAttack(new TrojanHorse());
                break;
            case 3:
                addAttack(new DatabaseEncryptionKey());
                break;
            case 4:
                addAttack(new XSS());
                break;
            case 5:
                addAttack(new EmailSpoof());
                break;
            default: ;
        }
    }

    // Add defense to the computer
    if (icon == '!') {
        addDefense(new Antivirus());
    }
    if (icon == '@') {
        addDefense(new Firewall());
    }
}

// Constructor to initialize the network and store layout
Network::Network(std::string layout) : layout(std::move(layout)) {
    int index = 0;
    for (auto &room: rooms) {
        for (auto &j: room) {
            char const icon = this->layout[index]; // Casting to char because it's a string
            if (icon != '#') {
                j = new Computer(icon);
            } else {
                j = new WumpDB();
            }
            ++index;
        }
    }
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            Computer *room = rooms[row][col];
            if (col > 0) {
                room->setNeighbor(WEST, rooms[row][col - 1]);
            }
            if (col < 7) {
                room->setNeighbor(EAST, rooms[row][col + 1]);
            }
            if (row > 0) {
                room->setNeighbor(NORTH, rooms[row - 1][col]);
            }
            if (row < 5) {
                room->setNeighbor(SOUTH, rooms[row + 1][col]);
            }
        }
    }
}

// Method to scan adjacent computers for defenses
void Network::scan(Computer *computer) {
    // Check for defenses in computers above, below, to the left, and to the right
    std::cout << "Scanning for defenses and services in adjacent computers..." << std::endl;
    // Output all the defenses and attacks in the computers above, below, to the left, and to the right
    if (Computer *neighbor = computer->getNeighbor(NORTH); neighbor != nullptr) {
        std::cout << "Above: ";
        for (const auto &defense: neighbor->get_defenses()) {
            std::cout << defense->get_name() << ' ';
        }
        for (const auto &service: neighbor->get_services()) {
            std::cout << service->get_name() << ' ';
        }
        std::cout << std::endl;
    }
    if (Computer *neighbor = computer->getNeighbor(SOUTH); neighbor != nullptr) {
        std::cout << "Below: ";
        for (const auto &defense: neighbor->get_defenses()) {
            std::cout << defense->get_name() << ' ';
        }
        for (const auto &service: neighbor->get_services()) {
            std::cout << service->get_name() << ' ';
        }
        std::cout << std::endl;
    }
    if (Computer *neighbor = computer->getNeighbor(WEST); neighbor != nullptr) {
        std::cout << "Left: ";
        for (const auto &defense: neighbor->get_defenses()) {
            std::cout << defense->get_name() << ' ';
        }
        for (const auto &service: neighbor->get_services()) {
            std::cout << service->get_name() << ' ';
        }
        std::cout << std::endl;
    }
    if (Computer *neighbor = computer->getNeighbor(EAST); neighbor != nullptr) {
        std::cout << "Right: ";
        for (const auto &defense: neighbor->get_defenses()) {
            std::cout << defense->get_name() << ' ';
        }
        for (const auto &service: neighbor->get_services()) {
            std::cout << service->get_name() << ' ';
        }
        std::cout << std::endl;
    }
}


// Overload the << operator to print the network map based on layout
std::ostream &operator<<(std::ostream &os, const Network &network) {
    os << "Network Map:" << std::endl;

    for (auto &room: network.rooms) {
        for (auto &j: room) {
            os << j->getIcon() << ' ';
        }
        os << std::endl;
    }
    return os;
}

Computer *Network::getStart() const {
    return rooms[0][0];
}

Network::~Network() {
    for (auto &room: rooms) {
        for (const auto &j: room) {
            delete j;
        }
    }
}

Computer::~Computer() {
    for (const Defense *defense: defenses) {
        delete defense;
    }
    for (const Attack *attack: loot) {
        delete attack;
    }
    for (const Service *service: services) {
        delete service;
    }
}
