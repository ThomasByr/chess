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
        this->board->set_square(pos, Square::from_piece(piece.move_to(pos)));
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
        this->board->set_square(pos, Square::from_piece(piece.move_to(pos)));
        pos = pos.next_above();
    }

    return *this;
}

BoardBuilder BoardBuilder::piece(Piece *piece) {
    Position pos = piece->get_pos();
    this->board->set_square(pos, Square::from_piece(piece));
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
    Board board = builder.piece(new Rook(Color::Black, A8, true))
                      .piece(new Knight(Color::Black, B8, true))
                      .piece(new Bishop(Color::Black, C8, true))
                      .piece(new Queen(Color::Black, D8, true))
                      .piece(new King(Color::Black, E8, true))
                      .piece(new Bishop(Color::Black, F8, true))
                      .piece(new Knight(Color::Black, G8, true))
                      .piece(new Rook(Color::Black, H8, true))
                      .row(Pawn(Color::Black, A7, true))
                      .row(Pawn(Color::White, A2, true))
                      .piece(new Rook(Color::White, A1, true))
                      .piece(new Knight(Color::White, B1, true))
                      .piece(new Bishop(Color::White, C1, true))
                      .piece(new Queen(Color::White, D1, true))
                      .piece(new King(Color::White, E1, true))
                      .piece(new Bishop(Color::White, F1, true))
                      .piece(new Knight(Color::White, G1, true))
                      .piece(new Rook(Color::White, H1, true))
                      .enable_castling()
                      .build();

    board.turn = Color::White;
    board.en_passant = nullptr;

    // std::cout << board << std::endl;
    return board;
}

Board::~Board() {}

std::string Board::end_fen() const {
    std::string fen = "";

    for (unsigned row = 0; row < 8; row++) {
        for (unsigned col = 0; col < 8; col++) {
            Square s = this->get_square(Position(row, col));
            if (!s.is_empty()) {
                fen += s.get_piece()->get_fen();
            }
            fen += ",";
        }
    }
    return fen;
}

double Board::value_for(const Color &ally_color) const {
    double sum = 0;
    for (Square square : this->squares) {
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

void Board::set_square(const Position &pos, const Square &square) {
    this->squares[((7 - pos.get_row()) * 8 + pos.get_col())] = square;
}

void Board::add_piece(Piece *piece) {
    Position pos = piece->get_pos();
    this->set_square(pos, Square::from_piece(piece));
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
    result.set_square(from, Square::from_piece(nullptr));

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

    return result;
}

GameResult Board::play_move(const Move &move) {
    Color current_color = this->get_current_player_color();
    GameResult result;

    if (move.move_type == Move::Resign) {
        result.result_type = GameResult::Victory;
        result.next_board =
            this->remove_all(current_color).queen_all(!current_color);
        result.winner = !current_color;
    } else if (this->is_legal_move(move, current_color)) {
        Board next_turn = this->apply_move(move).change_turn();
        if (next_turn.is_checkmate()) {
            result.result_type = GameResult::Victory;
            result.winner = current_color;
        } else if (next_turn.is_stalemate()) {
            result.result_type = GameResult::Stalemate;
        } else {
            result.result_type = GameResult::Continuing;
        }
        result.next_board = next_turn;
    } else {
        result.result_type = GameResult::IllegalMove;
        result.move = move;
    }

    return result;
}

std::string Board::rating_bar(unsigned len) {
    std::tuple<Move, unsigned, double> best0 = this->get_next_best_move(2);
    std::tuple<Move, unsigned, double> worst0 = this->get_next_worst_move(2);
    Move best_m = std::get<0>(best0);
    double your_best_val = std::get<2>(best0),
           your_lowest_val = std::get<2>(worst0);
    double your_val = your_best_val + your_lowest_val;

    std::tuple<Move, unsigned, double> best1 =
        this->apply_move(best_m).change_turn().get_next_best_move(2);
    std::tuple<Move, unsigned, double> worst1 =
        this->apply_move(best_m).change_turn().get_next_worst_move(2);
    double their_best_val = std::get<2>(best1),
           their_lowest_val = std::get<2>(worst1);
    double their_val = their_best_val + their_lowest_val;

    if (your_val < 0) {
        your_val *= -1;
        their_val += 2 * your_val;
    }

    if (their_val < 0) {
        their_val *= -1;
        your_val += 2 * their_val;
    }

    double your_percentage = your_val / (your_val + their_val);
    double their_percentage = their_val / (your_val + their_val);

    std::string your_color, their_color, white, black;
    switch (this->turn) {
    case Color::White:
        your_color = "\u2593";
        their_color = "\u2591";
        break;
    case Color::Black:
        your_color = "\u2591";
        their_color = "\u2593";
        break;
    }

    switch (this->turn) {
    case Color::White:
        white = your_color * unsigned(double(len) * your_percentage);
        black = their_color * unsigned(double(len) * their_percentage);
        break;
    case Color::Black:
        white = their_color * unsigned(double(len) * their_percentage);
        black = your_color * unsigned(double(len) * your_percentage);
        break;
    }

    return white + black;
}

double Board::score() {
    std::tuple<Move, unsigned, double> best0 = this->get_next_best_move(2);
    std::tuple<Move, unsigned, double> worst0 = this->get_next_worst_move(2);
    Move best_m = std::get<0>(best0);
    double your_best_val = std::get<2>(best0),
           your_lowest_val = std::get<2>(worst0);
    double your_val = your_best_val + your_lowest_val;

    std::tuple<Move, unsigned, double> best1 =
        this->apply_move(best_m).change_turn().get_next_best_move(2);
    std::tuple<Move, unsigned, double> worst1 =
        this->apply_move(best_m).change_turn().get_next_worst_move(2);
    double their_best_val = std::get<2>(best1),
           their_lowest_val = std::get<2>(worst1);
    double their_val = their_best_val + their_lowest_val;

    if (your_val < 0) {
        your_val *= -1;
        their_val += 2 * your_val;
    }

    if (their_val < 0) {
        their_val *= -1;
        your_val += 2 * their_val;
    }

    return your_val - their_val;
}

Color Board::get_turn_color() const { return this->turn; }

Position *Board::get_en_passant() const { return this->en_passant; }

Board Board::remove_all(const Color &color) const {
    Board result = Board(*this);

    for (unsigned i = 0; i < 64; i++) {
        Piece *piece = result.squares[i].get_piece();
        if (piece != nullptr && piece->get_color() == color) {
            result.squares[i] = EMPTY_SQUARE;
        }
    }
    return result;
}

Board Board::queen_all(const Color &color) const {
    Board result = Board(*this);

    for (unsigned i = 0; i < 64; i++) {
        Piece *piece = result.squares[i].get_piece();
        if (piece != nullptr && piece->get_type() != Piece::King &&
            piece->get_color() == color) {
            result.squares[i] = Square(new Queen(color, piece->get_pos()));
        }
    }
    return result;
}

Board Board::set_turn(const Color &color) const {
    Board result = Board(*this);
    result.turn = color;
    return result;
}

int Board::get_material_advantage(const Color &color) const {
    int sum = 0;
    for (Square square : this->squares) {
        Piece *piece = square.get_piece();
        if (piece == nullptr) {
            continue;
        }

        if (piece->get_color() == color) {
            sum += piece->get_material_value();
        } else {
            sum -= piece->get_material_value();
        }
    }
    return sum;
}

std::ostream &operator<<(std::ostream &os, Board &board) {
    std::string rating_bar = board.rating_bar(16);

    std::string abc;
    switch (board.get_turn_color()) {
    case Color::White:
        abc = " a  b  c  d  e  f  g  h";
        break;
    case Color::Black:
        abc = " h  g  f  e  d  c  b  a";
        break;
    }
    os << "   " << abc << "\n  ╔════════════════════════╗";

    Color square_color = !board.get_turn_color();
    unsigned height = 8, width = 8;

    for (unsigned row = 0; row < height; row++) {
        unsigned print_row = 0;
        os << "\n";
        switch (board.get_turn_color()) {
        case Color::White:
            print_row = height - row - 1;
            break;
        case Color::Black:
            print_row = row;
            break;
        }
        os << print_row + 1 << " ║";

        for (unsigned col = 0; col < width; col++) {
            unsigned print_col = 0;
            switch (board.get_turn_color()) {
            case Color::Black:
                print_col = width - col - 1;
                break;
            case Color::White:
                print_col = col;
                break;
            }

            Position pos = Position(print_row, print_col);

            std::string s;
            Piece *piece = board.get_piece(pos);
            if (piece != nullptr) {
                s = " " + piece->to_string() + " ";
            } else {
                switch (square_color) {
                case Color::White:
                    s = std::string("\u2591") * 3;
                    break;
                case Color::Black:
                    s = std::string("\u2593") * 3;
                    break;
                }
            }

            if (board.get_en_passant() != nullptr &&
                pos == *board.get_en_passant()) {
                os << "\x1b[34m" << s << "\x1b[m\x1b[0m";
            } else if (board.is_threatened(pos, board.get_turn_color())) {
                os << "\x1b[31m" << s << "\x1b[m\x1b[0m";
            } else if (board.is_threatened(pos, !board.get_turn_color())) {
                os << "\x1b[32m" << s << "\x1b[m\x1b[0m";
            } else {
                os << s;
            }

            square_color = !square_color;
        }
        os << "║ " << print_row + 1 << " ";

        if (row == 2) {
            int white_adv = board.get_material_advantage(Color::White);
            int black_adv = board.get_material_advantage(Color::Black);

            if (white_adv == black_adv) {
                os << " Both sides have equal material";
            } else if (white_adv > black_adv) {
                os << " White +" << white_adv << " points";
            } else {
                os << " Black +" << black_adv << " points";
            }
        } else if (row == 3) {
            os << " " << board.get_turn_color() << " to move";
        } else if (row == 4) {
            os << " [" << rating_bar << "]";
        }

        square_color = !square_color;
    }
    os << "\n  ╚════════════════════════╝\n   " << abc << "\n";

    return os;
}

std::tuple<Move, unsigned, double> Board::get_next_best_move(int depth) {
    std::vector<Move> legal_moves = this->get_legal_moves();
    double best_move_value = -999999.;
    Move best_move = Move();
    best_move.move_type = Move::Resign;

    Color color = this->get_current_player_color();
    unsigned board_count = 0;

    for (Move m : legal_moves) {
        double child_board_value = this->apply_eval_move(m).minimax(
            depth, -1000000., 1000000., false, color, &board_count);

        if (child_board_value >= best_move_value) {
            best_move = m;
            best_move_value = child_board_value;
        }
    }

    return std::make_tuple(best_move, board_count, best_move_value);
}

std::tuple<Move, unsigned, double> Board::get_next_worst_move(int depth) {
    std::vector<Move> legal_moves = this->get_legal_moves();
    double best_move_value = -999999.;
    Move best_move = Move();
    best_move.move_type = Move::Resign;

    Color color = this->get_current_player_color();
    unsigned board_count = 0;

    for (Move m : legal_moves) {
        double child_board_value = this->apply_eval_move(m).minimax(
            depth, -1000000., 1000000., true, !color, &board_count);

        if (child_board_value >= best_move_value) {
            best_move = m;
            best_move_value = child_board_value;
        }
    }

    return std::make_tuple(best_move, board_count, best_move_value);
}

double Board::minimax(int depth, double alpha, double beta, bool is_maximizing,
                      Color getting_move_for, unsigned *board_count) {
    *board_count += 1;

    if (depth <= 0) {
        return this->value_for(getting_move_for);
    }

    std::vector<Move> legal_moves = this->get_legal_moves();
    double best_move_value;

    if (is_maximizing) {
        best_move_value = -999999.;
        for (Move m : legal_moves) {
            double child_board_value = this->apply_eval_move(m).minimax(
                depth - 1, alpha, beta, !is_maximizing, getting_move_for,
                board_count);

            if (child_board_value > best_move_value) {
                best_move_value = child_board_value;
            }
            if (best_move_value > alpha) {
                alpha = best_move_value;
            }
            if (beta <= alpha) {
                return best_move_value;
            }
        }
    } else {
        best_move_value = 999999.;
        for (Move m : legal_moves) {
            double child_board_value = this->apply_eval_move(m).minimax(
                depth - 1, alpha, beta, !is_maximizing, getting_move_for,
                board_count);

            if (child_board_value < best_move_value) {
                best_move_value = child_board_value;
            }
            if (best_move_value < beta) {
                beta = best_move_value;
            }
            if (beta <= alpha) {
                return best_move_value;
            }
        }
    }
    return best_move_value;
}
