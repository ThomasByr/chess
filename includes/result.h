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

    Color winner;     // Color::White or Color::Black if result_type == Victory
    Board next_board; // Board after the move if result_type == Continuing
    Move move;        // Move that was played if result_type == IllegalMove

    /**
     * @brief GameResult constructor
     *
     * This constructor creates non valid default result.
     */
    GameResult();
    ~GameResult();

  private:
};
