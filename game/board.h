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

  Board() {
    bool make_white = false;
    ForEachSquare([&](Square& sq, const SquareIdentifier&) {
      sq.is_white = make_white;
      make_white = !make_white;
    });
  };
  ~Board() = default;

  static Square EmptyWhiteSquare() {
    return {
        .occupant = {},
        .is_white = true,
    };
  }

  static Square EmptyBlackSquare() {
    return {
        .occupant = {},
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

  File& operator[](FileIdentifier file) {
    int index = static_cast<int>(file) - static_cast<int>('a');
    assert(index >= 0);
    assert(index < kWidth);
    return board_[index];
  }

  void ForEachSquare(
      std::function<void(Square&, const SquareIdentifier& id)> f) {
    for (FileIdentifier w = 0; w < kWidth; ++w) {
      for (RankIdentifier h = 0; h < kHeight; ++h) {
        f(board_[w][h], {
                            .rank = h,
                            .file = w,
                        });
      }
    }
  }

  void ForEachSquareAsQueensMove(
      std::function<void(Square& square, const SquareIdentifier& id)> f,
      const SquareIdentifier& origin) {
    ForEachSquareAsBishopsMove(f, origin);
    ForEachSquareAsRooksMove(f, origin);
  }

  void ForEachSquareAsKingsMove(
      std::function<void(Square& square, const SquareIdentifier& id)> f,
      const SquareIdentifier& origin) {
    for (RankIdentifier rank = -1; rank <= 1; ++rank) {
      for (FileIdentifier file = -1; file <= 1; ++file) {
        if (rank == 0 && file == 0) {
          continue;
        }

        SquareIdentifier current_square = {
            .rank = origin.rank + rank,
            .file = origin.file + file,
        };

        if (IsOnBoard(current_square)) {
          f(GetSquare(current_square), current_square);
        }
      }
    }
  }

  void ForEachSquareAsRooksMove(
      std::function<void(Square& square, const SquareIdentifier& id)> f,
      const SquareIdentifier& origin) {
    // Up
    SquareIdentifier current_square = {
        .rank = origin.rank + 1,
        .file = origin.file,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank++;

      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Right
    current_square = {
        .rank = origin.rank,
        .file = origin.file + 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.file++;

      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Down
    current_square = {
        .rank = origin.rank - 1,
        .file = origin.file,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank--;

      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Left
    current_square = {
        .rank = origin.rank,
        .file = origin.file - 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.file--;

      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }
  }

  void ForEachSquareAsBishopsMove(
      std::function<void(Square& square, const SquareIdentifier& id)> f,
      const SquareIdentifier& origin) {
    // Up and right
    SquareIdentifier current_square = {
        .rank = origin.rank + 1,
        .file = origin.file + 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank++;
      current_square.file++;
      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Up and left
    current_square = {
        .rank = origin.rank + 1,
        .file = origin.file - 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank++;
      current_square.file--;
      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Down and left
    current_square = {
        .rank = origin.rank - 1,
        .file = origin.file - 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank--;
      current_square.file--;
      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }

    // Down and right
    current_square = {
        .rank = origin.rank - 1,
        .file = origin.file + 1,
    };

    while (IsOnBoard(current_square)) {
      f(GetSquare(current_square), current_square);
      current_square.rank--;
      current_square.file++;
      if (GetSquare(current_square).occupant.has_value()) {
        break;
      }
    }
  }

  void ForEachSquareAsKnightsMove(
      std::function<void(Square& square, const SquareIdentifier& id)> f,
      const SquareIdentifier& origin) {
    SquareIdentifier up_and_left = {
        .rank = origin.rank + 2,
        .file = origin.file - 1,
    };

    if (IsOnBoard(up_and_left)) {
      f(GetSquare(up_and_left), up_and_left);
    }

    SquareIdentifier up_and_right = {
        .rank = origin.rank + 2,
        .file = origin.file + 1,
    };

    if (IsOnBoard(up_and_right)) {
      f(GetSquare(up_and_right), up_and_right);
    }

    SquareIdentifier right_and_up = {
        .rank = origin.rank + 1,
        .file = origin.file + 2,
    };

    if (IsOnBoard(right_and_up)) {
      f(GetSquare(right_and_up), right_and_up);
    }

    SquareIdentifier right_and_down = {
        .rank = origin.rank - 1,
        .file = origin.file + 2,
    };

    if (IsOnBoard(right_and_down)) {
      f(GetSquare(right_and_down), right_and_down);
    }

    SquareIdentifier down_and_right = {
        .rank = origin.rank - 2,
        .file = origin.file + 1,
    };

    if (IsOnBoard(down_and_right)) {
      f(GetSquare(down_and_right), down_and_right);
    }

    SquareIdentifier down_and_left = {
        .rank = origin.rank - 2,
        .file = origin.file - 1,
    };

    if (IsOnBoard(down_and_left)) {
      f(GetSquare(down_and_left), down_and_left);
    }

    SquareIdentifier left_and_down = {
        .rank = origin.rank - 1,
        .file = origin.file - 2,
    };

    if (IsOnBoard(left_and_down)) {
      f(GetSquare(left_and_down), left_and_down);
    }

    SquareIdentifier left_and_up = {
        .rank = origin.rank + 1,
        .file = origin.file - 2,
    };

    if (IsOnBoard(left_and_up)) {
      f(GetSquare(left_and_up), left_and_up);
    }
  }

  inline Square& GetSquare(SquareIdentifier& id) {
    return board_[id.file][id.rank];
  }

 private:
  bool IsOnBoard(const SquareIdentifier& location) {
    if (location.rank >= kHeight || location.rank < 0) {
      return false;
    }

    if (location.file >= kWidth || location.file < 0) {
      return false;
    }

    return true;
  }

  Square board_[kWidth][kHeight];
};

}  // namespace chess

#endif  // CHESS_BOARD_H