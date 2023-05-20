#include "game.h"

#include <cstdint>

#include "piece.h"
#include "zobrist.h"

namespace chess {

Game::Game() : is_white_to_move_(true) {
  // Set up white pieces
  board_['a'][1] = Board::WhiteSquareWithPiece(Piece<>());
}

Game::Game(const Game& other, MoveIdentifier with_move) {
  this->board_ = other.board_;
  this->is_white_to_move_ = !other.is_white_to_move_;
  // TODO(jsnl): Apply with_move!
}

uint64_t Game::Hash() {
  uint64_t hash = 0;
  for (int h = 0; h < kBoardHeight; ++h) {
    for (int w = 0; w < kBoardWidth; ++w) {
      const ChessBoard::Square& sq = board_[h][w];
      if (sq.occupant.has_value() == true) {
        size_t piece = ZobristStandard::GetPieceId(*sq.occupant);
        size_t turn = ZobristStandard::GetTurnId(is_white_to_move_);
        hash ^= ZobristStandard::kTable[h][w][piece][turn];
      }
    }
  }
  return hash;
}

}  // namespace chess