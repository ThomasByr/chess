#include "piece.h"

Piece::Piece(Color color, Position position) {
    this->color = color;
    this->position = position;

    switch (color) {
    case Color::White:
        this->id = Piece::White;
        break;
    case Color::Black:
        this->id = Piece::Black;
        break;
    default:
        this->id = Piece::None;
        break;
    }
}

Piece::~Piece() {}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
    (void)piece;
    os << "?";
    return os;
}

Color Piece::get_color() const { return this->color; }

Position Piece::get_pos() const { return this->position; }

int Piece::get_type() const { return this->id & Piece::type_mask; }

Pawn::Pawn(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Pawn;
}

Pawn::~Pawn() {}

std::ostream &operator<<(std::ostream &os, const Pawn &pawn) {
    switch (pawn.get_color()) {
    case Color::White:
        os << "\u2659";
        break;
    case Color::Black:
        os << "\u265F";
        break;
    default:
        os << "?";
        break;
    }
    return os;
}

Pawn *Pawn::move_to(Position new_pos) const {
    return new Pawn(this->color, new_pos);
}

std::string Pawn::get_name() const { return "pawn"; }

int Pawn::get_material_value() const { return 1; }

double Pawn::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_PAWN_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_PAWN_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool Pawn::is_starting_pawn() const {
    return this->get_pos().is_starting_pawn(this->get_color());
}

bool Pawn::is_queenside_rook() const { return false; }

bool Pawn::is_kingside_rook() const { return false; }

std::vector<Move> Pawn::get_legal_moves(const Board &board) const {
    (void)board;
    return std::vector<Move>();
}

bool Pawn::is_legal_move(const Position &new_pos, const Board &board) const {
    (void)new_pos;
    (void)board;
    return false;
}

bool Pawn::is_legal_attack(const Position &new_pos, const Board &board) const {
    (void)new_pos;
    (void)board;
    return false;
}
