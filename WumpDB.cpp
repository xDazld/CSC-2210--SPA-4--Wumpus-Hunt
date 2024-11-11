//
// Created by schreibert on 10/29/2024.
//

#include "WumpDB.h"

#include "Network.h"

WumpDB::WumpDB(): Computer('#') {
    addService(new SQLServer());
    addDefense(new Antivirus());
    addDefense(new Firewall());
}
