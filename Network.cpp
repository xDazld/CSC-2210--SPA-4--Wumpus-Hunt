//
// Created by schreibert on 10/29/2024.
//

#include "Network.h"

#include <iostream>

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
            if (char const icon = this->layout[index]; icon != '#' and icon != ' ') {
                j = new Computer(icon);
            } else if (icon == '#') {
                j = new WumpDB();
            }
            ++index;
        }
    }
    rooms[0][0]->setCompromised(true);
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 8; col++) {
            if (Computer *room = rooms[row][col]; room != nullptr) {
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
                if (room->getIcon()=='.') {
                    room->setCompromised(true);
                }
            }
        }
    }
}


// Overload the << operator to print the network map based on layout
std::ostream &operator<<(std::ostream &os, const Network &network) {
    os << "Network Map:" << std::endl;

    for (auto &room: network.rooms) {
        for (auto &j: room) {
            char icon = ' ';
            if (j != nullptr) {
                icon = j->getIcon();
            }
            os << icon << ' ';
        }
        os << std::endl;
    }
    return os;
}

Computer *Network::getStart() const {
    return rooms[0][0];
}

WumpDB::WumpDB(): Computer('#') {
    addService(new SQLServer());
    addDefense(new Antivirus());
    addDefense(new Firewall());
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
