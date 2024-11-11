//
// Created by raffertyp on 11/8/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <string>
#include <utility>

/**
 * The Service class is responsible for representing the services available on a computer.
 */
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

/**
 * The SQLServer class is responsible for representing the SQL service on the WumpDB.
 */
class SQLServer : public Service {
public:
    SQLServer() : Service("SQL", 3306) {
    }
};

/**
 * The HTTPServer class is responsible for representing the HTTP service on computers.
 */
class HTTPServer : public Service {
public:
    HTTPServer() : Service("HTTP", 80) {
    }
};

/**
 * The EmailServer class is responsible for representing the Email service on computers.
 */
class EmailServer : public Service {
public:
    EmailServer() : Service("Email", 25) {
    }
};

#endif //SERVICE_H
