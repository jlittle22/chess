#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>
#include <vector>

#include "board.h"
#include "move.h"
#include "piece.h"

namespace chess {
class Game {
 public:
  using MoveList = std::vector<MoveIdentifier>;
  Game();
  ~Game() = default;
  Game(const Game& other, MoveIdentifier with_move);
  uint64_t GetHash() const;

  MoveList GetLegalMoves();

 private:
  static constexpr size_t kBoardHeight = 8;
  static constexpr size_t kBoardWidth = 8;
  using ChessBoard = Board<kBoardHeight, kBoardWidth, Piece>;

  void Hash();

  void FindLegalMovesForPiece(Piece& p, const SquareIdentifier& location,
                              MoveList& moves);

  void FindLegalMovesForPawn(Piece& pawn, const SquareIdentifier& location,
                             MoveList& moves);

  void FindLegalMovesForRook(Piece& rook, const SquareIdentifier& location,
                             MoveList& moves);

  void FindLegalMovesForKnight(Piece& knight, const SquareIdentifier& location,
                               MoveList& moves);

  void FindLegalMovesForBishop(Piece& bishop, const SquareIdentifier& location,
                               MoveList& moves);

  void FindLegalMovesForQueen(Piece& queen, const SquareIdentifier& location,
                              MoveList& moves);

  void FindLegalMovesForKing(Piece& king, const SquareIdentifier& location,
                             MoveList& moves);

  ChessBoard board_;
  uint64_t hash_ = 0;
  bool is_white_to_move_;
  std::vector<SquareIdentifier> white_king_checks_;
  std::vector<SquareIdentifier> black_king_checks_;
};
}  // namespace chess

#endif  // CHESS_GAME_H