#include "game.h"

#include <cstdint>

#include "zobrist.h"

namespace chess {

Game::Game() : is_white_to_move_(true) {
  // TODO(jsnl)
}

Game::Game(const Game& other, MoveIdentifier with_move) {
  this->board_ = other.board_;
  this->is_white_to_move_ = !other.is_white_to_move_;
  // TODO(jsnl): Apply with_move!
}

// TODO(jsnl)
uint64_t Game::Hash() { return ZobristStandard::kTable[0][0][0][0]; }

}  // namespace chess