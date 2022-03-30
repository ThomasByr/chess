#include "board.h"

#include "piece.h"
#include "result.h"

CastlingRights::CastlingRights() {
    kingside = true;
    queenside = true;
}

CastlingRights::~CastlingRights() {}

bool CastlingRights::can_kingside_castle() const { return this->kingside; }

bool CastlingRights::can_queenside_castle() const { return this->queenside; }

void CastlingRights::disable_kingside() { this->kingside = false; }

void CastlingRights::disable_queenside() { this->queenside = false; }

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

BoardBuilder::~BoardBuilder() {}

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
    for (int i = 0; i < 64; i++) {
        squares[i] = EMPTY_SQUARE;
    }
    turn = Color::White;
    white_castling_rights = new CastlingRights();
    black_castling_rights = new CastlingRights();
    en_passant = nullptr;
}

// Board::Board(const Board &board) {
//     for (int i = 0; i < 64; i++) {
//         squares[i] = board.squares[i];
//     }
//     turn = board.turn;
//     en_passant = board.en_passant;
//     white_castling_rights = new CastlingRights(*board.white_castling_rights);
//     black_castling_rights = new CastlingRights(*board.black_castling_rights);
// }

Board Board::new_board() {
    BoardBuilder builder;
    Board board = builder.piece(new Pawn(Color::White, B1))
                      .piece(new Pawn(Color::White, B2))
                      .build();
    board.turn = Color::White;
    board.en_passant = nullptr;
    return board;
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

void Board::add_piece(Piece *piece) {
    Position pos = piece->get_pos();
    this->get_square(pos) = Square::from_piece(piece);
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
    Piece *piece;
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

        piece = this->get_piece(from);
        if (piece == nullptr) {
            return false;
        }
        switch (piece->get_type()) {
        case Piece::None:
            return false;

        case Piece::Pawn:
            en_passant = this->en_passant;
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

Board Board::apply_eval_move(const Move &move) {
    return this->apply_move(move).change_turn();
}

std::vector<Move> Board::get_legal_moves() {
    std::vector<Move> result;
    Color color = this->get_current_player_color();

    for (Square square : this->squares) {
        if (square.is_empty()) {
            continue;
        }
        Piece *piece = square.get_piece();
        if (piece->get_color() != color) {
            continue;
        }
        std::vector<Move> moves = piece->get_legal_moves(*this);
        for (Move m : moves) {
            result.push_back(m);
        }
    }
    return result;
}

Board Board::move_piece(const Position &from, const Position &to) {
    Board result = Board(*this);
    result.en_passant = nullptr;

    if (from.is_off_board() || to.is_off_board()) {
        return result;
    }
    Square from_square = result.get_square(from);

    if (from_square.is_empty()) {
        return result;
    }
    Piece *piece = from_square.get_piece();
    // Square from_square = EMPTY_SQUARE;

    if ((piece->get_type() == Piece::Pawn) &&
        (to.get_row() == 0 || to.get_row() == 7)) {
        piece = new Queen(piece->get_color(), piece->get_pos());
    }

    if ((piece->is_starting_pawn()) &&
        abs(from.get_row() - to.get_row()) == 2) {
        result.en_passant = new Position(to.pawn_back(piece->get_color()));
    }

    result.add_piece(piece->move_to(to));

    CastlingRights *castling_rights;
    switch (piece->get_color()) {
    case Color::White:
        castling_rights = result.white_castling_rights;
        break;
    case Color::Black:
        castling_rights = result.black_castling_rights;
        break;
    default:
        return result;
    }

    if (piece->get_type() == Piece::King) {
        castling_rights->disable_all();
    } else if (piece->is_queenside_rook()) {
        castling_rights->disable_queenside();
    } else if (piece->is_kingside_rook()) {
        castling_rights->disable_kingside();
    }

    return result;
}

bool Board::can_kingside_castle(const Color &color) {
    Position right_of_king = Position::king_position(color).next_right();
    Piece *piece;
    switch (color) {
    case Color::White:
        piece = this->get_piece(Position(0, 7));
        if (piece == nullptr) {
            return false;
        }
        return this->has_no_piece(Position(0, 5)) &&
               this->has_no_piece(Position(0, 6)) &&
               *piece == Rook(Color::White, Position(0, 7)) &&
               this->white_castling_rights->can_kingside_castle() &&
               !this->is_in_check(color) &&
               !this->is_threatened(right_of_king, color) &&
               !this->is_threatened(right_of_king.next_right(), color);
    case Color::Black:
        piece = this->get_piece(Position(7, 7));
        if (piece == nullptr) {
            return false;
        }
        return this->has_no_piece(Position(7, 5)) &&
               this->has_no_piece(Position(7, 6)) &&
               *piece == Rook(Color::White, Position(7, 7)) &&
               this->black_castling_rights->can_kingside_castle() &&
               !this->is_in_check(color) &&
               !this->is_threatened(right_of_king, color) &&
               !this->is_threatened(right_of_king.next_right(), color);
    }
    return false;
}

bool Board::can_queenside_castle(const Color &color) {
    Piece *piece;
    switch (color) {
    case Color::White:
        piece = this->get_piece(Position(0, 0));
        if (piece == nullptr) {
            return false;
        }
        return this->has_no_piece(Position(0, 1)) &&
               this->has_no_piece(Position(0, 2)) &&
               this->has_no_piece(Position(0, 3)) &&
               *piece == Rook(color, Position(0, 0)) &&
               this->white_castling_rights->can_queenside_castle() &&
               !this->is_in_check(color) &&
               !this->is_threatened(Position::queen_position(color), color);
    case Color::Black:
        piece = this->get_piece(Position(7, 0));
        if (piece == nullptr) {
            return false;
        }
        return this->has_no_piece(Position(7, 1)) &&
               this->has_no_piece(Position(7, 2)) &&
               this->has_no_piece(Position(7, 3)) &&
               *piece == Rook(color, Position(7, 0)) &&
               this->black_castling_rights->can_queenside_castle() &&
               !this->is_in_check(color) &&
               !this->is_threatened(Position::queen_position(color), color);
    }
    return false;
}

bool Board::has_sufficient_material(const Color &color) const {
    std::vector<Piece *> pieces;
    for (Square square : this->squares) {
        if (square.is_empty()) {
            continue;
        }
        Piece *piece = square.get_piece();
        if (piece->get_color() == color) {
            pieces.push_back(piece);
        }
    }

    std::sort(pieces.begin(), pieces.end(), [](Piece *a, Piece *b) {
        return a->get_material_value() < b->get_material_value();
    });

    if (pieces.size() == 0) {
        return false;
    } else if (pieces.size() == 1 && pieces[0]->get_type() == Piece::King) {
        return false;
    } else if (pieces.size() == 2 && pieces[0]->get_type() == Piece::King &&
               pieces[1]->get_type() == Piece::Knight) {
        return false;
    } else if (pieces.size() == 2 && pieces[0]->get_type() == Piece::King &&
               pieces[1]->get_type() == Piece::Bishop) {
    } else if (pieces.size() == 3 && pieces[0]->get_type() == Piece::King &&
               pieces[1]->get_type() == Piece::Knight &&
               pieces[2]->get_type() == Piece::Knight) {
        return false;
    } else if (pieces.size() == 3 && pieces[0]->get_type() == Piece::King &&
               pieces[1]->get_type() == Piece::Bishop &&
               pieces[2]->get_type() == Piece::Bishop) {
        return false;
    }
    return true;
}

bool Board::has_insufficient_material(const Color &color) const {
    return !this->has_sufficient_material(color);
}

bool Board::is_stalemate() {
    return (this->get_legal_moves().empty() &&
            !this->is_in_check(this->get_current_player_color())) ||
           (this->has_insufficient_material(this->turn) &&
            this->has_insufficient_material(!this->turn));
}

bool Board::is_checkmate() {
    return this->is_in_check(this->get_current_player_color()) &&
           this->get_legal_moves().empty();
}

Board Board::change_turn() {
    this->turn = !this->turn;
    return *this;
}

Board Board::apply_move(const Move &move) {
    Position *en_passant, king_pos, rook_pos, from, to;
    Piece *piece;
    Color player_color;
    Board result;

    switch (move.move_type) {
    case Move::KingSideCastle:
        king_pos = this->get_king_position(this->turn);
        if (king_pos.is_off_board()) {
            return *this;
        }
        switch (this->turn) {
        case Color::White:
            rook_pos = Position(0, 7);
            break;
        case Color::Black:
            rook_pos = Position(7, 7);
            break;
        }
        return this->move_piece(king_pos, rook_pos.next_left())
            .move_piece(rook_pos, king_pos.next_right());

    case Move::QueenSideCastle:
        king_pos = this->get_king_position(this->turn);
        if (king_pos.is_off_board()) {
            return *this;
        }
        switch (this->turn) {
        case Color::White:
            rook_pos = Position(0, 0);
            break;
        case Color::Black:
            rook_pos = Position(7, 0);
            break;
        }
        return this->move_piece(king_pos, rook_pos.next_left().next_left())
            .move_piece(rook_pos, king_pos.next_left());

    case Move::PieceMove:
        from = move.from, to = move.to;
        result = this->move_piece(from, to);

        en_passant = this->en_passant;
        piece = this->get_piece(from);

        if (en_passant != nullptr && piece != nullptr) {
            player_color = piece->get_color();
            if ((*en_passant == from.pawn_up(player_color).next_left() ||
                 *en_passant == from.pawn_up(player_color).next_right()) &&
                *en_passant == to) {
                result.squares[(7 -
                                en_passant->pawn_back(player_color).get_row()) *
                                   8 +
                               en_passant->get_col()] = EMPTY_SQUARE;
            }
        }
        return result;

    case Move::Resign:
        return this->remove_all(this->turn).queen_all(!this->turn);
    }
    
    return *this;
}
