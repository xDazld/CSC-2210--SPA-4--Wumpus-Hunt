//
// Created by schreibert on 10/29/2024.
//

#include "Controller.h"
#include <iostream>
#include <map>

using namespace std;

static constexpr bool DEBUG_MODE = false;

// Constructor to initialize messages
Controller::Controller()
    : network(new Network(".?...@..@!.?..?.?..  .?.?..  ?...!..@#..+??.!..@")), player() {
    // Initialize player
    player = new Player(network->getStart(), network);
    // Store the help text in the messages map
    messages["start"] = R"(
You are in a network with many computers. Each computer has 1 to 4 connections to other computers.
Each computer has a service you can attack. Some computers are protected by an antivirus or a
firewall. You can download programs from some computers to attack others. Good luck.
)";
    messages["help"] = R"(
Welcome to "Hack the WumpDB"

The WumpDB resides in a network of computers. Each computer has 1 to 4 network connections leading
to other computers. (Look at a rectangular maze to see how this works - if you don't know what a
rectangular maze is, ask someone).

Hazards:
 * Antivirus
 * Firewall

WumpDB:
The WumpDB is well protected and is usually not moved to different computers. Attempting to connect
to the WumpDB without having proper permissions to access it will cause it to blacklist your IP
address, meaning you lose.

You:
Each turn you can attack an adjacent computer to allow lateral movement to that computer or perform
the lateral movement.
You can move across one network connection at a time. If you successfully move to the computer with
the WumpDB, you win. You will automatically do some scanning when you connect to a computer.
You attack by telling the game which direction on the network you want to attack. If you manage to
attack your local host, you will lose. However, if you connect to a computer will a firewall, all
your spoof attacks will be removed.
Connecting to a computer with antivirus installed will cause your attack to be found out and you
will be removed from the network.
When exploring network you can find three different tools to help you. An encryption key will allow
you to decode the encryption on the WumpDB and gain access to the database without getting
blacklisted, allowing you to win the game. You can also find source code for spoofing attacks in
the network, using a spoofing attack will allow you to remove firewalls and antiviruses from an
adjacent computer. Finally, you can find backdoors that will let you return back to the location
you found it when used.

Scanning:
When you are one connection away from a WumpDB or hazard, the game will say:
* WumpDB: This device has a database administration tool installed.
* Antivirus: Unauthorized Activity Detected
* Firewall: A connected device is not responding to scans.

Good luck!
)";
if (DEBUG_MODE) {
        // ReSharper disable once CppDFAUnreachableCode
        cerr << "WARNING: DEBUG MODE IS ON! DO NOT COMMIT IN THIS STATE" << endl;
    }
}

void Controller::startGame() {
    cout << messages["start"] << endl;

    char command;
    bool gameRunning = true;

    while (gameRunning) {
        cout <<
                "Action: N)orth, S)outh, E)ast, W)est, A)ttack, B)ackdoor, K)ey, H)elp, M)ap, Q)uit:"
                << endl;
        cin >> command;

        if (isValidCommand(command)) {
            switch (command) {
                case HELP:
                    showHelp();
                    break;
                case MAP:
                    showNetwork();
                    break;
                case QUIT:
                    gameRunning = false; // Exit the loop
                    cout << endl << "Thank you for playing!";
                    break;
                default:
                    doTurn(command);
                    break;
            }
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}

void Controller::doTurn(char command) {
    if (isMove(command)) {
        player->doMove(command);

    } else if (isAttack(command)) {
        cout << "N)orth, S)outh, E)ast, W)est" << endl;
        char directionInput;
        cin >> directionInput;

        player->aimAttack(command, directionInput);

    }
    if (DEBUG_MODE) {
        // ReSharper disable once CppDFAUnreachableCode
        showNetwork();
    }
}

// Function to show help
void Controller::showHelp() {
    // Output the help text from the messages map
    cout << messages["help"];
}

void Controller::showNetwork() {
    cout << endl << *network << endl;
}

void Controller::showActions() {
    cout << messages["actions"];
}

bool Controller:: isMove(char command) {
    if (command == NORTH || command == SOUTH || command == EAST || command == WEST) {
        return true;
    }
    return false;
}

bool Controller::isAttack(char command) {
    if (command == CODE || command == BACKDOOR || command == KEY) {
        return true;
    }
    return false;
}

bool Controller::isMenu(char command) {
    if (command == HELP || command == MAP || command == QUIT) {
        return true;
    }
    return false;
}

bool Controller::isValidCommand(const char command) {
    if (isAttack(command) || isMove(command) || isMenu(command)) {
        return true;
    }
    return false;
}

Controller::~Controller() {
    delete network;
    delete player;
}
