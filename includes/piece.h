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

    static bool is_sliding_piece(int piece);

    Piece(Color color, Position position);
    virtual ~Piece();

    Color get_color() const;
    Position get_pos() const;

    int get_type() const;

    std::vector<Move> get_valid_moves(std::vector<Move> &result, Board &board);

    virtual std::string get_name() const = 0;
    virtual std::string get_fen() const = 0;
    virtual int get_material_value() const = 0;
    virtual double get_weighted_value() const = 0;

    virtual bool is_starting_pawn() const = 0;
    virtual bool is_queenside_rook() const = 0;
    virtual bool is_kingside_rook() const = 0;

    virtual std::vector<Move> get_legal_moves(Board &board) = 0;
    virtual bool is_legal_move(const Position &new_pos, Board &board) = 0;
    virtual bool is_legal_attack(const Position &new_pos, Board &board) = 0;

    virtual Piece *move_to(Position new_pos) const = 0;

    /**
     * @brief returns the visual representation of the piece
     *
     * @param os ostream
     * @return std::ostream& - ostream
     */
    virtual std::ostream &operator<<(std::ostream &os) const = 0;
    bool operator==(const Piece &other) const;
    virtual std::string to_string() const = 0;

  protected:
    int id;            // type + color
    Color color;       // enum class
    Position position; // position on the board
};

class Pawn : public Piece {
  public:
    Pawn(Color color, Position position);
    ~Pawn();

    Pawn *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};

class King : public Piece {
  public:
    King(Color color, Position position);
    ~King();

    King *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};

class Queen : public Piece {
  public:
    Queen(Color color, Position position);
    ~Queen();

    Queen *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};

class Knight : public Piece {
  public:
    Knight(Color color, Position position);
    ~Knight();

    Knight *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};

class Bishop : public Piece {
  public:
    Bishop(Color color, Position position);
    ~Bishop();

    Bishop *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};

class Rook : public Piece {
  public:
    Rook(Color color, Position position);
    ~Rook();

    Rook *move_to(Position new_pos) const;

    std::string get_name() const;
    std::string get_fen() const;
    int get_material_value() const;
    double get_weighted_value() const;

    bool is_starting_pawn() const;
    bool is_queenside_rook() const;
    bool is_kingside_rook() const;

    std::vector<Move> get_legal_moves(Board &board);
    bool is_legal_move(const Position &new_pos, Board &board);
    bool is_legal_attack(const Position &new_pos, Board &board);

    std::ostream &operator<<(std::ostream &os) const;
    std::string to_string() const;
};
