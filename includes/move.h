#pragma once

#include "lib.h"

#include "position.h"

/**
 * @brief The Move class
 *
 * This class represents a move in the game.
 */
class Move {
  public:
    static const int QueenSideCastle = 0;
    static const int KingSideCastle = 1;
    static const int PieceMove = 2;
    static const int Resign = 3;
    static const int Invalid = 4;

    int move_type;
    Position from;
    Position to;

    /**
     * @brief Move constructor
     *
     * This constructor creates non valid default move.
     */
    Move();
    ~Move();

    /**
     * @brief updates a non valid move to a valid move
     *
     * @param move_string a string representing a move
     * @return int - the type of the move (also positionned in the object)
     */
    int from_string(const std::string &move_string);

    friend std::ostream &operator<<(std::ostream &os, const Move &move);

  private:
};
