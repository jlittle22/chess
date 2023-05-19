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

 private:
  static constexpr size_t kBoardHeight = 8;
  static constexpr size_t kBoardWidth = 8;

  /**
   * A standard game of chess includes the following unique piece types:
   *     1. White pawn
   *     2. Black pawn
   *     3. White pawn (with en passant)
   *     4. Black pawn (with en passant)
   *     5. White rook
   *     6. Black rook
   *     7. White rook (with castle)
   *     8. Black rook (with castle)
   *     9. White knight
   *     10. Black knight
   *     11. White bishop
   *     12. Black bishop
   *     13. White king
   *     14. Black king
   *     15. White king (with castle)
   *     16. Black king (with castle)
   *     17. White queen
   *     18. Black queen
   */
  static constexpr size_t kUniquePieceTypeCount = 18;

  // https://en.wikipedia.org/wiki/Zobrist_hashing
  static uint64_t kZobristTable[kBoardHeight][kBoardWidth]
                               [kUniquePieceTypeCount];

  Board<kBoardHeight, kBoardWidth, Piece> board_;
  bool is_white_to_move_;
};
}  // namespace chess

#endif  // CHESS_GAME_H