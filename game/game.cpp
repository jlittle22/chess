#include "game.h"

#include <cstdint>

#include "piece.h"
#include "zobrist.h"

namespace chess {
namespace {
inline size_t AsFile(size_t index) { return index + 'a'; }
}  // namespace

Game::Game() : is_white_to_move_(true) {
  // Set up white pieces
  board_['a'][0] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kRook, /*is_white=*/true));
  board_['b'][0] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kKnight, /*is_white=*/true));
  board_['c'][0] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kBishop, /*is_white=*/true));
  board_['d'][0] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kQueen, /*is_white=*/true));
  board_['e'][0] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kKing, /*is_white=*/true));
  board_['f'][0] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kBishop, /*is_white=*/true));
  board_['g'][0] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kKnight, /*is_white=*/true));
  board_['h'][0] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kRook, /*is_white=*/true));

  // White pawns
  board_['a'][1] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['b'][1] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['c'][1] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['d'][1] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['e'][1] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['f'][1] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['g'][1] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));
  board_['h'][1] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/true));

  // Black pieces
  board_['a'][7] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kRook, /*is_white=*/false));
  board_['b'][7] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kKnight, /*is_white=*/false));
  board_['c'][7] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kBishop, /*is_white=*/false));
  board_['d'][7] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kQueen, /*is_white=*/false));
  board_['e'][7] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kKing, /*is_white=*/false));
  board_['f'][7] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kBishop, /*is_white=*/false));
  board_['g'][7] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kKnight, /*is_white=*/false));
  board_['h'][7] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kRook, /*is_white=*/false));

  // Black pawns
  board_['a'][6] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['b'][6] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['c'][6] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['d'][6] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['e'][6] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['f'][6] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['g'][6] = ChessBoard::BlackSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));
  board_['h'][6] = ChessBoard::WhiteSquareWithPiece(
      Piece(Piece::Type::kPawn, /*is_white=*/false));

  Hash();
}

Game::Game(const Game& other, MoveIdentifier with_move) {
  // Assume with_move is a legal move.
  this->board_ = other.board_;
  this->is_white_to_move_ = !other.is_white_to_move_;
  // TODO(jsnl): Apply with_move!
  Hash();
}

uint64_t Game::GetHash() const { return hash_; }

std::vector<MoveIdentifier> Game::GetLegalMoves() {
  std::vector<MoveIdentifier> legal_moves = {};
  board_.ForEachSquare([&](ChessBoard::Square& sq) {
    if (sq.occupant.has_value()) {
      // FindLegalMovesForPiece(*sq.occupant)
    }
  });

  return legal_moves;
}

void Game::FindLegalMovesForPiece(const Piece& p,
                                  const SquareIdentifier& location,
                                  MoveList& moves) {
  switch (p.GetType()) {
    case Piece::Type::kPawn: {
      break;
    }
    case Piece::Type::kRook: {
      break;
    }
    case Piece::Type::kBishop: {
      break;
    }
    case Piece::Type::kKnight: {
      break;
    }
    case Piece::Type::kQueen: {
      break;
    }
    case Piece::Type::kKing: {
      break;
    }
    default:
      assert(false);
  }
}

void Game::Hash() {
  hash_ = 0;
  for (int w = 0; w < kBoardWidth; ++w) {
    for (int h = 0; h < kBoardHeight; ++h) {
      const ChessBoard::Square& sq = board_[AsFile(w)][h];
      if (sq.occupant.has_value() == true) {
        size_t piece = ZobristStandard::GetPieceId(*sq.occupant);
        size_t turn = ZobristStandard::GetTurnId(is_white_to_move_);
        hash_ ^= ZobristStandard::kTable[w][h][piece][turn];
      }
    }
  }
}

}  // namespace chess