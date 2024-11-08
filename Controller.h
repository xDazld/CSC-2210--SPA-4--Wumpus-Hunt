//
// Created by schreibert on 10/29/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>

#include "Network.h"
#include "Player.h"
using namespace std;

class Controller {
private:
  std::map<std::string, std::string> messages;
  Network network;
  Player* player;
  const string HELP = "HMQ";
  const string MOVES = "NSEW";
  const string ACTIONS = "CBK";

public:
  Controller(); // Constructor to initialize messages
  void startGame();
  void doTurn(char command);
  void showNetwork();
  void showHelp();
  void showError();
  void showActions();
  bool isValidCommand(const char command);
};

#endif // CONTROLLER_H

