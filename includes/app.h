#include <chrono>
#include <csignal>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <getopt.h>
#include <unistd.h>

#include "lib.h"

#include "board.h"
#include "move.h"
#include "result.h"

/**
 * @brief The App class
 *
 * This class represents the main loop of the chess game.
 */
class App {
  public:
    /**
     * @brief Construct a new App
     *
     * @param argc number of arguments
     * @param argv array of strings
     */
    App(int argc, char *argv[]);
    ~App();

    const std::string &fen() const;      // accessor
    const std::string &moves() const;    // accessor
    const std::string &filename() const; // accessor
    const bool &verbose() const;         // accessor
    const bool &quiet() const;           // accessor
    const bool &help() const;            // accessor
    const bool &version() const;         // accessor
    const bool &license() const;         // accessor

    std::string &fen();      // mutator
    std::string &moves();    // mutator
    std::string &filename(); // mutator
    bool &verbose();         // mutator
    bool &quiet();           // mutator
    bool &help();            // mutator
    bool &version();         // mutator
    bool &license();         // mutator

    void fen(const std::string &fen);           // mutator
    void moves(const std::string &moves);       // mutator
    void filename(const std::string &filename); // mutator
    void verbose(const bool verbose);           // mutator
    void quiet(const bool quiet);               // mutator
    void help(const bool help);                 // mutator
    void version(const bool version);           // mutator
    void license(const bool license);           // mutator

    /**
     * @brief gets the move played by CPU
     *
     * @param board board
     * @param best if get best move
     * @return Move - move
     */
    Move get_cpu_move(Board &board, bool best);
    /**
     * @brief run the app until either the user quits the app
     * or there is no legal move left for the current player
     *
     * @return int - exit code
     */
    int run();

    void get_help [[noreturn]] (const std::string &msg = "");
    void get_version [[noreturn]] ();
    void get_license [[noreturn]] ();

    /**
     * @brief parse the command line arguments
     *
     * @param argc number of arguments
     * @param argv array of strings
     */
    void parse_args(int argc, char *argv[]);
    /**
     * @brief checks parsed arguments
     *
     */
    void check_args();

    friend std::ostream &operator<<(std::ostream &os, const App &app);

  private:
    std::string fen_;      // starting fen or blank
    std::string moves_;    // starting moves to be played on game launch
    std::string filename_; // filename to load a play
    bool verbose_;         // verbose mode
    bool quiet_;           // quiet mode
    bool help_;            // display help
    bool version_;         // display version
    bool license_;         // display small license

    int64_t white_thinking_time; // white thinking time
    int64_t black_thinking_time; // black thinking time

    unsigned count_sigint; // count registered sigint
};
