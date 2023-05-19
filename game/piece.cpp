#include "piece.h"

namespace chess {

MaterialValue Piece::GetMaterialValue() { return material_; }

Piece::Type Piece::GetType() { return type_; }

}  // namespace chess
