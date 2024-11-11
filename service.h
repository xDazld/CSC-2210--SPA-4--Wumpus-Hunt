//
// Created by raffertyp on 11/8/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <string>
#include <utility>


class Service {
    std::string name;
    int port;

protected:
    explicit Service(std::string name, int port)
        : name(std::move(name)), port(port) {
    }

public:
    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] int get_port() const {
        return port;
    }
};

class SQLServer : public Service {
public:
    SQLServer() : Service("SQL", 3306) {
    }
};

class HTTPServer : public Service {
public:
    HTTPServer() : Service("HTTP", 80) {
    }
};

class EmailServer : public Service {
public:
    EmailServer() : Service("Email", 25) {
    }
};

#endif //SERVICE_H
