#pragma once

#include "lib.h"
#include "piece.h"

class Square {
  public:
    Square();
    Square(Piece *piece);
    ~Square();

    static Square from_piece(Piece *piece);
    bool is_empty();
    Piece *get_piece();

  private:
    Piece *piece;
};

static const Square EMPTY_SQUARE = Square();
