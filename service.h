//
// Created by raffertyp on 11/8/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <string>
#include <utility>


class Service {
    std::string name;

protected:
    explicit Service(std::string name)
        : name(std::move(name)) {
    }

public:
    [[nodiscard]] std::string get_name() const {
        return name;
    }
};

class SQLServer : public Service {
public:
    SQLServer() : Service("SQL") {
    }
};

class HTTPServer : public Service {
public:
    HTTPServer() : Service("HTTP") {
    }
};

class EmailServer : public Service {
public:
    EmailServer() : Service("Email") {
    }
};

#endif //SERVICE_H
