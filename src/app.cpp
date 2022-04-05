#include "app.h"

std::string input(std::string prompt) {
    std::string s;
    std::cout << prompt;
    std::cout.flush();

    std::getline(std::cin, s);
    return s;
}

Move App::get_cpu_move(Board &board, bool best) {
    std::tuple<Move, unsigned, double> r;

    auto start = std::chrono::high_resolution_clock::now();
    if (best) {
        r = board.get_next_best_move(4);
    } else {
        r = board.get_next_worst_move(4);
    }
    auto end = std::chrono::high_resolution_clock::now();

    Move m = std::get<0>(r);
    unsigned count = std::get<1>(r);
    double score = std::get<2>(r);
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

    if (this->verbose()) {
        std::cout << "CPU score: " << score << std::endl;
        std::cout << "Took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         end - start)
                         .count()
                  << "ms" << std::endl;
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

App::App(int argc, char *argv[]) {
    fen_ = "";
    moves_ = "";
    filename_ = "";
    verbose_ = false;
    quiet_ = false;
    help_ = false;
    version_ = false;

    parse_args(argc, argv);
    check_args();
}

App::~App() {}

const std::string &App::fen() const { return fen_; }

const std::string &App::moves() const { return moves_; }

const std::string &App::filename() const { return filename_; }

const bool &App::verbose() const { return verbose_; }

const bool &App::quiet() const { return quiet_; }

const bool &App::help() const { return help_; }

const bool &App::version() const { return version_; }

std::string &App::fen() { return fen_; }

std::string &App::moves() { return moves_; }

std::string &App::filename() { return filename_; }

bool &App::verbose() { return verbose_; }

bool &App::quiet() { return quiet_; }

bool &App::help() { return help_; }

bool &App::version() { return version_; }

void App::fen(const std::string &fen) { fen_ = std::move(fen); }

void App::moves(const std::string &moves) { moves_ = std::move(moves); }

void App::filename(const std::string &filename) {
    filename_ = std::move(filename);
}

void App::verbose(const bool verbose) { verbose_ = std::move(verbose); }

void App::quiet(const bool quiet) { quiet_ = std::move(quiet); }

void App::help(const bool help) { help_ = std::move(help); }

void App::version(const bool version) { version_ = std::move(version); }

void App::parse_args(int argc, char *argv[]) {
    int opt;
    const struct option long_options[] = {
        {"fen", required_argument, nullptr, 'f'},
        {"moves", required_argument, nullptr, 'm'},
        {"filename", required_argument, nullptr, 'n'},
        {"verbose", no_argument, nullptr, 'v'},
        {"quiet", no_argument, nullptr, 'q'},
        {"help", no_argument, nullptr, 'h'},
        {"version", no_argument, nullptr, 'V'},
        {nullptr, 0, nullptr, 0}};

    const char *short_options = "f:m:n:vqhV";
    std::stringstream ss;

    while ((opt = getopt_long(argc, argv, short_options, long_options,
                              nullptr)) != -1) {
        switch (opt) {
        case 'f':
            fen_ = optarg;
            break;
        case 'm':
            moves_ = optarg;
            break;
        case 'n':
            filename_ = optarg;
            break;
        case 'v':
            verbose_ = true;
            break;
        case 'q':
            quiet_ = true;
            break;
        case 'h':
            help_ = true;
            break;
        case 'V':
            version_ = true;
            break;
        default:
            ss << "Unknown option: " << (char)opt << std::endl;
            get_help(ss.str());
            panic("");
        }
    }
}

void App::check_args() {
    if (help_) {
        get_help();
    }
    if (version_) {
        get_version();
    }

    if (verbose_ && quiet_) {
        get_help("--verbose and --quiet are mutually exclusive");
        panic("");
    }
}

void App::get_version() {
    std::stringstream ss;
    ss << "chess-cli"
       << "\nversion: " << __VERSION_MAJOR__ << "." << __VERSION_MINOR__ << "."
       << __VERSION_PATCH__ << "\n";
    std::cout << ss.str();
    std::cout.flush();
    exit(0);
}

void App::get_help(const std::string &msg) {
    int status = msg.empty() ? 0 : 1;
    std::stringstream ss;

    if (!msg.empty()) {
        ss << "runtime exception: " << msg << "\n\n";
    }

    ss << "chess-cli"
       << "\nversion: " << __VERSION_MAJOR__ << "." << __VERSION_MINOR__ << "."
       << __VERSION_PATCH__ << "\n";
    ss << "usage: chess-cli [OPTION]...\n";
    ss << "  -f, --fen      FEN\n";
    ss << "  -m, --moves    MOVES\n";
    ss << "  -n, --filename FILENAME\n";
    ss << "  -v, --verbose\n";
    ss << "  -q, --quiet\n";
    ss << "  -h, --help\n";
    ss << "  -V, --version\n";
    ss << "\n";
    ss << "Report bugs on <https://github.com/ThomasByr/chess/issues>\n";
    ss << "chess-cli home page: <https://github.com/ThomasByr/chess>\n";
    ss << "\n";

    std::cout << ss.str();

    exit(status);
}

std::ostream &operator<<(std::ostream &os, const App &app) {
    os << "fen: " << app.fen() << "\n";
    os << "moves: " << app.moves() << "\n";
    os << "filename: " << app.filename() << "\n";
    os << "verbose: " << app.verbose() << "\n";
    os << "quiet: " << app.quiet() << "\n";
    os << "help: " << app.help() << "\n";
    os << "version: " << app.version() << "\n";
    return os;
}

int App::run() {
    Board board = Board::new_board();
    if (!this->quiet()) {
        std::cout << board << std::endl;
    }

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
            int t = m.update_from_string(s);
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
            if (!this->quiet()) {
                std::cout << board << std::endl;
            }
            history.push_back(m);
            break;
        case GameResult::Victory:
            if (!this->quiet()) {
                std::cout << r.next_board() << "\n";
            }
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
