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

    /**
     * @brief GameResult constructor
     *
     * This constructor creates non valid default result.
     */
    GameResult();
    ~GameResult();

    const int &result_type() const;           // accessor
    int &result_type();                       // mutator
    void result_type(const int &result_type); // mutator

    const Color &winner() const;      // accessor
    Color &winner();                  // mutator
    void winner(const Color &winner); // mutator

    const Board &next_board() const;          // accessor
    Board &next_board();                      // mutator
    void next_board(const Board &next_board); // mutator

    const Move &move() const;    // accessor
    Move &move();                // mutator
    void move(const Move &move); // mutator

  private:
    int result_type_;

    Color winner_;     // Color::White or Color::Black if result_type == Victory
    Board next_board_; // Board after the move if result_type == Continuing
    Move move_;        // Move that was played if result_type == IllegalMove
};
