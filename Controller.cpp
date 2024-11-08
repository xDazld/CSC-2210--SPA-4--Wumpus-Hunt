//
// Created by schreibert on 10/29/2024.
//

#include "Controller.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Constructor to initialize messages
Controller::Controller()
    : network(".?...@..@!.?..?.?..  .?.?..  ?...!..@#..+??.!..@"),
    player() {
        // Initialize player
        // Store the help text in the messages map
        messages["start"] = R"(
Welcome to "Hack the WumpDB" The WumpDB is in a network of computers, each with 1-4 connections.
Move through the network to locate the WumpDB. Hazards include Antivirus, which detects unauthorized
access and removes you from the network, and Firewalls, which block spoof attacks and clear nearby hazards.
Your goal is to reach the WumpDB without getting blacklisted. Each turn, you can move one connection or
attack in a direction to open a path. You can find tools: the Encryption Key bypasses the WumpDB
blacklist for access, Spoofing Code removes firewalls or antivirus on nearby computers, and Backdoors
allow you to return to the location you discovered them when used. You are constantly scanning, messages
from the scans will indicate proximity to targets: "Database admin tool detected" (WumpDB nearby),
"Unauthorized activity detected" (Antivirus nearby), and "Connected device unresponsive to scans" (Firewall nearby).
)";
        messages["help"] = R"(
There are 2 Defenses:
    Antivirus (Unauthorized activity detected)
    Firewall (Connected device unresponsive to scans)
You cannot enter the WumpDB without a key.
You need to find spoof codes in the network.
Spoof codes can remove firewalls and antivirus from computers.
Backdoors can bring you back to a previous location.
The Firewall will take your spoof codes.
The antivirus will kick you out of the network.
)";
    }

void Controller::startGame() {
    cout << messages["start"] << endl;

    char command;
    bool gameRunning = true;

    while (gameRunning) {
        cout << "Action: N)orth, S)outh, E)ast, W)est, C)ode, B)ackdoor, K)ey, H)elp, M)ap, Q)uit:" << endl;
        cin >> command;
        
        if (isValidCommand(command)) {
            switch (command) {
                case 'H':
                    showHelp();
                    break;
                case 'M':
                    showNetwork();
                    break;
                case 'Q':
                    gameRunning = false; // Exit the loop
                    cout << endl << "Thank you for playing!";
                    break;
                default:
                    doTurn(command);
                    break;
            }
        }
        else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}

void Controller::doTurn(char command) {
    cout << "doTurn" << endl;
    // Implementation for doing a turn in the game
}

// Function to show help
void Controller::showHelp() {
    // Output the help text from the messages map
    cout << messages["help"];
}

void Controller::showNetwork() {
    cout << endl << network << endl;
}

void Controller::showActions() {
    cout << messages["actions"];
}

bool Controller::isValidCommand(const char command) {
     if (COMMANDS.find(command) == string::npos) {
         return false;
     }

    return true;
}
