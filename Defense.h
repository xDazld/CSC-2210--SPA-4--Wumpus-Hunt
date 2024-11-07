//
// Created by schreibert on 10/29/2024.
//

#ifndef DEFENSE_H
#define DEFENSE_H
#include <string>
#include <utility>


class Defense {
    std::string name;

protected:
    [[nodiscard]] explicit Defense(std::string name)
        : name(std::move(name)) {
    }

public:
    virtual ~Defense() = default;

    virtual bool defend() = 0;

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    friend bool operator==(const Defense &lhs, const std::string &rhs) {
        return lhs.name == rhs;
    }

    friend bool operator==(const Defense &lhs, const Defense &rhs) {
        return lhs.name == rhs.name;
    }
};

class Firewall : public Defense {
public:
    Firewall(): Defense("Firewall") {
    }

    bool defend() override;
};

class Antivirus : public Defense {
public:
    Antivirus(): Defense("Antivirus") {
    }

    bool defend() override;
};

#endif //DEFENSE_H
