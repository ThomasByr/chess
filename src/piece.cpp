#include "piece.h"

Piece::Piece(Color color, Position position) {
    this->color = color;
    this->position = position;
}

Piece::~Piece() {}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
    os << "?";
    return os;
}
