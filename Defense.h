//
// Created by schreibert on 10/29/2024.
//

#ifndef DEFENSE_H
#define DEFENSE_H
#include <string>


class Defense {
    std::string name;

public:
    virtual ~Defense() = default;

    virtual bool defend() = 0;
};

class Firewall : Defense {
};

class Antivirus : Defense {
};

#endif //DEFENSE_H
