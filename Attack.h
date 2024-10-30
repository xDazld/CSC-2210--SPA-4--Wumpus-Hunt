//
// Created by schreibert on 10/29/2024.
//

#ifndef ATTACK_H
#define ATTACK_H
#include <string>


class Attack {
    std::string name;

public:
    virtual ~Attack() = default;

    virtual bool doAttack() = 0;
};

class Backdoor : Attack {
};

class Spoof : Attack {
};

class DatabaseEncryptionKey : Attack {
};

#endif //ATTACK_H
