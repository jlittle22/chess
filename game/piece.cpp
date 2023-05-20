#include "piece.h"

#include <cassert>

namespace chess {

MaterialValue Piece::GetMaterialValue() const { return material_; }

Piece::Type Piece::GetType() const { return type_; }

void Piece::SetHasMoved() {
  assert(has_moved_ == false);
  has_moved_ = true;
}

bool Piece::HasMoved() const { return has_moved_; }

void Piece::SetHasEnPassant(bool has_en_passant) {
  has_en_passant_ = has_en_passant;
}

bool Piece::HasEnPassant() const { return has_en_passant_; }

bool Piece::IsWhite() const { return is_white_; }

bool Piece::HasCastle() const { return has_castle_; }

}  // namespace chess
