#include "square.h"

Square Square::from_piece(Piece *piece) {
    if (piece == nullptr) {
        return Square(nullptr);
    }
    return Square{piece};
}

Square::Square() { this->piece = nullptr; }

Square::Square(Piece *piece) { this->piece = piece; }

Square::~Square() {}

bool Square::is_empty() { return this->piece == nullptr; }

Piece *Square::get_piece() { return this->piece; }
