#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace chess {

using MaterialValue = size_t;

constexpr MaterialValue kInfiniteMaterialValue = SIZE_MAX;

class Piece {
 public:
  enum class Type {
    kPawn,
    kRook,
    kKnight,
    kBishop,
    kKing,
    kQueen,
  };

  Piece(Type t, bool is_white) {
    type_ = t;
    is_white_ = is_white;

    switch (type_) {
      case Type::kPawn:
        material_ = 1;
        break;
      case Type::kRook:
        material_ = 6;
        has_castle_ = true;
        break;
      case Type::kKnight:
        material_ = 3;
        break;
      case Type::kBishop:
        material_ = 3;
        break;
      case Type::kQueen:
        material_ = 9;
        break;
      case Type::kKing:
        material_ = kInfiniteMaterialValue;
        has_castle_ = true;
        break;
      default:
        assert(false);
    }
  }

  MaterialValue GetMaterialValue() const;
  Type GetType() const;
  void SetHasMoved();
  bool HasMoved() const;
  void SetHasEnPassant(bool has_en_passant);
  bool HasEnPassant() const;
  bool IsWhite() const;
  bool HasCastle() const;

 private:
  Type type_;
  MaterialValue material_;
  bool is_white_;
  bool has_moved_ = false;
  bool has_en_passant_ = false;
  bool has_castle_ = false;
};

}  // namespace chess

#endif  // CHESS_PIECE_H