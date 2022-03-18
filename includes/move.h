#pragma once

#include "lib.h"
#include "position.h"

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

    Move();
    ~Move();

    int from_string(const std::string &move_string);

    friend std::ostream &operator<<(std::ostream &os, const Move &move);

  private:
};
