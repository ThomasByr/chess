#include "move.h"

Move::Move() {
    from_ = Position();
    to_ = Position();
    move_type_ = Invalid;
}

Move::~Move() {}

const int &Move::move_type() const { return move_type_; }

int &Move::move_type() { return move_type_; }

void Move::move_type(const int &move_type) {
    move_type_ = std::move(move_type);
}

Position &Move::from() { return from_; }

Position &Move::to() { return to_; }

const Position &Move::from() const { return from_; }

const Position &Move::to() const { return to_; }

void Move::from(const Position &from) { from_ = std::move(from); }

void Move::to(const Position &to) { to_ = std::move(to); }

int Move::update_from_string(const std::string &move_string) {
    if (move_string == "resign" || move_string == "resigns") {
        this->move_type_ = Resign;
        return Resign;
    } else if (move_string == "queenside castle" ||
               move_string == "castle queenside" || move_string == "O-O-O" ||
               move_string == "0-0-0" || move_string == "o-o-o") {
        this->move_type_ = QueenSideCastle;
        return QueenSideCastle;
    } else if (move_string == "kingside castle" ||
               move_string == "castle kingside" || move_string == "O-O" ||
               move_string == "0-0" || move_string == "o-o") {
        this->move_type_ = KingSideCastle;
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
            from_ = Position(move_parts[0].substr(0, 2));
            to_ = Position(move_parts[0].substr(2, 2));
            this->move_type_ = PieceMove;
            return PieceMove;
        } else if (move_parts.size() == 2) {
            from_ = Position(move_parts[0]);
            to_ = Position(move_parts[1]);
            this->move_type_ = PieceMove;
            return PieceMove;
        } else if (move_parts.size() == 3 &&
                   (move_parts[1] == "to" || move_parts[1] == "->")) {
            from_ = Position(move_parts[0]);
            to_ = Position(move_parts[2]);
            this->move_type_ = PieceMove;
            return PieceMove;
        } else {
            this->move_type_ = Invalid;
            return Invalid;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    switch (move.move_type_) {
    case Move::PieceMove:
        return os << move.from_ << " to " << move.to_;
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
