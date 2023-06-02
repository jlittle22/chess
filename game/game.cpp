#include "game.h"

#include <cstdint>

#include "piece.h"
#include "zobrist.h"

namespace chess {
namespace {
constexpr inline size_t AsFile(size_t index) { return index + 'a'; }
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
  MoveList legal_moves = {};
  board_.ForEachSquare([&](ChessBoard::Square& sq, const SquareIdentifier& id) {
    if (sq.occupant.has_value()) {
      FindLegalMovesForPiece(*sq.occupant, id, legal_moves);
    }
  });

  return legal_moves;
}

void Game::FindLegalMovesForPiece(Piece& p, const SquareIdentifier& location,
                                  MoveList& moves) {
  switch (p.GetType()) {
    case Piece::Type::kPawn: {
      FindLegalMovesForPawn(p, location, moves);
      break;
    }
    case Piece::Type::kRook: {
      FindLegalMovesForRook(p, location, moves);
      break;
    }
    case Piece::Type::kBishop: {
      FindLegalMovesForBishop(p, location, moves);
      break;
    }
    case Piece::Type::kKnight: {
      FindLegalMovesForKnight(p, location, moves);
      break;
    }
    case Piece::Type::kQueen: {
      FindLegalMovesForQueen(p, location, moves);
      break;
    }
    case Piece::Type::kKing: {
      FindLegalMovesForKing(p, location, moves);
      break;
    }
    default:
      assert(false);
  }
}

void Game::FindLegalMovesForPawn(Piece& pawn, const SquareIdentifier& location,
                                 MoveList& moves) {
  // Pawns can move...
  //    1. One vacant square forward (cannot capture)
  //    2. Two vacant squares forward on their first turn (cannot capture)
  //    3. One square diagonally only on a capture.
  //        a. And upon a double-square pawn move which jumps over a pawn's
  //           diagonal capture square.

  // If the king is in check, the pawn may not make any move other than those
  // that remove the check from the king by capture or block.
}

void Game::FindLegalMovesForRook(Piece& rook, const SquareIdentifier& location,
                                 MoveList& moves) {
  // Rooks can move...
  //   1. Any number of unoccupied squares in vertically or horizontally
  //   2. (DO NOT COUNT) Castle -- count as king move.

  // If the king is in check, the rook may not make any move other than those
  // that remove the check from the king by capture or block.
}

void Game::FindLegalMovesForKnight(Piece& knight,
                                   const SquareIdentifier& location,
                                   MoveList& moves) {
  // Knights can move...
  //   1. Two squares vertically and one square horizontally
  //   1. One square vertically and two squares horizontally

  // If the king is in check, the knight may not make any move other than those
  // that removes the check from the king by capture or block.
}

void Game::FindLegalMovesForBishop(Piece& bishop,
                                   const SquareIdentifier& location,
                                   MoveList& moves) {
  // Bishops can move...
  //   1. Any number of unoccupied squares diagonally

  // If the king is in check, the bishop may not make any move other than those
  // that removes the check from the king by capture or block.
}

void Game::FindLegalMovesForQueen(Piece& queen,
                                  const SquareIdentifier& location,
                                  MoveList& moves) {
  // The queen can move...
  // 1. Any number of unoccupied squares diagonally.
  // 2. Any number of unoccupied squares horizontally or vertically.

  // If the king is in check, the queen may not make any move other than those
  // that removes the check from the king by capture or block.
}

void Game::FindLegalMovesForKing(Piece& king, const SquareIdentifier& location,
                                 MoveList& moves) {
  // The king can move...
  //   1. To any unoccupied adjoining square unless it would be check.
  //   2. Castle long or short so long as...
  //        a. Neither the king nor the rook has previously moved
  //        b. The squares between the king and the rook are vacant
  //        c. The king does not leave, cross over, or finish on a square
  //           attacked by an enemy piece
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