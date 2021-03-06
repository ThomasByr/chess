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
    while (pos.col() > 0) {
        pos = pos.next_left();
    } // move to leftmost position

    for (int i = 0; i < 8; i++) {
        this->board->set_square(pos, Square::from_piece(piece.move_to(pos)));
        pos = pos.next_right();
    } // move to rightmost position and set square

    return *this;
}

BoardBuilder BoardBuilder::column(const Piece &piece) {
    Position pos = piece.get_pos();
    while (pos.row() > 0) {
        pos = pos.next_below();
    } // move to bottommost position

    for (int i = 0; i < 8; i++) {
        this->board->set_square(pos, Square::from_piece(piece.move_to(pos)));
        pos = pos.next_above();
    } // move to topmost position and set square

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
        squares[i] = EMPTY_SQUARE; // set all squares to empty
    }
    turn = Color::White;
    white_castling_rights = new CastlingRights();
    black_castling_rights = new CastlingRights();
    en_passant = nullptr;

    for (unsigned i = 0; i < 7; i++) {
        white_takes[i] = 0;
        black_takes[i] = 0;
    }
}

Board::Board(const Board &board) {
    for (unsigned i = 0; i < 64; i++) {
        squares[i] = Square(board.squares[i]); // copy all squares
    }
    turn = board.turn;
    en_passant = board.en_passant;
    white_castling_rights = new CastlingRights(*board.white_castling_rights);
    black_castling_rights = new CastlingRights(*board.black_castling_rights);

    for (unsigned i = 0; i < 7; i++) {
        white_takes[i] = board.white_takes[i];
        black_takes[i] = board.black_takes[i];
    }
}

Board Board::new_board() {
    BoardBuilder builder;

    // fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
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

    // board.turn = Color::White;
    // board.en_passant = nullptr;

    return board;
}

Board Board::from_fen(const std::string &fen) {
    static const std::map<char, int> piece_map = {
        {'k', Piece::King},   {'q', Piece::Queen},  {'r', Piece::Rook},
        {'b', Piece::Bishop}, {'n', Piece::Knight}, {'p', Piece::Pawn},
    };

    BoardBuilder builder;
    std::string fen_board = fen.substr(0, fen.find(' '));
    int file = 0, rank = 7, piece_id;

    for (const unsigned char c : fen_board) {
        assert_debug(file <= 8 && rank >= -1);
        if (c == '/') {
            file = 0;
            rank--;
        } else {
            if (isdigit(c)) {
                file += c - '0';
            } else {
                try {
                    piece_id = piece_map.at(tolower(c));
                } catch (std::out_of_range &e) {
                    throw std::invalid_argument("Invalid piece in FEN");
                }
                assert_debug(file < 8 && rank > -1);
                Color color = isupper(c) ? Color::White : Color::Black;
                Position pos = Position(rank, file);

                Piece *piece_ptr = Piece::from_id(piece_id, color, pos);
                std::stringstream ss;
                ss << "Placing " << piece_ptr->to_string() << " at " << pos;
                std_debug(ss.str());

                builder.piece(piece_ptr);
                file++;
            }
        }
    }

    // get turn
    Color turn =
        fen.find("w") != std::string::npos ? Color::White : Color::Black;

    // get castling rights
    std::string castling_rights = fen.substr(fen.find(' ') + 1);
    if (castling_rights.find('K') != std::string::npos) {
        std_debug("Enabling white kingside castle");
        builder.enable_kingside_castle(Color::White);
    }
    if (castling_rights.find('Q') != std::string::npos) {
        std_debug("Enabling white queenside castle");
        builder.enable_queenside_castle(Color::White);
    }
    if (castling_rights.find('k') != std::string::npos) {
        std_debug("Enabling black kingside castle");
        builder.enable_kingside_castle(Color::Black);
    }
    if (castling_rights.find('q') != std::string::npos) {
        std_debug("Enabling black queenside castle");
        builder.enable_queenside_castle(Color::Black);
    }

    // get en passant
    std::string en_passant =
        castling_rights.substr(castling_rights.find(' ', 5) + 1);
    std::stringstream ss;
    Position *en_passant_pos;
    // std::cout << en_passant << std::endl;
    if (en_passant.find('-') == std::string::npos) {
        en_passant_pos = new Position(en_passant.substr(0, 2));
        ss << "En passant at " << *en_passant_pos;
        std_debug(ss.str());
    } else {
        en_passant_pos = nullptr;
        ss << "No en passant";
        std_debug(ss.str());
    }

    Board board = builder.build();
    board.set_turn(turn);
    board.en_passant = en_passant_pos;

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
        Piece *piece = square.get_piece();
        if (piece == nullptr) {
            continue;
        }

        if (piece->get_color() == ally_color) {
            sum += piece->get_weighted_value();
        } else {
            sum -= piece->get_weighted_value();
        }
    }
    return sum;
}

Color Board::get_current_player_color() const { return this->turn; }

Square Board::get_square(const Position &pos) const {
    return this->squares[((7 - pos.row()) * 8 + pos.col())];
}

void Board::set_square(const Position &pos, const Square &square) {
    this->squares[((7 - pos.row()) * 8 + pos.col())] = square;
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
    Position king_pos = Position(-1, -1);
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

        // if the square position is either not in the same file or rank,
        // not in the same diagonal, as the position we are checking,
        // or does not represent a knight move, we can skip it
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
    state = State::CHECKING_CHECK;
    Position king_pos = this->get_king_position(color);
    if (king_pos.is_off_board()) {
        return false;
    } else {
        return this->is_threatened(king_pos, color);
    }
}

bool Board::is_legal_move(const Move &move, const Color &player_color,
                          const bool &cpu) {
    bool tmp;
    Piece *piece;
    Position *en_passant, from, to;

    switch (move.move_type()) {
    case Move::Invalid:
        return false;
    case Move::KingSideCastle:
        return this->can_kingside_castle(player_color);
    case Move::QueenSideCastle:
        return this->can_queenside_castle(player_color);
    case Move::Resign:
        return true;
    case Move::PieceMove:
        from = move.from();
        to = move.to();

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
            return tmp ||
                   (piece->is_legal_move(to, *this) &&
                    piece->get_color() == player_color &&
                    !this->apply_move(move, cpu).is_in_check(player_color));

        default:
            return piece->is_legal_move(to, *this) &&
                   piece->get_color() == player_color &&
                   !this->apply_move(move, cpu).is_in_check(player_color);
        }
    default:
        panic("Invalid move type");
    }
    return false;
}

Board Board::apply_eval_move(const Move &move, const bool &cpu) {
    state = State::PLAYING_MOVES;
    return this->apply_move(move, cpu).change_turn();
}

std::vector<Move> Board::get_legal_moves() {
    state = State::GETTING_LEGAL_MOVES;
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

Board Board::move_piece(const Position &from, const Position &to,
                        const bool &cpu) {
    Board result = Board(*this);
    result.en_passant = nullptr;

    if (from.is_off_board() || to.is_off_board()) {
        return result;
    }
    Square from_square = result.get_square(from);
    Square to_square = result.get_square(to);

    if (from_square.is_empty()) {
        return result;
    }

    // updating piece cemetery
    if (!to_square.is_empty()) {
        Piece *to_piece = to_square.get_piece();
        if (to_piece->get_color() == result.get_current_player_color()) {
            // this should not even happen assuming the move has been verified
            panic("Trying to move a piece onto an ally piece");
        }
        switch (!to_piece->get_color()) {
        case Color::White:
            result.white_takes[to_piece->get_type()] += 1;
            break;
        case Color::Black:
            result.black_takes[to_piece->get_type()] += 1;
            break;
        default:
            panic("Invalid color");
        }
    }

    Piece *piece = from_square.get_piece();
    result.set_square(from, Square::from_piece(nullptr));

    if ((piece->get_type() == Piece::Pawn) &&
        (to.row() == 0 || to.row() == 7)) {

        if (cpu) {
            // the cpu will always choose the queen
            // TODO: make the cpu choose the best piece
            piece = new Queen(piece->get_color(), piece->get_pos());
        } else {
            // ask the user what piece to promote to
            bool valid = false;
            while (!valid) {
                std::string promote;
                input(promote, "Promote to: ");
                promote = to_lower(trim(promote));

                if (promote.empty() || promote == "queen" || promote == "q") {
                    piece = new Queen(piece->get_color(), piece->get_pos());
                    valid = true;
                } else if (promote == "rook" || promote == "r") {
                    piece = new Rook(piece->get_color(), piece->get_pos());
                    valid = true;
                } else if (promote == "bishop" || promote == "b") {
                    piece = new Bishop(piece->get_color(), piece->get_pos());
                    valid = true;
                } else if (promote == "knight" || promote == "n") {
                    piece = new Knight(piece->get_color(), piece->get_pos());
                    valid = true;
                } else {
                    std::cerr << "Invalid piece type" << std::endl;
                }
            }
        }
    }

    if ((piece->is_starting_pawn()) && abs(from.row() - to.row()) == 2) {
        result.en_passant = new Position(to.pawn_back(piece->get_color()));
    }

    result.add_piece(piece->move_to(to));

    // check for castling validity
    CastlingRights *castling_rights;
    switch (piece->get_color()) {
    case Color::White:
        castling_rights = result.white_castling_rights;
        break;
    case Color::Black:
        castling_rights = result.black_castling_rights;
        break;
    default:
        panic("Invalid color");
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
               *piece == Rook(color, Position(0, 7)) &&
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
               *piece == Rook(color, Position(7, 7)) &&
               this->black_castling_rights->can_kingside_castle() &&
               !this->is_in_check(color) &&
               !this->is_threatened(right_of_king, color) &&
               !this->is_threatened(right_of_king.next_right(), color);
    }
    panic("Invalid color");
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
    panic("Invalid color");
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

    // sort the pieces based of their base material value
    std::sort(pieces.begin(), pieces.end(), [](Piece *a, Piece *b) {
        return a->get_material_value() < b->get_material_value();
    });

    // if there are no pieces, then the game is over
    // if the remaining pieces are :
    // 1. only one piece
    // 2. one knight
    // 3. one bishop
    // 4. two knights
    // 5. two bishops
    // then the current player has insufficient material
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
    // if there is no legal moves,
    // and the player is not in check,
    // or if both players have insufficient material,
    // then the game is a stalemate
    return (this->get_legal_moves().empty() &&
            !this->is_in_check(this->get_current_player_color())) ||
           (this->has_insufficient_material(this->turn) &&
            this->has_insufficient_material(!this->turn));
}

bool Board::is_checkmate() {
    // if there is no legal moves,
    // and the player is in check,
    // then the game is a checkmate
    state = State::CHECKING_CHECKMATE;
    return this->is_in_check(this->get_current_player_color()) &&
           this->get_legal_moves().empty();
}

bool Board::is_endgame() {
    std::vector<Piece *> w_pieces;
    std::vector<Piece *> b_pieces;

    for (Square square : this->squares) {
        Piece *piece = square.get_piece();
        if (piece == nullptr) {
            continue;
        }

        if (piece->get_color() == Color::White) {
            w_pieces.push_back(piece);
        } else {
            b_pieces.push_back(piece);
        }
    }

    return (w_pieces.size() <= 3 && b_pieces.size() <= 3);
}

Board Board::change_turn() {
    this->turn = !this->turn;
    return *this; // return a copy of the board
}

Board Board::apply_move(const Move &move, const bool &cpu) {
    state = State::PLAYING_MOVES;
    Position *en_passant, king_pos, rook_pos, from, to;
    Piece *piece;
    Color player_color;
    Board result;

    switch (move.move_type()) {
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
        return this->move_piece(king_pos, rook_pos.next_left(), cpu)
            .move_piece(rook_pos, king_pos.next_right(), cpu);

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
        return this->move_piece(king_pos, rook_pos.next_left().next_left(), cpu)
            .move_piece(rook_pos, king_pos.next_left(), cpu);

    case Move::PieceMove:
        from = move.from(), to = move.to();
        result = this->move_piece(from, to, cpu);

        en_passant = this->en_passant;
        piece = this->get_piece(from);

        if (en_passant != nullptr && piece != nullptr) {
            player_color = piece->get_color();
            if ((*en_passant == from.pawn_up(player_color).next_left() ||
                 *en_passant == from.pawn_up(player_color).next_right()) &&
                *en_passant == to) {
                result.squares[(7 - en_passant->pawn_back(player_color).row()) *
                                   8 +
                               en_passant->col()] = EMPTY_SQUARE;
            }
        }
        return result;

    case Move::Resign:
        return this->remove_all(this->turn).queen_all(!this->turn);
    }

    panic("Invalid move type");
}

GameResult Board::play_move(const Move &move, const bool &cpu) {
    state = State::PLAYING_MOVES;
    Color current_color = this->get_current_player_color();
    GameResult result;

    if (move.move_type() == Move::Resign) {
        result.result_type() = GameResult::Victory;
        result.next_board() =
            this->remove_all(current_color).queen_all(!current_color);
        result.winner() = !current_color;
    } else if (this->is_legal_move(move, current_color, cpu)) {
        Board next_turn = this->apply_move(move, cpu).change_turn();
        if (next_turn.is_checkmate()) {
            result.result_type() = GameResult::Victory;
            result.winner() = current_color;
        } else if (next_turn.is_stalemate()) {
            result.result_type() = GameResult::Stalemate;
        } else {
            result.result_type() = GameResult::Continuing;
        }
        result.next_board() = next_turn;
    } else {
        result.result_type() = GameResult::IllegalMove;
        result.move() = move;
    }

    return result;
}

std::string Board::rating_bar(unsigned len) {
    std::tuple<Move, unsigned, double> best0 = this->get_next_best_move(0);
    std::tuple<Move, unsigned, double> worst0 = this->get_next_worst_move(0);
    Move best_m = std::get<0>(best0);
    double your_best_val = std::get<2>(best0),
           your_lowest_val = std::get<2>(worst0);
    double your_val = your_best_val + your_lowest_val;

    std::tuple<Move, unsigned, double> best1 =
        this->apply_move(best_m, true).change_turn().get_next_best_move(0);
    std::tuple<Move, unsigned, double> worst1 =
        this->apply_move(best_m, true).change_turn().get_next_worst_move(0);
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
    std::tuple<Move, unsigned, double> best0 = this->get_next_best_move(0);
    std::tuple<Move, unsigned, double> worst0 = this->get_next_worst_move(0);
    Move best_m = std::get<0>(best0);
    double your_best_val = std::get<2>(best0),
           your_lowest_val = std::get<2>(worst0);
    double your_val = your_best_val + your_lowest_val;

    std::tuple<Move, unsigned, double> best1 =
        this->apply_move(best_m, true).change_turn().get_next_best_move(0);
    std::tuple<Move, unsigned, double> worst1 =
        this->apply_move(best_m, true).change_turn().get_next_worst_move(0);
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
    state = State::WRITING_OSTREAM;
    std::string rating_bar = board.rating_bar(16);

    // this string flips over depending on whose turn it is
    std::string abc;
    switch (board.get_turn_color()) {
    case Color::White:
        abc = " a  b  c  d  e  f  g  h";
        break;
    case Color::Black:
        abc = " h  g  f  e  d  c  b  a";
        break;
    default:
        panic("Invalid color");
    }
    os << "   " << abc << "\n  ??????????????????????????????????????????????????????????????????????????????";

    Color square_color = !board.get_turn_color();
    unsigned height = 8, width = 8;

    for (unsigned row = 0; row < height; row++) {
        state = State::WRITING_OSTREAM;
        unsigned print_row = 0;
        os << "\n";
        switch (board.get_turn_color()) {
        case Color::White:
            print_row = height - row - 1;
            break;
        case Color::Black:
            print_row = row;
            break;
        default:
            panic("Invalid color");
        }
        os << print_row + 1 << " ???";

        for (unsigned col = 0; col < width; col++) {
            state = State::WRITING_OSTREAM;
            unsigned print_col = 0;
            switch (board.get_turn_color()) {
            case Color::Black:
                print_col = width - col - 1;
                break;
            case Color::White:
                print_col = col;
                break;
            default:
                panic("Invalid color");
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
                default:
                    panic("Invalid color");
                }
            }

            if (board.get_en_passant() != nullptr &&
                pos == *board.get_en_passant()) {
                os << FG_BLU << s << RST;
            } else if (board.is_threatened(pos, board.get_turn_color())) {
                os << FG_RED << s << RST;
            } else if (board.is_threatened(pos, !board.get_turn_color())) {
                os << FG_GRN << s << RST;
            } else {
                os << s;
            }

            square_color = !square_color;
        }
        os << "??? " << print_row + 1 << " ";

        if (row == 0) {
            // display material advantage
            int white_adv = board.get_material_advantage(Color::White);
            int black_adv = board.get_material_advantage(Color::Black);

            if (white_adv == black_adv) {
                os << " Both sides have equal material";
            } else if (white_adv > black_adv) {
                os << " White +" << white_adv << " points";
            } else {
                os << " Black +" << black_adv << " points";
            }
        } else if (row == 1) {
            // piece cemetery (white takes)
            for (unsigned id = 1; id < 7; id++) {
                unsigned count = board.white_takes[id];
                Piece *piece = Piece::from_id(id, Color::Black);
                if (count <= 0 || piece == nullptr) {
                    continue;
                }
                os << " " << piece->to_string() << "*" << count;
            }
        } else if (row == 2) {
            // piece cemetery (black takes)
            for (unsigned id = 1; id < 7; id++) {
                unsigned count = board.black_takes[id];
                Piece *piece = Piece::from_id(id, Color::White);
                if (count <= 0 || piece == nullptr) {
                    continue;
                }
                os << " " << piece->to_string() << "*" << count;
            }
        } else if (row == 3) {
            // display the current player's color
            os << " " << board.get_turn_color() << " to move";
        } else if (row == 4) {
            // display the rating bar
            os << " [" << rating_bar << "]";
        }

        square_color = !square_color;
    }
    os << "\n  ??????????????????????????????????????????????????????????????????????????????\n   " << abc << "\n";

    return os;
}

bool cmp(Board &board, Move a, Move b) {
    Position a_pos_from = a.from();
    Position a_pos_to = a.to();
    Position b_pos_from = b.from();
    Position b_pos_to = b.to();

    Piece *a_piece_from = board.get_piece(a_pos_from);
    Piece *a_piece_to = board.get_piece(a_pos_to);
    Piece *b_piece_from = board.get_piece(b_pos_from);
    Piece *b_piece_to = board.get_piece(b_pos_to);

    // if move a is a take, but b is not, a is better
    if (a_piece_to != nullptr && b_piece_to == nullptr) {
        return true;
    }
    // if move b is a take, but a is not, b is better
    if (b_piece_to != nullptr && a_piece_to == nullptr) {
        return false;
    }
    // if both moves are takes, compare the piece values
    if (a_piece_to != nullptr && b_piece_to != nullptr) {
        return a_piece_to->get_material_value() >
               b_piece_to->get_material_value();
    }
    // if both moves are not takes, compare the piece values
    if (a_piece_from != nullptr && b_piece_from != nullptr) {
        return a_piece_from->get_material_value() >
               b_piece_from->get_material_value();
    }

    return false;
}

std::tuple<Move, u_int64_t, double> Board::get_next_best_move(int depth) {
    state = State::GETTING_LEGAL_MOVES;
    std::vector<Move> legal_moves = this->get_legal_moves();

    state = State::SORTING_MOVES;
    std::sort(legal_moves.begin(), legal_moves.end(),
              [&](Move a, Move b) { return cmp(*this, a, b); });
    state = State::PLAYING_MOVES;

    double best_move_value = -999999.;
    Move best_move = Move();
    best_move.move_type() = Move::Resign;

    Color color = this->get_current_player_color();
    u_int64_t board_count = 0;

    for (Move m : legal_moves) {
        double child_board_value = this->apply_eval_move(m, true).minimax(
            depth, -1000000., 1000000., false, color, &board_count);

        if (child_board_value >= best_move_value) {
            best_move = m;
            best_move_value = child_board_value;
        }
    }

    return std::make_tuple(best_move, board_count, best_move_value);
}

std::tuple<Move, u_int64_t, double> Board::get_next_worst_move(int depth) {
    state = State::GETTING_LEGAL_MOVES;
    std::vector<Move> legal_moves = this->get_legal_moves();

    state = State::SORTING_MOVES;
    std::sort(legal_moves.begin(), legal_moves.end(),
              [&](Move a, Move b) { return cmp(*this, a, b); });
    state = State::PLAYING_MOVES;

    double best_move_value = -999999.;
    Move best_move = Move();
    best_move.move_type() = Move::Resign;

    Color color = this->get_current_player_color();
    u_int64_t board_count = 0;

    for (Move m : legal_moves) {
        double child_board_value = this->apply_eval_move(m, true).minimax(
            depth, -1000000., 1000000., true, !color, &board_count);

        if (child_board_value >= best_move_value) {
            best_move = m;
            best_move_value = child_board_value;
        }
    }

    return std::make_tuple(best_move, board_count, best_move_value);
}

double Board::minimax(int depth, double alpha, double beta, bool is_maximizing,
                      Color getting_move_for, u_int64_t *board_count) {
    *board_count += 1;

    if (depth <= 0) {
        return this->value_for(getting_move_for);
    }

    state = State::GETTING_LEGAL_MOVES;
    std::vector<Move> legal_moves = this->get_legal_moves();

    state = State::SORTING_MOVES;
    std::sort(legal_moves.begin(), legal_moves.end(),
              [&](Move a, Move b) { return cmp(*this, a, b); });
    state = State::PLAYING_MOVES;

    double best_move_value;

    if (is_maximizing) {
        best_move_value = -999999.;
        for (Move m : legal_moves) {
            double child_board_value = this->apply_eval_move(m, true).minimax(
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
            double child_board_value = this->apply_eval_move(m, true).minimax(
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
