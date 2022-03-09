#pragma once

#include "piece.h"

class Square {
  public:
    Square();
    Square(Piece *piece);
    ~Square();

    static Square from_piece(Piece *piece);
    inline bool is_empty();
    inline Piece *get_piece();

  private:
    Piece *piece;
};

static const Square EMPTY_SQUARE = Square{nullptr};
