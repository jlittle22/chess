#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

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

  template <Type T, bool kIsWhite>
  constexpr Piece() {
    if constexpr (T == Type::kPawn) {
      material_ = 1;
    } else if constexpr (T == Type::kRook) {
      material_ = 6;
      has_castle_ = true;
    } else if constexpr (T == Type::kKnight) {
      material_ = 3;
    } else if constexpr (T == Type::kBishop) {
      material_ = 3;
    } else if constexpr (T == Type::kQueen) {
      material_ = 9;
    } else {
      static_assert(T == Type::kKing,
                    "Unknown Piece::Type in Piece constructor.");
      material_ = kInfiniteMaterialValue;
      has_castle_ = true;
    }

    type_ = T;
    is_white_ = kIsWhite;
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