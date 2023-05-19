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

    template <Type T>
  	constexpr Piece() {
  		if constexpr (T == Type::kPawn) {
  			material_ = 1;
  		} else if constexpr (T == Type::kRook) {
  			material_ = 6;
  		} else if constexpr (T == Type::kKnight) {
  			material_ = 3;
  		} else if constexpr (T == Type::kBishop) {
  			material_ = 3;
  		} else if constexpr (T == Type::kQueen) {
  			material_ = 9;
  	    } else {
  	    	static_assert(T == Type::kKing, "Unknown Piece::Type in Piece constructor.");
  	    	material_ = kInfiniteMaterialValue;
  	    }

  	    type_ = T;
  	}

  	MaterialValue GetMaterialValue();

  private:
  	Type type_;
  	MaterialValue material_;
};

}  // namespace chess

#endif  // CHESS_PIECE_H