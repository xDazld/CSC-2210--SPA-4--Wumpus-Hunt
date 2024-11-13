//
// Created by schreibert on 10/29/2024.
//

#ifndef DEFENSE_H
#define DEFENSE_H
#include <string>
#include <utility>

/**
 * The Defense class is responsible for defending a computer.
 */
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

/**
 * The Firewall class is responsible for defending against scans.
 */
class Firewall : public Defense {
public:
    Firewall(): Defense("Firewall", "The computer is not responding to scans.") {
    }
};

/**
 * The Antivirus class is responsible for defending against scans.
 */
class Antivirus : public Defense {
public:
    Antivirus(): Defense("Antivirus", "Unauthorized Activity Detected.") {
    }
};

#endif //DEFENSE_H
