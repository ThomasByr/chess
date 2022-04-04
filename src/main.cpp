#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "lib.h"

#include "board.h"
#include "move.h"
#include "result.h"

std::string input(std::string prompt) {
    std::string s;
    std::cout << prompt;
    std::cout.flush();

    std::getline(std::cin, s);
    return s;
}

Move get_cpu_move(Board &board, bool best) {
    std::tuple<Move, unsigned, double> r;
    if (best) {
        r = board.get_next_best_move(4);
    } else {
        r = board.get_next_worst_move(4);
    }

    Move m = std::get<0>(r);
    unsigned count = std::get<1>(r);
    std::cout << "CPU evaluated " << count << " moves before choosing to ";
    std::cout.flush();

    Piece *from;
    Piece *to;
    switch (m.move_type()) {
    case Move::PieceMove:
        from = board.get_piece(m.from());
        to = board.get_piece(m.to());
        if (from != nullptr && to != nullptr) {
            std::cout << "take " << to->get_name() << "(" << m.to() << ") ";
            std::cout << "with " << from->get_name() << "(" << m.from() << ")"
                      << std::endl;
        } else if (from != nullptr && to == nullptr) {
            std::cout << "move " << from->get_name() << "(" << m.from() << ") ";
            std::cout << "to " << m.to() << std::endl;
        } else {
            std::cout << "move " << m.from() << " to " << m.to() << std::endl;
        }
        break;
    case Move::KingSideCastle:
        std::cout << "castle kingside" << std::endl;
        break;
    case Move::QueenSideCastle:
        std::cout << "castle queenside" << std::endl;
        break;
    case Move::Resign:
        std::cout << "resign" << std::endl;
        break;
    case Move::Invalid:
        std::cout << "fliptables" << std::endl;
        break;
    }
    return m;
}

std::string trim(const std::string &s) {
    std::string::size_type first = s.find_first_not_of(' ');
    std::string::size_type last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

std::string to_lower(const std::string &s) {
    std::string r;
    for (char c : s) {
        r += tolower(c);
    }
    return r;
}

int main() {
    Board board = Board::new_board();
    std::cout << board << std::endl;

    std::vector<Move> history = std::vector<Move>();
    bool is_running = true;

    while (is_running) {
        std::string s = input(">>> ");
        if (!s.empty()) {
            s = to_lower(trim(s));
        }

        Move m;
        if (s.empty() || s == "best" || s == "b") {
            std::cout << "Waiting for CPU to choose best move..." << std::endl;
            m = get_cpu_move(board, true);
        } else if (s == "worst" || s == "w") {
            std::cout << "Waiting for CPU to choose worst move..." << std::endl;
            m = get_cpu_move(board, false);
        } else if (s == "rate" || s == "r") {
            double score = board.score();
            std::cout << "Score: " << score << std::endl;
            continue;
        } else if (s == "pass" || s == "p") {
            board = board.change_turn();
            std::cout << board << std::endl;
            continue;
        } else if (s == "/quit") {
            is_running = false;
        } else if (s == "history") {
            for (std::vector<Move>::size_type i = 0; i < history.size(); i++) {
                if (i < history.size() - 1) {
                    std::cout << history[i] << " " << history[i + 1]
                              << std::endl;
                } else {
                    std::cout << history[i] << std::endl;
                }
            }
            continue;
        } else {
            int t = m.from_string(s);
            switch (t) {
            case Move::Invalid:
                std::cerr << "Invalid move: " << s << std::endl;
                continue;
                break;
            }
        }

        GameResult r;
        std::cout << "\n";
        switch ((r = board.play_move(m)).result_type()) {
        case GameResult::Continuing:
            board = r.next_board();
            std::cout << board << std::endl;
            history.push_back(m);
            break;
        case GameResult::Victory:
            std::cout << r.next_board() << "\n";
            std::cout << !r.winner() << " loses. " << r.winner()
                      << " is victorious." << std::endl;
            history.push_back(m);
            is_running = false;
            board = r.next_board();
            break;
        case GameResult::IllegalMove:
            if (is_running) {
                std::cerr << r.move() << " is an illegal move." << std::endl;
            }
            break;
        case GameResult::Stalemate:
            std::cout << "Drawn game." << std::endl;
            history.push_back(m);
            is_running = false;
            board = r.next_board();
            break;
        }
    }

    for (Move m : history) {
        std::cout << m << std::endl;
    }
    std::cout << board.end_fen() << std::endl;
    return 0;
}
