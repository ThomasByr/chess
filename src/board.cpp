#include "board.h"

#include "piece.h"

CastlingRights::CastlingRights() {
    kingside = true;
    queenside = true;
}

CastlingRights::~CastlingRights() {}

bool CastlingRights::can_kingside_castle() const { return kingside; }

bool CastlingRights::can_queenside_castle() const { return queenside; }

void CastlingRights::disable_kingside() { kingside = false; }

void CastlingRights::disable_queenside() { queenside = false; }

void CastlingRights::disable_all() {
    disable_kingside();
    disable_queenside();
}

void CastlingRights::enable_kingside() { kingside = true; }

void CastlingRights::enable_queenside() { queenside = true; }

void CastlingRights::enable_all() {
    enable_kingside();
    enable_queenside();
}

BoardBuilder::BoardBuilder() {
    Board *new_board = new Board();
    new_board->white_castling_rights->disable_all();
    new_board->black_castling_rights->disable_all();
    board = new_board;
}

BoardBuilder::BoardBuilder(const Board &board) {
    this->board = new Board(board);
}

BoardBuilder::~BoardBuilder() { delete board; }

BoardBuilder BoardBuilder::row(const Piece &piece) {
    Position pos = piece.get_pos();
    while (pos.get_col() > 0) {
        pos = pos.next_left();
    }

    for (int i = 0; i < 8; i++) {
        this->board->get_square(pos) = Square::from_piece(piece.move_to(pos));
        pos = pos.next_right();
    }

    return *this;
}

BoardBuilder BoardBuilder::column(const Piece &piece) {
    Position pos = piece.get_pos();
    while (pos.get_row() > 0) {
        pos = pos.next_below();
    }

    for (int i = 0; i < 8; i++) {
        this->board->get_square(pos) = Square::from_piece(piece.move_to(pos));
        pos = pos.next_above();
    }

    return *this;
}

BoardBuilder BoardBuilder::piece(Piece *piece) {
    Position pos = piece->get_pos();
    this->board->get_square(pos) = Square::from_piece(piece);
    return *this;
}

BoardBuilder BoardBuilder::enable_castling() {
    this->board->white_castling_rights->enable_all();
    this->board->black_castling_rights->enable_all();
    return *this;
}

BoardBuilder BoardBuilder::disable_castling() {
    this->board->white_castling_rights->disable_all();
    this->board->black_castling_rights->disable_all();
    return *this;
}

BoardBuilder BoardBuilder::enable_queenside_castle(const Color &color) {
    switch (color) {
    case Color::White:
        this->board->white_castling_rights->enable_queenside();
        break;
    case Color::Black:
        this->board->black_castling_rights->enable_queenside();
        break;
    }
    return *this;
}

BoardBuilder BoardBuilder::disable_queenside_castle(const Color &color) {
    switch (color) {
    case Color::White:
        this->board->white_castling_rights->disable_queenside();
        break;
    case Color::Black:
        this->board->black_castling_rights->disable_queenside();
        break;
    }
    return *this;
}

BoardBuilder BoardBuilder::enable_kingside_castle(const Color &color) {
    switch (color) {
    case Color::White:
        this->board->white_castling_rights->enable_kingside();
        break;
    case Color::Black:
        this->board->black_castling_rights->enable_kingside();
        break;
    }
    return *this;
}

BoardBuilder BoardBuilder::disable_kingside_castle(const Color &color) {
    switch (color) {
    case Color::White:
        this->board->white_castling_rights->disable_kingside();
        break;
    case Color::Black:
        this->board->black_castling_rights->disable_kingside();
        break;
    }
    return *this;
}

Board BoardBuilder::build() const { return *board; }

Board::Board() {
    BoardBuilder builder;
    *this = builder.piece(new Pawn(Color::White, B1))
                .piece(new Pawn(Color::White, B2))
                .build();
    this->en_passant = nullptr;
}

Board::~Board() {}

double Board::value_for(const Color &ally_color) const {
    double sum = 0;
    for (Square square : squares) {
        if (square.is_empty()) {
            continue;
        }

        Piece *piece = square.get_piece();
        if (piece->get_color() == ally_color) {
            sum += piece->get_weighted_value();
        } else {
            sum -= piece->get_weighted_value();
        }
    }
    return sum;
}

Color Board::get_current_player_color() const { return turn; }

Square Board::get_square(const Position &pos) const {
    return this->squares[((7 - pos.get_row()) * 8 + pos.get_col())];
}

void Board::add_piece(Piece &piece) {
    Position pos = piece.get_pos();
    this->get_square(pos) = Square::from_piece(&piece);
}

Piece *Board::get_piece(const Position &pos) {
    if (pos.is_off_board()) {
        return nullptr;
    }
    return this->get_square(pos).get_piece();
}

bool Board::has_ally_piece(const Position &pos, const Color &ally_color) {
    Piece *piece = this->get_piece(pos);
    if (piece == nullptr) {
        return false;
    }
    return piece->get_color() == ally_color;
}

bool Board::has_enemy_piece(const Position &pos, const Color &ally_color) {
    Piece *piece = this->get_piece(pos);
    if (piece == nullptr) {
        return false;
    }
    return piece->get_color() == !ally_color;
}

bool Board::has_piece(const Position &pos) {
    return this->get_piece(pos) != nullptr;
}

bool Board::has_no_piece(const Position &pos) {
    return this->get_piece(pos) == nullptr;
}

Position Board::get_king_position(const Color &color) const {
    Position king_pos;
    for (Square square : this->squares) {
        Piece *piece = square.get_piece();
        if (piece == nullptr) {
            continue;
        }
        if (piece->get_type() == Piece::King && piece->get_color() == color) {
            king_pos = piece->get_pos();
        }
    }
    return king_pos;
}

bool Board::is_threatened(const Position &pos, const Color &ally_color) {
    for (int i = 0; i < 64; i++) {
        Square square = this->squares[i];

        int row = 7 - (i / 8);
        int col = i % 8;
        Position square_pos = Position(row, col);

        if (!square_pos.is_orthogonal_to(pos) &&
            !square_pos.is_diagonal_to(pos) &&
            !square_pos.is_knight_move(pos)) {
            continue;
        }

        Piece *piece = square.get_piece();
        if (piece == nullptr) {
            continue;
        }
        if (piece->get_color() == ally_color) {
            continue;
        }
        if (piece->is_legal_attack(pos, *this)) {
            return true;
        }
    }
    return false;
}

bool Board::is_in_check(const Color &color) {
    Position king_pos = this->get_king_position(color);
    if (king_pos.is_off_board()) {
        return false;
    } else {
        return this->is_threatened(king_pos, color);
    }
}

bool Board::is_legal_move(const Move &move, const Color &player_color) {
    bool tmp;
    Position *en_passant;

    switch (move.move_type) {
    case Move::Invalid:
        return false;
    case Move::KingSideCastle:
        return this->can_kingside_castle(player_color);
    case Move::QueenSideCastle:
        return this->can_queenside_castle(player_color);
    case Move::Resign:
        return true;
    case Move::PieceMove:
        Position from = move.from;
        Position to = move.to;

        Piece *piece = this->get_piece(from);
        if (piece == nullptr) {
            return false;
        }
        switch (piece->get_type()) {
        case Piece::Pawn:
            en_passant = this->en_passant;
            tmp = false;
            if (en_passant == nullptr) {
                tmp = false;
            } else {
                tmp =
                    ((*en_passant == from.pawn_up(player_color).next_left() ||
                      *en_passant == from.pawn_up(player_color).next_right()) &&
                     *en_passant == to) &&
                    piece->get_color() == player_color;
            }
            return tmp || (piece->is_legal_move(to, *this) &&
                           piece->get_color() == player_color &&
                           !this->apply_move(move).is_in_check(player_color));

        default:
            return piece->is_legal_move(to, *this) &&
                   piece->get_color() == player_color &&
                   !this->apply_move(move).is_in_check(player_color);
        }
    }
    return false;
}
