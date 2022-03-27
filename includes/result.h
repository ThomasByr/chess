#pragma once

#include "lib.h"

#include "board.h"
#include "move.h"

/**
 * @brief The Result class
 *
 * This class represents the result of a move play.
 */
class GameResult {
  public:
    static const int Continuing = 0;
    static const int Victory = 1;
    static const int Stalemate = 2;
    static const int IllegalMove = 3;

    int result_type;

    Color winner;
    Board next_board;
    Move move;

    /**
     * @brief GameResult constructor
     *
     * This constructor creates non valid default result.
     */
    GameResult();
    ~GameResult();

  private:
};
