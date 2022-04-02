#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "lib.h"

/**
 * @brief The Position class
 *
 * This class represents a position of a piece in the game.
 */
class Position {
  public:
    /**
     * @brief Construct a new Position object
     *
     */
    Position();
    /**
     * @brief Construct a new Position object
     *
     * @param row row number 0..=7
     * @param col col number 0..=7
     */
    Position(int row, int col);
    /**
     * @brief Construct a new Position object
     *
     * @param position_string string representing a position
     */
    Position(const std::string &position_string);
    ~Position();

    /**
     * @brief returns the position of the king when the game starts
     *
     * @param color color of the piece
     * @return const Position - position
     */
    static const Position king_position(Color color);
    /**
     * @brief returns the position of the queen when the game starts
     *
     * @param color color of the piece
     * @return const Position - position
     */
    static const Position queen_position(Color color);

    /**
     * @brief if a position is on the board
     *
     * @return true - on board
     * @return false - otherwise
     */
    bool is_on_board() const;
    /**
     * @brief if a position is off the board
     *
     * @return true - off board
     * @return false - otherwise
     */
    bool is_off_board() const;

    /**
     * @brief returns the row number
     *
     * @return int - 0..=7
     */
    int get_row() const;
    /**
     * @brief returns the col number
     *
     * @return int  - 0..=7
     */
    int get_col() const;

    /**
     * @brief makes a new position with the same col but a new row
     *
     * @param row row to add
     * @return Position - new position
     */
    Position add_row(int row) const;
    /**
     * @brief makes a new position with the same row but a new col
     *
     * @param col col to add
     * @return Position - new position
     */
    Position add_col(int col) const;

    /**
     * @brief if two positions are diagonal to each other
     *
     * @param other other position
     * @return true - diagonal
     * @return false - otherwise
     */
    bool is_diagonal_to(const Position &other) const;
    /**
     * @brief returns the diagonal distance between two positions
     * Meaning it will return the number of diagonal steps between two positions
     *
     * @param other other position
     * @return int - distance
     */
    int diagonal_distance(const Position &other) const;

    /**
     * @brief if two positions are orthogonal to each other
     * Meaning they either have the same row or same col
     *
     * @param other other position
     * @return true - orthogonal
     * @return false - otherwise
     */
    bool is_orthogonal_to(const Position &other) const;
    /**
     * @brief returns the orthogonal distance between two positions
     *
     * @param other other position
     * @return int - distance
     */
    int orthogonal_distance(const Position &other) const;

    /**
     * @brief if two positions are adjacent to each other
     *
     * @param other other position
     * @return true - adjacent
     * @return false - otherwise
     */
    bool is_adjacent_to(const Position &other) const;
    /**
     * @brief if a position is below another position
     *
     * @param other other position
     * @return true - below
     * @return false - otherwise
     */
    bool is_below(const Position &other) const;
    /**
     * @brief if a position is above another position
     *
     * @param other other position
     * @return true - above
     * @return false - otherwise
     */
    bool is_above(const Position &other) const;
    /**
     * @brief if a position is left of another position
     *
     * @param other other position
     * @return true - left
     * @return false - otherwise
     */
    bool is_left_of(const Position &other) const;
    /**
     * @brief if a position is right of another position
     *
     * @param other other position
     * @return true - right
     * @return false - otherwise
     */
    bool is_right_of(const Position &other) const;

    /**
     * @brief makes a new position below the current position
     *
     * @return Position - new position
     */
    Position next_below() const;
    /**
     * @brief makes a new position above the current position
     *
     * @return Position - new position
     */
    Position next_above() const;

    /**
     * @brief makes a new position above or below the current position
     * depending on the color of the pawn
     *
     * @param ally_color - color of the pawn
     * @return Position - new position
     */
    Position pawn_up(Color ally_color) const;
    /**
     * @brief makes a new position above or below the current position
     * depending on the color of the pawn
     *
     * @param ally_color - color of the pawn
     * @return Position - new position
     */
    Position pawn_back(Color ally_color) const;

    /**
     * @brief makes a new position left of the current position
     *
     * @return Position - new position
     */
    Position next_left() const;
    /**
     * @brief makes a new position right of the current position
     *
     * @return Position - new position
     */
    Position next_right() const;

    /**
     * @brief if a position represents a starting pawn
     *
     * @param color color of the pawn
     * @return true - starting pawn
     * @return false - otherwise
     */
    bool is_starting_pawn(Color color) const;
    /**
     * @brief if a position represents a starting rook
     *
     * @return true - starting rook
     * @return false - otherwise
     */
    bool is_kingside_rook() const;
    /**
     * @brief if a position represents a starting rook
     *
     * @return true - starting rook
     * @return false - otherwise
     */
    bool is_queenside_rook() const;

    /**
     * @brief gets a collection of positions that are diagonal to the current
     * position and heading towards the other position
     *
     * @param to other position
     * @return std::vector<Position> - positions
     */
    std::vector<Position> diagonals_to(const Position &to) const;
    /**
     * @brief gets a collection of positions that are orthogonal to the current
     * position and heading towards the other position
     *
     * @param to other position
     * @return std::vector<Position> - positions
     */
    std::vector<Position> orthogonals_to(const Position &to) const;

    /**
     * @brief if two positions represents a knight move
     * 
     * @param other - other position
     * @return true - knight move
     * @return false - otherwise
     */
    bool is_knight_move(const Position &other) const;

    /**
     * @brief fmt a position
     * 
     * @param os ostream
     * @param position position
     * @return std::ostream& - ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const Position &position);

    /**
     * @brief if two positions are equal (same row and col)
     * 
     * @param other - other position
     * @return true - equal
     * @return false - otherwise
     */
    bool operator==(const Position &other) const;

  private:
    int row; // 0-7 (0 is white the bottom row)
    int col; // 0-7 (0 is the white left column)
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
