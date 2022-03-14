#pragma once

#include "lib.h"
#include "move.h"
#include "piece.h"
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

    double value_for(const Color &ally_color) const;
    Color get_current_player_color() const;

    Board apply_eval_move(const Move &move) const; // todo
    std::vector<Move> get_legal_moves() const;     // todo

    std::tuple<Move, unsigned, double> get_next_best_move(int depth) const;
    std::tuple<Move, unsigned, double> get_next_worst_move(int depth) const;
    double minimax(int depth, double alpha, double beta, bool is_maximizing,
                   Color getting_move_for, unsigned board_count) const;

    CastlingRights *black_castling_rights;
    CastlingRights *white_castling_rights;

    Square get_square(const Position &pos) const;
    void add_piece(Piece &piece);
    Piece *get_piece(const Position &pos);

    bool has_ally_piece(const Position &pos, const Color &ally_color);
    bool has_enemy_piece(const Position &pos, const Color &enemy_color);
    bool has_piece(const Position &pos);
    bool has_no_piece(const Position &pos);

    Position get_king_position(const Color &color) const;

    bool is_threatened(const Position &pos, const Color &ally_color) const;
    bool is_in_check(const Color &color) const;

    Board move_piece(const Position &from, const Position &to) const;

    bool can_kingside_castle(const Color &color) const;
    bool can_queenside_castle(const Color &color) const;

    bool has_sufficient_material(const Color &color) const;
    bool has_insufficient_material(const Color &color) const;

    bool is_stalemate() const;
    bool is_checkmate() const;

    Board change_turn() const;

    Board apply_move(const Move &move) const;

    GameResult play_move(const Move &move);

    std::string rating_bar() const;
    Color get_turn_color() const;
    Position *get_en_passant() const;

    Board remove_all(const Color &color) const;
    Board queen_all(const Color &color) const;

    Board set_turn(const Color &color) const;

    int get_material_advantage(const Color &color) const;

    bool is_legal_move(const Move &move, const Color &player_color) const;

  private:
    Square squares[64];
    Position *en_passant;

    Color turn;
};

class BoardBuilder {
  public:
    BoardBuilder();
    BoardBuilder(const Board &board);
    ~BoardBuilder();

    BoardBuilder row(const Piece &piece);
    BoardBuilder column(const Piece &piece);

    BoardBuilder piece(Piece *piece);
    BoardBuilder enable_castling();
    BoardBuilder disable_castling();

    BoardBuilder enable_queenside_castle(const Color &color);
    BoardBuilder disable_queenside_castle(const Color &color);

    BoardBuilder enable_kingside_castle(const Color &color);
    BoardBuilder disable_kingside_castle(const Color &color);

    Board build() const;

  private:
    Board *board;
};
