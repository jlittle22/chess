#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <memory>

#include "board.h"
#include "piece.h"

namespace chess {
class Game {
  public:
  	Game();
	~Game() = default;
  private:
  	static constexpr size_t kBoardHeight = 8;
  	static constexpr size_t kBoardWidth = 8;
    Board<kBoardHeight, kBoardWidth, Piece> board;
};
}

#endif  // CHESS_GAME_H