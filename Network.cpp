//
// Created by schreibert on 10/29/2024.
//

#include "Network.h"

#include <iostream>
#include <utility>

void initializeNetwork(Network *network) {}

// TODO: Parse layout string and initialize rooms based on it
// Constructor to initialize the network and store layout
Network::Network(std::string  layout) : layout(std::move(layout)) {
    for (auto & room : rooms) {
        for (auto & j : room) {
            j = new Computer();
        }
    }
}

// Overload the << operator to print the network map based on layout
std::ostream& operator<<(std::ostream& os, const Network& network) {
    os << "Network Map:\n";
    int index = 0;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (index < network.layout.length()) {
                os << network.layout[index] << ' ';
            } else {
                os << "[ ] ";
            }
            ++index;
        }
        os << '\n';
    }
    return os;
}