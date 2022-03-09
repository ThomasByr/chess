#pragma once

#include "lib.h"
#include "move.h"
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
  public:
    Board();
    ~Board();

    double value_for(Color ally_color) const;
    Color get_current_player_color() const;
    Board apply_eval_move(const Move &move) const;
    std::vector<Move> get_legal_moves() const;

    std::tuple<Move, unsigned, double> get_next_best_move(int depth) const;
    std::tuple<Move, unsigned, double> get_next_worst_move(int depth) const;
    double minimax(int depth, double alpha, double beta, bool is_maximizing,
                   Color getting_move_for, unsigned board_count) const;

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
