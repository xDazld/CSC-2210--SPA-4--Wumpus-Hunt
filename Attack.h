//
// Created by schreibert on 10/29/2024.
//

#ifndef ATTACK_H
#define ATTACK_H
#include <string>

#include "Network.h"
#include "Player.h"

class Player;
class Computer;

/**
 * The Attack class is responsible for attacking a computer.
 */
class Attack {
protected:
    std::string name;
    Player *player = nullptr;

public:
    virtual ~Attack() = default;

    virtual bool doAttack(Computer &target) = 0;

    virtual void download(Player *player);
};

/**
 * The Backdoor class is responsible for creating a backdoor on a computer.
 */
class Backdoor : public Attack {
    Computer *location = nullptr;

public:
    bool doAttack(Computer &target) override;
};

/**
 * The IPSpoof class is responsible for granting access to a firewall-protected computer.
 */
class IPSpoof : public Attack {
public:
    bool doAttack(Computer &target) override;
};

/**
 * The TrojanHorse class is responsible for granting access to an antivirus-protected computer.
 */
class TrojanHorse : public Attack {
public:
    bool doAttack(Computer &target) override;
};

/**
 * The DatabaseEncryptionKey class is responsible for granting access to the WumpDB.
 */
class DatabaseEncryptionKey : public Attack {
public:
    bool doAttack(Computer &target) override;
};

/**
 * The XSS class is responsible for granting access to a web server.
 */
class XSS : public Attack {
public:
    bool doAttack(Computer &target) override;
};

/**
 * The EmailSpoof class is responsible for granting access to an email server.
 */
class EmailSpoof : public Attack {
public:
    bool doAttack(Computer &target) override;
};

#endif //ATTACK_H
