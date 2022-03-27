#pragma once

#include <iostream>
#include <string>

#include "lib.h"

#include "move.h"
#include "position.h"

static double WHITE_KING_POSITION_WEIGHTS[8][8] = {
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
    {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
};

static double BLACK_KING_POSITION_WEIGHTS[8][8] = {
    {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
    {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
};

static double WHITE_QUEEN_POSITION_WEIGHTS[8][8] = {
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
    {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
    {-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
    {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
    {-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
    {-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-1.0, -0.0, -1.0, -0.5, -0.5, -0.5, -1.0, -2.0},
};

static double BLACK_QUEEN_POSITION_WEIGHTS[8][8] = {
    {-1.0, -0.0, -1.0, -0.5, -0.5, -0.5, -1.0, -2.0},
    {-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
    {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
    {-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
    {-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
    {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
};

static double WHITE_ROOK_POSITION_WEIGHTS[8][8] = {
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0},
};

static double BLACK_ROOK_POSITION_WEIGHTS[8][8] = {
    {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
    {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
};

static double WHITE_BISHOP_POSITION_WEIGHTS[8][8] = {
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
    {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
    {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
    {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
    {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
};

static double BLACK_BISHOP_POSITION_WEIGHTS[8][8] = {
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
    {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
    {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
    {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
    {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
    {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
};

static double WHITE_KNIGHT_POSITION_WEIGHTS[8][8] = {
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
    {-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
    {-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
    {-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
    {-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
    {-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
};

static double BLACK_KNIGHT_POSITION_WEIGHTS[8][8] = {
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
    {-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
    {-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
    {-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
    {-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
    {-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
};

static double WHITE_PAWN_POSITION_WEIGHTS[8][8] = {
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
    {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
    {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
    {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
    {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
    {0.5, 1.5, -1.0, -2.0, -2.0, 1.0, 1.5, 0.5},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
};

static double BLACK_PAWN_POSITION_WEIGHTS[8][8] = {
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    {0.5, 1.5, -1.0, -2.0, -2.0, 1.0, 1.5, 0.5},
    {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
    {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
    {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
    {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
    {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
};

class Piece {
  public:
    static const int None = 0;
    static const int King = 1;
    static const int Pawn = 2;
    static const int Knight = 3;
    static const int Bishop = 4;
    static const int Rook = 5;
    static const int Queen = 6;

    static const int White = 8;
    static const int Black = 16;

    static const int type_mask = 0b00111;
    static const int black_mask = 0b10000;
    static const int white_mask = 0b01000;
    static const int color_mask = black_mask | white_mask;

    Piece(Color color, Position position);
    virtual ~Piece();

    Color get_color() const;
    Position get_pos() const;

    int get_type() const;

    std::vector<Move> get_valid_moves(std::vector<Move> &result, Board &board);

    virtual std::string get_name() const = 0;
    virtual int get_material_value() const = 0;
    virtual double get_weighted_value() const = 0;

    virtual bool is_starting_pawn() const = 0;
    virtual bool is_queenside_rook() const = 0;
    virtual bool is_kingside_rook() const = 0;

    virtual std::vector<Move> get_legal_moves(Board &board) = 0;
    virtual bool is_legal_move(const Position &new_pos, Board &board) = 0;
    virtual bool is_legal_attack(const Position &new_pos, Board &board) = 0;

    virtual Piece *move_to(Position new_pos) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);

  protected:
    int id;
    Color color;
    Position position;
};

class Pawn : public Piece {
  public:
    Pawn(Color color, Position position);
    ~Pawn();

    Pawn *move_to(Position new_pos) const;

    std::string get_name() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    friend std::ostream &operator<<(std::ostream &os, const Pawn &pawn);
};
