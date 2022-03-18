#include "piece.h"

#include "board.h"

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

std::vector<Move> Piece::get_valid_moves(std::vector<Move> &result,
                                         Board &board) {
    Color ally_color = this->get_color();
    std::vector<Move> moves;

    for (Move move : result) {
        switch (move.move_type) {
        case Move::PieceMove:
            if (move.from.is_on_board() && move.to.is_on_board()) {
                if (board.is_legal_move(move, ally_color)) {
                    moves.push_back(move);
                }
            }
        case Move::Invalid:
            break;
        default:
            if (board.is_legal_move(move, ally_color)) {
                moves.push_back(move);
            }
        }
    }

    return moves;
}

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

std::vector<Move> Pawn::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    Position up = pos.pawn_up(ally_color);
    Position next_up = up.pawn_up(ally_color);
    Position up_left = up.next_left();
    Position up_right = up.next_right();

    Position *en_passant = board.get_en_passant();
    if (en_passant != nullptr) {
        if (*en_passant == up_left || *en_passant == up_right) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = *en_passant;
            result.push_back(move);
        }
    }

    if (next_up.is_on_board() && this->is_starting_pawn() &&
        board.has_no_piece(up) && board.has_no_piece(next_up)) {
        Move move;
        move.move_type = Move::PieceMove;
        move.from = pos;
        move.to = next_up;
        result.push_back(move);
    }

    if (up.is_on_board() && board.has_no_piece(up)) {
        Move move;
        move.move_type = Move::PieceMove;
        move.from = pos;
        move.to = up;
        result.push_back(move);
    }

    if (up_left.is_on_board() && board.has_enemy_piece(up_left, ally_color)) {
        Move move;
        move.move_type = Move::PieceMove;
        move.from = pos;
        move.to = up_left;
        result.push_back(move);
    } else if (up_right.is_on_board() &&
               board.has_enemy_piece(up_right, ally_color)) {
        Move move;
        move.move_type = Move::PieceMove;
        move.from = pos;
        move.to = up_right;
        result.push_back(move);
    }

    return this->get_valid_moves(result, board);
}

bool Pawn::is_legal_move(const Position &new_pos, Board &board) {
    (void)new_pos;
    (void)board;
    return false;
}

bool Pawn::is_legal_attack(const Position &new_pos, Board &board) {
    (void)new_pos;
    (void)board;
    return false;
}
