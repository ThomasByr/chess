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

bool Piece::is_sliding_piece(int piece) { return (piece & 0b100) != 0; }

std::ostream &Piece::operator<<(std::ostream &os) const {
    os << "?";
    return os;
}

std::string Piece::to_string() const { return "?"; }

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
            break;
        default:
            if (board.is_legal_move(move, ally_color)) {
                moves.push_back(move);
            }
            break;
        }
    }

    return moves;
}

bool Piece::operator==(const Piece &piece) const {
    return this->get_color() == piece.get_color() &&
           this->get_type() == piece.get_type() &&
           this->get_pos() == piece.get_pos() && this->get_pos().is_on_board();
}

Pawn::Pawn(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Pawn;
}

Pawn::~Pawn() {}

std::ostream &Pawn::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2659";
        break;
    case Color::Black:
        os << "\u265F";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string Pawn::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2659";
    case Color::Black:
        return "\u265F";
    default:
        return "!";
    }
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
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    Position up = pos.pawn_up(ally_color);
    Position up_left = up.next_left();
    Position up_right = up.next_right();

    Position *en_passant = board.get_en_passant();
    bool tmp = false;
    if (en_passant != nullptr) {
        tmp = ((*en_passant == up_left || *en_passant == up_right) &&
               new_pos == *en_passant);
    }

    return tmp ||
           (this->is_starting_pawn() && board.has_no_piece(new_pos) &&
            board.has_no_piece(up) && new_pos == up.pawn_up(ally_color)) ||
           (board.has_enemy_piece(new_pos, ally_color) && new_pos == up_left) ||
           (board.has_enemy_piece(new_pos, ally_color) &&
            new_pos == up_right) ||
           (board.has_no_piece(new_pos) && new_pos == up);
}

bool Pawn::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    Position up = pos.pawn_up(ally_color);
    Position *en_passant = board.get_en_passant();
    bool tmp = false;
    if (en_passant != nullptr) {
        tmp = ((*en_passant == up.next_left() ||
                *en_passant == up.next_right()) &&
               new_pos == *en_passant);
    }

    return tmp || new_pos == up.next_left() || new_pos == up.next_right();
}

King::King(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::King;
}

King::~King() {}

std::ostream &King::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2654";
        break;
    case Color::Black:
        os << "\u265A";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string King::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2654";
    case Color::Black:
        return "\u265A";
    default:
        return "!";
    }
}

King *King::move_to(Position new_pos) const {
    return new King(this->color, new_pos);
}

std::string King::get_name() const { return "king"; }

int King::get_material_value() const { return 99999; }

double King::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_KING_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_KING_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool King::is_starting_pawn() const { return false; }

bool King::is_queenside_rook() const { return false; }

bool King::is_kingside_rook() const { return false; }

std::vector<Move> King::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    for (Position p : {
             pos.next_left(),
             pos.next_right(),
             pos.next_above(),
             pos.next_below(),
             pos.next_left().next_above(),
             pos.next_left().next_below(),
             pos.next_right().next_above(),
             pos.next_right().next_below(),
         }) {
        if (p.is_on_board() && !board.has_ally_piece(p, ally_color)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = p;
            result.push_back(move);
        }
    }
    if (board.can_kingside_castle(ally_color)) {
        Move move;
        move.move_type = Move::KingSideCastle;
        result.push_back(move);
    } else if (board.can_queenside_castle(ally_color)) {
        Move move;
        move.move_type = Move::QueenSideCastle;
        result.push_back(move);
    }
    return this->get_valid_moves(result, board);
}

bool King::is_legal_move(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    return this->position.is_adjacent_to(new_pos);
}

bool King::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    return this->position.is_adjacent_to(new_pos);
}

Queen::Queen(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Queen;
}

Queen::~Queen() {}

std::ostream &Queen::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2655";
        break;
    case Color::Black:
        os << "\u265B";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string Queen::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2655";
    case Color::Black:
        return "\u265B";
    default:
        return "!";
    }
}

Queen *Queen::move_to(Position new_pos) const {
    return new Queen(this->color, new_pos);
}

std::string Queen::get_name() const { return "queen"; }

int Queen::get_material_value() const { return 9; }

double Queen::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_QUEEN_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_QUEEN_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool Queen::is_starting_pawn() const { return false; }

bool Queen::is_queenside_rook() const { return false; }

bool Queen::is_kingside_rook() const { return false; }

std::vector<Move> Queen::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    for (unsigned row = 0; row < 8; row++) {
        Position new_pos = Position(row, pos.get_col());
        if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
            new_pos.is_orthogonal_to(pos)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = new_pos;
            result.push_back(move);
        }
    }
    for (unsigned col = 0; col < 8; col++) {
        Position new_pos = Position(pos.get_row(), col);
        if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
            new_pos.is_orthogonal_to(pos)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = new_pos;
            result.push_back(move);
        }
    }
    for (unsigned row = 0; row < 8; row++) {
        for (unsigned col = 0; col < 8; col++) {
            Position new_pos = Position(row, col);
            if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
                new_pos.is_diagonal_to(pos)) {
                Move move;
                move.move_type = Move::PieceMove;
                move.from = pos;
                move.to = new_pos;
                result.push_back(move);
            }
        }
    }
    return this->get_valid_moves(result, board);
}

bool Queen::is_legal_move(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_orthogonal_to(new_pos)) {
        std::vector<Position> traveling = pos.orthogonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    } else if (pos.is_diagonal_to(new_pos)) {
        std::vector<Position> traveling = pos.diagonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Queen::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_orthogonal_to(new_pos)) {
        std::vector<Position> traveling = pos.orthogonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    } else if (pos.is_diagonal_to(new_pos)) {
        std::vector<Position> traveling = pos.diagonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Rook::Rook(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Rook;
}

Rook::~Rook() {}

std::ostream &Rook::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2656";
        break;
    case Color::Black:
        os << "\u265C";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string Rook::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2656";
    case Color::Black:
        return "\u265C";
    default:
        return "!";
    }
}

Rook *Rook::move_to(Position new_pos) const {
    return new Rook(this->color, new_pos);
}

std::string Rook::get_name() const { return "rook"; }

int Rook::get_material_value() const { return 5; }

double Rook::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_ROOK_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_ROOK_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool Rook::is_starting_pawn() const { return false; }

bool Rook::is_queenside_rook() const {
    return this->get_pos().is_queenside_rook();
}

bool Rook::is_kingside_rook() const {
    return this->get_pos().is_kingside_rook();
}

std::vector<Move> Rook::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    for (unsigned row = 0; row < 8; row++) {
        Position new_pos = Position(row, pos.get_col());
        if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
            new_pos.is_orthogonal_to(pos)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = new_pos;
            result.push_back(move);
        }
    }
    for (unsigned col = 0; col < 8; col++) {
        Position new_pos = Position(pos.get_row(), col);
        if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
            new_pos.is_orthogonal_to(pos)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = new_pos;
            result.push_back(move);
        }
    }
    return this->get_valid_moves(result, board);
}

bool Rook::is_legal_move(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_orthogonal_to(new_pos)) {
        std::vector<Position> traveling = pos.orthogonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Rook::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_orthogonal_to(new_pos)) {
        std::vector<Position> traveling = pos.orthogonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Bishop::Bishop(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Bishop;
}

Bishop::~Bishop() {}

std::ostream &Bishop::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2657";
        break;
    case Color::Black:
        os << "\u265D";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string Bishop::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2657";
    case Color::Black:
        return "\u265D";
    default:
        return "!";
    }
}

Bishop *Bishop::move_to(Position new_pos) const {
    return new Bishop(this->color, new_pos);
}

std::string Bishop::get_name() const { return "bishop"; }

int Bishop::get_material_value() const { return 3; }

double Bishop::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_BISHOP_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_BISHOP_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool Bishop::is_starting_pawn() const { return false; }

bool Bishop::is_queenside_rook() const { return false; }

bool Bishop::is_kingside_rook() const { return false; }

std::vector<Move> Bishop::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    for (unsigned row = 0; row < 8; row++) {
        for (unsigned col = 0; col < 8; col++) {
            Position new_pos = Position(row, col);
            if (new_pos != pos && !board.has_ally_piece(new_pos, ally_color) &&
                new_pos.is_diagonal_to(pos)) {
                Move move;
                move.move_type = Move::PieceMove;
                move.from = pos;
                move.to = new_pos;
                result.push_back(move);
            }
        }
    }
    return this->get_valid_moves(result, board);
}

bool Bishop::is_legal_move(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_diagonal_to(new_pos)) {
        std::vector<Position> traveling = pos.diagonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Bishop::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    Position pos = this->get_pos();
    if (pos.is_diagonal_to(new_pos)) {
        std::vector<Position> traveling = pos.diagonals_to(new_pos);
        traveling.pop_back();

        for (Position p : traveling) {
            if (board.has_piece(p)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Knight::Knight(Color color, Position position) : Piece(color, position) {
    this->id |= Piece::Knight;
}

Knight::~Knight() {}

std::ostream &Knight::operator<<(std::ostream &os) const {
    switch (this->get_color()) {
    case Color::White:
        os << "\u2658";
        break;
    case Color::Black:
        os << "\u265E";
        break;
    default:
        os << "!";
        break;
    }
    return os;
}

std::string Knight::to_string() const {
    switch (this->get_color()) {
    case Color::White:
        return "\u2658";
    case Color::Black:
        return "\u265E";
    default:
        return "!";
    }
}

Knight *Knight::move_to(Position new_pos) const {
    return new Knight(this->color, new_pos);
}

std::string Knight::get_name() const { return "knight"; }

int Knight::get_material_value() const { return 3; }

double Knight::get_weighted_value() const {
    double(*weights)[8] = {0};
    switch (this->color) {
    case Color::White:
        weights = WHITE_KNIGHT_POSITION_WEIGHTS;
        break;
    case Color::Black:
        weights = BLACK_KNIGHT_POSITION_WEIGHTS;
        break;
    }
    return weights[this->get_pos().get_row()][this->get_pos().get_col()] +
           (double)this->get_material_value() * 10.;
}

bool Knight::is_starting_pawn() const { return false; }

bool Knight::is_queenside_rook() const { return false; }

bool Knight::is_kingside_rook() const { return false; }

std::vector<Move> Knight::get_legal_moves(Board &board) {
    std::vector<Move> result;
    Color ally_color = this->get_color();
    Position pos = this->get_pos();

    for (Position p : {
             pos.next_left().next_left().next_above(),
             pos.next_left().next_above().next_above(),
             pos.next_left().next_left().next_below(),
             pos.next_left().next_below().next_below(),
             pos.next_right().next_right().next_above(),
             pos.next_right().next_above().next_above(),
             pos.next_right().next_right().next_below(),
             pos.next_right().next_below().next_below(),
         }) {
        if (p.is_on_board() && !board.has_ally_piece(p, ally_color)) {
            Move move;
            move.move_type = Move::PieceMove;
            move.from = pos;
            move.to = p;
            result.push_back(move);
        }
    }
    return this->get_valid_moves(result, board);
}

bool Knight::is_legal_move(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    return this->get_pos().is_knight_move(new_pos);
}

bool Knight::is_legal_attack(const Position &new_pos, Board &board) {
    if (board.has_ally_piece(new_pos, this->get_color()) ||
        new_pos.is_off_board()) {
        return false;
    }

    return this->get_pos().is_knight_move(new_pos);
}
