#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <cassert>
#include <functional>
#include <optional>

#include "move.h"

namespace chess {

template <typename Piece>
struct GeneralSquare {
  std::optional<Piece> occupant;
  bool is_white;
};

template <size_t kHeight, size_t kWidth, typename PieceType>
class Board {
 public:
  using Square = GeneralSquare<PieceType>;
  using File = Square[kHeight];

  Board() = default;
  ~Board() = default;

  static Square EmptyWhiteSquare() {
    return {
        .occupant = std::nullopt_t,
        .is_white = true,
    };
  }

  static Square EmptyBlackSquare() {
    return {
        .occupant = std::nullopt_t,
        .is_white = false,
    };
  }

  static Square WhiteSquareWithPiece(const PieceType& p) {
    return {
        .occupant = p,
        .is_white = true,
    };
  }

  static Square BlackSquareWithPiece(const PieceType& p) {
    return {
        .occupant = p,
        .is_white = false,
    };
  }

  const File& operator[](FileIdentifier file) {
    int index = static_cast<int>(file) - static_cast<int>('a');
    assert(index >= 0);
    assert(index < kHeight);
    return board_[index];
  }

  void ForEachSquare(std::function<void(Square&)> f) {
    for (int h = 0; h < kHeight; ++h) {
      for (int w = 0; w < kWidth; ++w) {
        f(board_[h][w]);
      }
    }
  }

 private:
  Square board_[kHeight][kWidth];
};

}  // namespace chess

#endif  // CHESS_BOARD_H