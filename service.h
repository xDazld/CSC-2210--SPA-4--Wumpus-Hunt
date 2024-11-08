//
// Created by raffertyp on 11/8/2024.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <string>


class Service {
    std::string name;
};

class SQLServer : public Service {
};

class HTTPServer : public Service {
};

class EmailServer : public Service {
};

#endif //SERVICE_H
