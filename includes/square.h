#pragma once

#include "lib.h"

#include "piece.h"

/**
 * @brief The Square class
 *
 * This class represents a square on the board.
 */
class Square {
  public:
    /**
     * @brief Square constructor
     *
     * This constructor creates an empty square.
     */
    Square();
    /**
     * @brief Square constructor
     *
     * This constructor creates a square with a piece.
     *
     * @param piece the piece to put on the square
     */
    Square(Piece *piece);
    ~Square();

    /**
     * @brief same as Square(Piece *piece) but static
     *
     * @param piece piece to put on the square
     * @return Square new square
     */
    static Square from_piece(Piece *piece);
    /**
     * @brief is_empty
     *
     * This method returns true if the square is empty.
     *
     * @return true if the square is empty
     * @return false if the square is not empty
     */
    bool is_empty();
    /**
     * @brief Get the piece object
     *
     * @return Piece* - the piece object, nullptr if the square is empty
     */
    Piece *get_piece();

  private:
    Piece *piece; // piece on the square or nullptr if empty
};

static const Square EMPTY_SQUARE = Square(); // Empty square
