#include "move.h"

Move::Move() {
    from = Position();
    to = Position();
    move_type = Invalid;
}

Move::~Move() {}

int Move::from_string(const std::string &move_string) {
    if (move_string == "resign" || move_string == "resigns") {
        return Resign;
    } else if (move_string == "queenside castle" ||
               move_string == "castle queenside" || move_string == "O-O-O" ||
               move_string == "0-0-0" || move_string == "o-o-o") {
        move_type = QueenSideCastle;
        return QueenSideCastle;
    } else if (move_string == "kingside castle" ||
               move_string == "castle kingside" || move_string == "O-O" ||
               move_string == "0-0" || move_string == "o-o") {
        move_type = KingSideCastle;
        return KingSideCastle;
    } else {
        std::vector<std::string> move_parts;
        std::string delim = " ";
        size_t last = 0, next = 0;
        while ((next = move_string.find(delim, last)) != std::string::npos) {
            move_parts.push_back(move_string.substr(last, next - last));
            last = next + delim.length();
        }
        move_parts.push_back(move_string.substr(last));

        if (move_parts.size() == 1 && move_parts[0].size() == 4) {
            from = Position(move_parts[0].substr(0, 2));
            to = Position(move_parts[0].substr(2, 2));
            move_type = PieceMove;
            return PieceMove;
        } else if (move_parts.size() == 2) {
            from = Position(move_parts[0]);
            to = Position(move_parts[1]);
            move_type = PieceMove;
            return PieceMove;
        } else if (move_parts.size() == 3 &&
                   (move_parts[1] == "to" || move_parts[1] == "->")) {
            from = Position(move_parts[0]);
            to = Position(move_parts[2]);
            move_type = PieceMove;
            return PieceMove;
        } else {
            move_type = Invalid;
            return Invalid;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    switch (move.move_type) {
    case Move::PieceMove:
        return os << move.from << " to " << move.to;
    case Move::KingSideCastle:
        return os << "O-O";
    case Move::QueenSideCastle:
        return os << "O-O-O";
    case Move::Resign:
        return os << "Resign";
    default:
        return os << "Invalid";
    }
}
