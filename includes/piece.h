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

    /**
     * @brief if the piece is a sliding piece
     *
     * @param piece piece
     * @return true - is sliding piece
     * @return false - otherwise
     */
    static bool is_sliding_piece(int piece);

    /**
     * @brief Construct a new Piece object
     *
     * @param color color of the piece
     * @param position position of the piece
     */
    Piece(Color color, Position position);
    virtual ~Piece();

    /**
     * @brief Get the color object
     *
     * @return Color - enum class
     */
    Color get_color() const;
    /**
     * @brief Get the pos object
     *
     * @return Position - position
     */
    Position get_pos() const;

    /**
     * @brief get the type of the piece
     * Same as id & type_mask
     *
     * @return int - type
     */
    int get_type() const;

    /**
     * @brief returns a collection of all legal moves given all pseudo legal
     * moves
     *
     * @param result pseudo legal moves
     * @param board board
     * @return std::vector<Move> - legal moves
     */
    std::vector<Move> get_valid_moves(std::vector<Move> &result, Board &board);

    /**
     * @brief gets the name of the piece as a lowercase string
     *
     * @return std::string - string
     */
    virtual std::string get_name() const = 0;
    /**
     * @brief gets the non-standard fen notation for the piece
     *
     * @return std::string - string
     */
    virtual std::string get_fen() const = 0;
    /**
     * @brief gets the material value for a piece
     * | Name | Value |
     * |-|-|
     * | King | 99999 |
     * | Queen | 9 |
     * | Rook | 5 |
     * | Bishop | 3 |
     * | Knight | 3 |
     * | Pawn | 1 |
     *
     * @return int - value
     */
    virtual int get_material_value() const = 0;
    /** 
     * @brief Get the weighted value of a piece. This simply factors in position
     * to the pieces value. For example, a knight that is in the center is
     * more favorable than a knight on the side of the board. Similarly,
     * a king in the center of the board is highly unfavorable compared to
     * a king its respective side.
     * 
     * Additionally, the weighted value of the piece is 10 times greater than
     * its material value, plus or minus a weight ranging between 5.0 and -5.0.
     */
    virtual double get_weighted_value() const = 0;

    /**
     * @brief if the piece is a starting pawn
     * 
     * @return true - is starting pawn
     * @return false - otherwise
     */
    virtual bool is_starting_pawn() const = 0;
    /**
     * @brief if the piece is able to queenside
     * 
     * @return true - if queenside rook
     * @return false - otherwise
     */
    virtual bool is_queenside_rook() const = 0;
    /**
     * @brief if the piece is able to kingside
     * 
     * @return true - if kingside rook
     * @return false - otherwise
     */
    virtual bool is_kingside_rook() const = 0;

    /**
     * @brief returns a collection of all pseudo legal moves
     * 
     * @param board board
     * @return std::vector<Move> - pseudo legal moves
     */
    virtual std::vector<Move> get_legal_moves(Board &board) = 0;
    /**
     * @brief if the move is legal
     * 
     * @param new_pos new position
     * @param board board
     * @return true - if legal
     * @return false - otherwise
     */
    virtual bool is_legal_move(const Position &new_pos, Board &board) = 0;
    /**
     * @brief if the attack is legal
     * 
     * @param new_pos new position
     * @param board board
     * @return true - if legal
     * @return false - otherwise
     */
    virtual bool is_legal_attack(const Position &new_pos, Board &board) = 0;

    /**
     * @brief moves a piece to an other position (assuming it is legal)
     * 
     * @param new_pos new position
     * @return Piece* - new piece
     */
    virtual Piece *move_to(Position new_pos) const = 0;

    /**
     * @brief returns the visual representation of the piece
     *
     * @param os ostream
     * @return std::ostream& - ostream
     */
    virtual std::ostream &operator<<(std::ostream &os) const = 0;
    /**
     * @brief performs equality check on two pieces
     * 
     * @param other other piece
     * @return true - if equal (same color, type and position)
     * @return false - otherwise
     */
    bool operator==(const Piece &other) const;
    /**
     * @brief returns the fmt string representation
     * 
     * @return std::string - string
     */
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
