#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>

#include "board.h"
#include "move.h"
#include "piece.h"

namespace chess {
class Game {
 public:
  Game();
  ~Game() = default;
  Game(const Game& other, MoveIdentifier with_move);

  uint64_t Hash();

 private:
  static constexpr size_t kBoardHeight = 8;
  static constexpr size_t kBoardWidth = 8;
  using ChessBoard = Board<kBoardHeight, kBoardWidth, Piece>;

  ChessBoard board_;
  bool is_white_to_move_;
};
}  // namespace chess

#endif  // CHESS_GAME_H