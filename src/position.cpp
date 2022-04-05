#include "position.h"

Position::Position() {
    row_ = -1;
    col_ = -1;
}

Position::Position(int row, int col) {
    this->row_ = row;
    this->col_ = col;
}

Position::Position(const std::string &position_string) {
    if (position_string.size() != 2) {
        row_ = -1;
        col_ = -1;
    } else {
        row_ = position_string[1] - '1';
        col_ = position_string[0] - 'a';
    }
}

Position::~Position() {}

std::ostream &operator<<(std::ostream &os, const Position &position) {
    os << (char)('a' + position.col_) << (position.row_ + 1);
    return os;
}

bool Position::operator==(const Position &other) const {
    return row_ == other.row_ && col_ == other.col_;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

const Position Position::king_position(Color color) {
    switch (color) {
    case Color::White:
        return Position(0, 4);
    case Color::Black:
        return Position(7, 4);
    default:
        panic("Invalid color");
    }
}

const Position Position::queen_position(Color color) {
    switch (color) {
    case Color::White:
        return Position(0, 3);
    case Color::Black:
        return Position(7, 3);
    default:
        panic("Invalid color");
    }
}

bool Position::is_off_board() const {
    return row_ < 0 || row_ > 7 || col_ < 0 || col_ > 7;
}

bool Position::is_on_board() const { return !is_off_board(); }

const int &Position::row() const { return row_; }

const int &Position::col() const { return col_; }

int &Position::row() { return row_; }

int &Position::col() { return col_; }

void Position::row(const int &row) { row_ = std::move(row); }

void Position::col(const int &col) { col_ = std::move(col); }

Position Position::add_row(int row) const {
    return Position(this->row_ + row, this->col_);
}

Position Position::add_col(int col) const {
    return Position(this->row_, this->col_ + col);
}

bool Position::is_diagonal_to(const Position &other) const {
    return abs(row_ - other.row_) == abs(col_ - other.col_);
}

int Position::diagonal_distance(const Position &other) const {
    return abs(row_ - other.row_);
}

bool Position::is_orthogonal_to(const Position &other) const {
    return row_ == other.row_ || col_ == other.col_;
}

int Position::orthogonal_distance(const Position &other) const {
    return abs(row_ - other.row_) + abs(col_ - other.col_);
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

bool Position::is_below(const Position &other) const {
    return row_ < other.row_;
}

bool Position::is_above(const Position &other) const {
    return row_ > other.row_;
}

bool Position::is_left_of(const Position &other) const {
    return col_ < other.col_;
}

bool Position::is_right_of(const Position &other) const {
    return col_ > other.col_;
}

Position Position::next_below() const { return Position(row_ - 1, col_); }

Position Position::next_above() const { return Position(row_ + 1, col_); }

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

Position Position::next_left() const { return Position(row_, col_ - 1); }

Position Position::next_right() const { return Position(row_, col_ + 1); }

bool Position::is_starting_pawn(Color color) const {
    switch (color) {
    case Color::White:
        return row_ == 1;
    case Color::Black:
        return row_ == 6;
    default:
        panic("Invalid color");
    }
}

bool Position::is_kingside_rook() const {
    return (row_ == 0 || row_ == 7) && col_ == 7;
}

bool Position::is_queenside_rook() const {
    return (row_ == 0 || row_ == 7) && col_ == 0;
}

std::vector<Position> Position::diagonals_to(const Position &to) const {
    if (!is_diagonal_to(to)) {
        return {};
    }

    int row_step, col_step;
    if (is_left_of(to)) {
        col_step = 1;
    } else {
        col_step = -1;
    }

    if (is_below(to)) {
        row_step = 1;
    } else {
        row_step = -1;
    }

    Position acc = *this;
    std::vector<Position> result;
    for (int i = 0; i < diagonal_distance(to); i++) {
        acc = acc.add_row(row_step).add_col(col_step);
        result.push_back(acc);
    }

    return result;
}

std::vector<Position> Position::orthogonals_to(const Position &to) const {
    if (!is_orthogonal_to(to)) {
        return {};
    }

    int row_step = 0, col_step = 0;
    if (is_left_of(to)) {
        col_step = 1;
    } else if (is_right_of(to)) {
        col_step = -1;
    } else if (is_above(to)) {
        row_step = -1;
    } else if (is_below(to)) {
        row_step = 1;
    }

    Position acc = *this;
    std::vector<Position> result;
    for (int i = 0; i < orthogonal_distance(to); i++) {
        acc = acc.add_row(row_step).add_col(col_step);
        result.push_back(acc);
    }

    return result;
}

bool Position::is_knight_move(const Position &other) const {
    return (abs(row_ - other.row_) == 2 && abs(col_ - other.col_) == 1) ||
           (abs(row_ - other.row_) == 1 && abs(col_ - other.col_) == 2);
}
