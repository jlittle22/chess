#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <cassert>
#include <optional>

#include "move.h"

namespace chess {

template <typename Piece>
struct Square {
  std::optional<Piece> occupant;
  bool is_white;
};

template <size_t kHeight, size_t kWidth, typename PieceType>
class Board {
 public:
  using File = Square<PieceType>[kHeight];

  Board() = default;
  ~Board() = default;

  const File& operator[](FileIdentifier file) {
    int index = static_cast<int>(file) - static_cast<int>('a');
    assert(index >= 0) assert(index < kHeight);
    return board_[index];
  }

 private:
  Square<PieceType> board_[kHeight][kWidth];
};

}  // namespace chess

#endif  // CHESS_BOARD_H