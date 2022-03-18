#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "lib.h"

class Position {
  public:
    Position();
    Position(int row, int col);
    Position(const std::string &position_string);
    ~Position();

    static const Position king_position(Color color);
    static const Position queen_position(Color color);

    bool is_on_board() const;
    bool is_off_board() const;

    int get_row() const;
    int get_col() const;

    Position add_row(int row) const;
    Position add_col(int col) const;

    bool is_diagonal_to(const Position &other) const;
    int diagonal_distance(const Position &other) const;

    bool is_orthogonal_to(const Position &other) const;
    int orthogonal_distance(const Position &other) const;

    bool is_adjacent_to(const Position &other) const;
    bool is_below(const Position &other) const;
    bool is_above(const Position &other) const;
    bool is_left_of(const Position &other) const;
    bool is_right_of(const Position &other) const;

    Position next_below() const;
    Position next_above() const;

    Position pawn_up(Color ally_color) const;
    Position pawn_back(Color ally_color) const;

    Position next_left() const;
    Position next_right() const;

    bool is_starting_pawn(Color color) const;
    bool is_kingside_rook() const;
    bool is_queenside_rook() const;

    std::vector<Position> diagonals_to(const Position &to) const;
    std::vector<Position> orthogonals_to(const Position &to) const;

    bool is_knight_move(const Position &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Position &position);

    bool operator==(const Position &other) const;

  private:
    int row;
    int col;
};

const Position A1 = Position(0, 0);
const Position A2 = Position(1, 0);
const Position A3 = Position(2, 0);
const Position A4 = Position(3, 0);
const Position A5 = Position(4, 0);
const Position A6 = Position(5, 0);
const Position A7 = Position(6, 0);
const Position A8 = Position(7, 0);

const Position B1 = Position(0, 1);
const Position B2 = Position(1, 1);
const Position B3 = Position(2, 1);
const Position B4 = Position(3, 1);
const Position B5 = Position(4, 1);
const Position B6 = Position(5, 1);
const Position B7 = Position(6, 1);
const Position B8 = Position(7, 1);

const Position C1 = Position(0, 2);
const Position C2 = Position(1, 2);
const Position C3 = Position(2, 2);
const Position C4 = Position(3, 2);
const Position C5 = Position(4, 2);
const Position C6 = Position(5, 2);
const Position C7 = Position(6, 2);
const Position C8 = Position(7, 2);

const Position D1 = Position(0, 3);
const Position D2 = Position(1, 3);
const Position D3 = Position(2, 3);
const Position D4 = Position(3, 3);
const Position D5 = Position(4, 3);
const Position D6 = Position(5, 3);
const Position D7 = Position(6, 3);
const Position D8 = Position(7, 3);

const Position E1 = Position(0, 4);
const Position E2 = Position(1, 4);
const Position E3 = Position(2, 4);
const Position E4 = Position(3, 4);
const Position E5 = Position(4, 4);
const Position E6 = Position(5, 4);
const Position E7 = Position(6, 4);
const Position E8 = Position(7, 4);

const Position F1 = Position(0, 5);
const Position F2 = Position(1, 5);
const Position F3 = Position(2, 5);
const Position F4 = Position(3, 5);
const Position F5 = Position(4, 5);
const Position F6 = Position(5, 5);
const Position F7 = Position(6, 5);
const Position F8 = Position(7, 5);

const Position G1 = Position(0, 6);
const Position G2 = Position(1, 6);
const Position G3 = Position(2, 6);
const Position G4 = Position(3, 6);
const Position G5 = Position(4, 6);
const Position G6 = Position(5, 6);
const Position G7 = Position(6, 6);
const Position G8 = Position(7, 6);

const Position H1 = Position(0, 7);
const Position H2 = Position(1, 7);
const Position H3 = Position(2, 7);
const Position H4 = Position(3, 7);
const Position H5 = Position(4, 7);
const Position H6 = Position(5, 7);
const Position H7 = Position(6, 7);
const Position H8 = Position(7, 7);
