#include "position.h"

Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row, int col) {
    this->row = row;
    this->col = col;
}

Position::Position(const std::string &position_string) {
    if (position_string.size() != 2) {
        row = -1;
        col = -1;
    } else {
        row = position_string[1] - '1';
        col = position_string[0] - 'a';
    }
}

Position::~Position() {}

std::ostream &operator<<(std::ostream &os, const Position &position) {
    os << (char)('a' + position.col) << (position.row + 1);
    return os;
}

const Position Position::king_position(Color color) {
    switch (color) {
    case Color::White:
        return Position(7, 4);
    case Color::Black:
        return Position(0, 4);
    default:
        return Position();
    }
}

bool Position::is_off_board() const {
    return row < 0 || row > 7 || col < 0 || col > 7;
}

bool Position::is_on_board() const { return !is_off_board(); }

int Position::get_row() const { return row; }

int Position::get_col() const { return col; }

Position Position::add_row(int row) const {
    return Position(this->row + row, this->col);
}

Position Position::add_col(int col) const {
    return Position(this->row, this->col + col);
}

bool Position::is_diagonal_to(const Position &other) const {
    return abs(row - other.row) == abs(col - other.col);
}

int Position::diagonal_distance(const Position &other) const {
    return abs(row - other.row);
}

bool Position::is_orthogonal_to(const Position &other) const {
    return row == other.row || col == other.col;
}

int Position::orthogonal_distance(const Position &other) const {
    return abs(row - other.row) + abs(col - other.col);
}

bool Position::is_adjacent_to(const Position &other) const {
    if (is_orthogonal_to(other)) {
        return orthogonal_distance(other) == 1;
    } else if (is_diagonal_to(other)) {
        return diagonal_distance(other) == 1;
    } else {
        return false;
    }
}

bool Position::is_below(const Position &other) const { return row < other.row; }

bool Position::is_above(const Position &other) const { return row > other.row; }

bool Position::is_left_of(const Position &other) const {
    return col < other.col;
}

bool Position::is_right_of(const Position &other) const {
    return col > other.col;
}

Position Position::next_below() const { return Position(row - 1, col); }

Position Position::next_above() const { return Position(row + 1, col); }

Position Position::pawn_up(Color ally_color) const {
    switch (ally_color) {
    case Color::White:
        return next_above();
    case Color::Black:
        return next_below();
    default:
        return Position();
    }
}

Position Position::pawn_back(Color ally_color) const {
    return pawn_up(!ally_color);
}

Position Position::next_left() const { return Position(row, col - 1); }

Position Position::next_right() const { return Position(row, col + 1); }

bool Position::is_starting_pawn(Color color) const {
    switch (color) {
    case Color::White:
        return row == 1;
    case Color::Black:
        return row == 6;
    default:
        return false;
    }
}
