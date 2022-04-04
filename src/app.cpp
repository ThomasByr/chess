#include "app.h"

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

const std::string App::fen() const { return fen_; }

const std::string App::moves() const { return moves_; }

const std::string App::filename() const { return filename_; }

const bool App::verbose() const { return verbose_; }

const bool App::quiet() const { return quiet_; }

const bool App::help() const { return help_; }

const bool App::version() const { return version_; }

std::string App::fen() { return fen_; }

std::string App::moves() { return moves_; }

std::string App::filename() { return filename_; }

bool App::verbose() { return verbose_; }

bool App::quiet() { return quiet_; }

bool App::help() { return help_; }

bool App::version() { return version_; }

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
