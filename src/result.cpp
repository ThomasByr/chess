#include "result.h"

GameResult::GameResult() {
    result_type_ = IllegalMove;

    // winner = Color::White;
    // next_board = Board();
    // move = Move();
}

GameResult::~GameResult() {}

const int &GameResult::result_type() const { return result_type_; }

int &GameResult::result_type() { return result_type_; }

const Color &GameResult::winner() const { return winner_; }

Color &GameResult::winner() { return winner_; }

const Board &GameResult::next_board() const { return next_board_; }

Board &GameResult::next_board() { return next_board_; }

const Move &GameResult::move() const { return move_; }

Move &GameResult::move() { return move_; }
