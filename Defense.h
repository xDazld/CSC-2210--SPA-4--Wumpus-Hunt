//
// Created by schreibert on 10/29/2024.
//

#ifndef DEFENSE_H
#define DEFENSE_H
#include <string>
#include <utility>


class Defense {
    std::string name;
    std::string message;

protected:
    [[nodiscard]] explicit Defense(std::string name, std::string message)
        : name(std::move(name)), message(std::move(message)) {
    }

public:
    virtual ~Defense() = default;

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    friend bool operator==(const Defense &lhs, const std::string &rhs) {
        return lhs.name == rhs;
    }

    friend bool operator==(const Defense &lhs, const Defense &rhs) {
        return lhs.name == rhs.name;
    }

    std::string get_message() {
        return message;
    }
};

class Firewall : public Defense {
public:
    Firewall(): Defense("Firewall", "The computer is not responding to scans.") {
    }
};

class Antivirus : public Defense {
public:
    Antivirus(): Defense("Antivirus", "The computer deleted the scanning program.") {
    }
};

#endif //DEFENSE_H
