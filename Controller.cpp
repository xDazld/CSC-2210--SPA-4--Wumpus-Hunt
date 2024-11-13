//
// Created by schreibert on 10/29/2024.
//

#include "Controller.h"
#include <iostream>
#include <map>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <typeinfo>

using namespace std;

static constexpr bool DEBUG_MODE = false;

// Constructor to initialize messages
Controller::Controller()
    : network(new Network(createLayout())), player() {
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

Services:
Every computer has a service running. Most are either HTTP or Email servers. The WumpDB has an SQL
server. Your scans will tell you what ports neighbor computers have open. The services run on the
following ports:
 * HTTP: 80
 * Email: 25
 * SQL: 3306

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

Map Key:
. - An empty space
+ - The Player (Only One)
? - IP Spoof
? - Backdoor (Only One)
? - Encryption Key (Only One)
? - XSS
? - Email Spoof
? - Trojan Horse
@ - Firewall
! - Antivirus
# - WumpDB (Only One)

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
        player->scan();
        cout <<
                "Action: N)orth, S)outh, E)ast, W)est, A)ttack, B)ackdoor, H)elp, M)ap, Q)uit:"
                << endl;
        cin >> command;
        command = toupper(command);

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
                    if (doTurn(command)) {
                        gameRunning = false;
                    }
                    break;
            }
        } else {
            cerr << "Invalid command. Please try again." << endl;
        }
    }
}

bool Controller::doTurn(const char command) const {
    bool isLoss = false;
    if (isMove(command)) {
        isLoss = player->doMove(command);
        if (isLoss) {
            cout << "You were removed from the network by an antivirus!" << endl;
        }
        return isLoss;
    } else if (command == ATTACK) {
        cout << "N)orth, S)outh, E)ast, W)est" << endl;
        char directionInput;
        cin >> directionInput;
        directionInput = toupper(directionInput);
        vector<Attack *> attacks = player->getAvailableAttacks();
        cout << "B)ackdoor ["<< countTypes<Backdoor>(attacks)
             <<"], I)P Spoof ["<< countTypes<IPSpoof>(attacks)
             <<"], T)rojan ["<< countTypes<TrojanHorse>(attacks)
             <<"], K)ey ["<< countTypes<DatabaseEncryptionKey>(attacks)
             <<"], X)SS ["<< countTypes<::XSS>(attacks)
             <<"], E)mail Spoof ["<< countTypes<EmailSpoof>(attacks)<<"]" << endl;
        char attackCommand;
        cin >> attackCommand;
        attackCommand = toupper(attackCommand);
        const bool isWin = player->aimAttack(attackCommand, directionInput);
        if (isWin) {
            cout << "You hacked the WumpDB!" << endl;
        }
        return isWin;
    }
    if (DEBUG_MODE) {
        // ReSharper disable once CppDFAUnreachableCode
        showNetwork();
    }
    return false;
}

// Function to show help
void Controller::showHelp() {
    // Output the help text from the messages map
    cout << messages["help"];
}

void Controller::showNetwork() const {
    cout << endl << *network << endl;
}

void Controller::showActions() {
    cout << messages["actions"];
}

bool Controller::isMove(const char command) {
    if (command == NORTH || command == SOUTH || command == EAST || command == WEST) {
        return true;
    }
    return false;
}

bool Controller::isMenu(const char command) {
    if (command == HELP || command == MAP || command == QUIT || command == ATTACK) {
        return true;
    }
    return false;
}

bool Controller::isValidCommand(const char command) {
    if (isMove(command) || isMenu(command)) {
        return true;
    }
    return false;
}

string Controller::createLayout() {
    // Initialize the base string with fixed characters
    string str = "+..................  ......  ........#..........";

    // Define the characters that can be randomized
    vector<char> randomChars = {'?', '@', '!', '.', '.', '?'}; // '.' has higher frequency

    // Seed for randomness
    srand(static_cast<unsigned int>(time(nullptr)));

    // Replace non-fixed characters with random choices from randomChars
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {  // Only replace dots
            str[i] = randomChars[rand() % randomChars.size()];
        }
    }

    return str;
}

Controller::~Controller() {
    delete network;
    delete player;
}
