#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

namespace chess {

using FileIdentifier = char;
using RankIdentifier = size_t;

struct SquareIdentifier {
  RankIdentifier rank;
  FileIdentifier file;
};

struct MoveIdentifier {
  SquareIdentifier origin;
  SquareIdentifier destination;
};

}  // namespace chess

#endif  // CHESS_MOVE_H