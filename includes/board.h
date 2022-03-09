#pragma once

#include "lib.h"
#include "position.h"
#include "square.h"

class CastlingRights {
  public:
    CastlingRights();
    ~CastlingRights();

    bool can_kingside_castle() const;
    bool can_queenside_castle() const;

    void disable_kingside();
    void disable_queenside();
    void disable_all();

    void enable_kingside();
    void enable_queenside();
    void enable_all();

  private:
    bool kingside;
    bool queenside;
};

class Board {
  private:
    Square squares[64];
    Position *en_passant;

    CastlingRights *black_castling_rights;
    CastlingRights *white_castling_rights;

    Color turn;
};

class BoardBuilder {
  public:
    BoardBuilder();
    BoardBuilder(const Board &board);
    ~BoardBuilder();

  private:
    Board *board;
};
