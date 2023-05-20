
#include <iostream>

#include "game/game.h"

int main() {
  // chess::Game::InitGlobalState();
  chess::Game game;
  std::cerr << sizeof(game) << std::endl;
  std::cerr << game.GetHash() << std::endl;
  return 0;
}