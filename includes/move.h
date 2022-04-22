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

    /**
     * @brief Move constructor
     *
     * This constructor creates non valid default move.
     */
    Move();
    ~Move();

    const int &move_type() const;         // accessor
    int &move_type();                     // mutator
    void move_type(const int &move_type); // mutator

    const Position &from() const; // accessor
    const Position &to() const;   // accessor
    Position &from();             // mutator
    Position &to();               // mutator
    void from(const Position &from);
    void to(const Position &to);

    /**
     * @brief updates a non valid move to a valid move
     *
     * @param move_string a string representing a move
     * @return int - the type of the move (also positionned in the object)
     */
    int update_from_string(const std::string &move_string);

    /**
     * @brief fmt a move
     *
     * @param os ostream
     * @param move move
     * @return std::ostream& - ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const Move &move);

  private:
    int move_type_; // type of the move
    Position from_; // Position of the piece that is moving
    Position to_;   // Position of the piece that is moving to
};
