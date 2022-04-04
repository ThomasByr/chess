#include "result.h"

GameResult::GameResult() { result_type_ = IllegalMove; }

GameResult::~GameResult() {}

const int &GameResult::result_type() const { return result_type_; }

int &GameResult::result_type() { return result_type_; }

void GameResult::result_type(const int &result_type) {
    result_type_ = std::move(result_type);
}

const Color &GameResult::winner() const { return winner_; }

Color &GameResult::winner() { return winner_; }

void GameResult::winner(const Color &winner) { winner_ = std::move(winner); }

const Board &GameResult::next_board() const { return next_board_; }

Board &GameResult::next_board() { return next_board_; }

void GameResult::next_board(const Board &next_board) {
    next_board_ = std::move(next_board);
}

const Move &GameResult::move() const { return move_; }

Move &GameResult::move() { return move_; }

void GameResult::move(const Move &move) { move_ = std::move(move); }
