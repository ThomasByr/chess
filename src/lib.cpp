#include "lib.h"

void panic(const std::string &msg) {
    std::stringstream ss;
    ss << FG_RED << "panic: " << msg << " (" << strerror(errno) << ")" << RST
       << std::endl;
    throw std::runtime_error(ss.str());
}

bool ask(const std::string &msg) {
    std::string answer;
    input(answer, msg);
    answer = to_lower(trim(answer));
    return answer == "y" || answer == "yes";
}

Color operator!(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}

std::ostream &operator<<(std::ostream &os, Color color) {
    switch (color) {
    case Color::White:
        return os << "White";
    case Color::Black:
        return os << "Black";
    default:
        panic("Invalid color");
    }
}

std::ostream &operator<<(std::ostream &os, State state) {
    switch (state) {
    case State::CPU_THINKING:
        return os << "cpu thinking or evaluating";
    case State::WAITING_FOR_INPUT:
        return os << "thread waiting for input";
    case State::PROGRAM_STARTING:
        return os << "program starting, allocating memory";
    case State::SORTING_MOVES:
        return os << "cpu is sorting best moves";
    case State::MOVING_PIECE:
        return os << "a piece is moving";
    case State::CHECKING_CHECK:
        return os << "checking if the king is in check";
    case State::CHECKING_CHECKMATE:
        return os << "checking if the king is in checkmate";
    case State::CHECKING_STALEMATE:
        return os << "checking if the game is a stalemate";
    case State::GETTING_LEGAL_MOVES:
        return os << "cpu getting all legal moves";
    case State::PLAYING_MOVES:
        return os << "cpu playing moves";
    case State::HANDLING_SIGNAL:
        return os << "os handling signal";
    case State::REGISTERING_EXIT:
        return os << "os registering exit";
    case State::PARSING_MOVE:
        return os << "parsing user input move";
    case State::DISPLAYING_CPU_MOVE:
        return os << "displaying cpu move as string";
    case State::PARSING_ARGS:
        return os << "parsing command line arguments";
    case State::CHECKING_ARGS:
        return os << "checking command line arguments";
    case State::WRITING_OSTREAM:
        return os << "writing to ostream (long write)";
    default:
        panic("Invalid state");
    }
}

std::string repeat(std::string str, const unsigned n) {
    if (n == 0) {
        str.clear();
        str.shrink_to_fit();
        return str;
    } else if (n == 1 || str.empty()) {
        return str;
    }
    const auto period = str.size();
    if (period == 1) {
        str.append(n - 1, str.front());
        return str;
    }
    str.reserve(period * n);
    unsigned m = 2;
    for (; m < n; m *= 2)
        str += str;
    str.append(str.c_str(), (n - (m / 2)) * period);
    return str;
}

std::string operator*(std::string str, unsigned n) {
    return repeat(std::move(str), n);
}

void input(std::string &str, const std::string &prompt) {
    // launch a thread to handle input
    state = State::WAITING_FOR_INPUT;
    std::thread([&str, &prompt]() {
        std::cout << prompt;
        std::cout.flush();
        std::getline(std::cin, str);
    }).join();
}

std::string trim(const std::string &s) {
    std::string::size_type first = s.find_first_not_of(' ');
    std::string::size_type last = s.find_last_not_of(' ');

    // std::string::npos is returned if all characters are whitespace
    // in this case s.substr returns an empty string, which is what we want
    return (first == std::string::npos || last == std::string::npos)
               ? std::string()
               : s.substr(first, last - first + 1);
}

std::string to_lower(const std::string &s) {
    std::string r;
    for (char c : s) {
        r += tolower(c);
    }
    return r;
}

std::string get_time(const int64_t &time) {
    // transform time in ms to time in xh:ymin:zsec:ms
    std::stringstream ss;
    int64_t ms = time % 1000;
    int64_t s = time / 1000;
    int64_t m = s / 60;
    int64_t h = m / 60;
    m %= 60;
    s %= 60;
    ss << h << "h:" << m << "min:" << s << "sec:" << ms << "ms";
    
    return ss.str();
}
