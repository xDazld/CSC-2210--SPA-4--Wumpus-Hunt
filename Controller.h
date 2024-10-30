//
// Created by schreibert on 10/29/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>

#include "Network.h"
#include "Player.h"

class Controller {
private:
  std::map<std::string, std::string> messages;
  Network* network;
  Player* player;

public:
  Controller(); // Constructor to initialize messages
  void startGame();
  void doTurn();
  void showNetwork();
  void showHelp();
  void showError();
  void showActions();
};

#endif // CONTROLLER_H

