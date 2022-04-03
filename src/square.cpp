#include "square.h"

Square Square::from_piece(Piece *piece) {
    if (piece == nullptr) {
        return Square(nullptr);
    }
    return Square{piece};
}

Square::Square() { this->piece = nullptr; }

Square::Square(Piece *piece) { this->piece = piece; }

// Square::Square(const Square &square) { this->piece = square.piece; }

Square::~Square() {}

bool Square::is_empty() const { return this->piece == nullptr; }

Piece *Square::get_piece() const { return this->piece; }
