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

class Attack {
protected:
    std::string name;
    Player *player = nullptr;

public:
    virtual ~Attack() = default;

    virtual bool doAttack(Computer &target) = 0;

    virtual void download(Player *player);
};

class Backdoor : public Attack {
    Computer *location = nullptr;

    bool doAttack(Computer &target) override;
};

class IPSpoof : public Attack {
    bool doAttack(Computer &target) override;
};

class TrojanHorse : public Attack {
    bool doAttack(Computer &target) override;
};

class DatabaseEncryptionKey : public Attack {
    bool doAttack(Computer &target) override;
};

class XSS : public Attack {
    bool doAttack(Computer &target) override;
};

class EmailSpoof : public Attack {
    bool doAttack(Computer &target) override;
};

#endif //ATTACK_H
