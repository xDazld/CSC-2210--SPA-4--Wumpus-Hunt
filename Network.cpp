//
// Created by schreibert on 10/29/2024.
//

#include "Network.h"

#include <iostream>

void initializeNetwork(Network *network) {}

// TODO: Parse layout string and initialize rooms based on it
// Constructor to initialize the network and store layout
Network::Network(std::string  layout) : layout(std::move(layout)) {
    int index = 0;
    for (auto & room : rooms) {
        for (auto & j : room) {
            char const icon = this->layout[index]; // Casting to char because it's a string
            j = new Computer(icon);
            j->setCompromised(false);
            ++index;
        }
    }
}



// Overload the << operator to print the network map based on layout
std::ostream& operator<<(std::ostream& os, const Network& network) {
    os << "Network Map:\n";

    for (auto & room : network.rooms) {
        for (auto & j : room) {
            os << j->getIcon() << ' ';
        }
        os << '\n';
    }
    return os;
}