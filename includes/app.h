#include <iostream>
#include <string>
#include <vector>

#include <getopt.h>

#include "lib.h"

class App {
  public:
    App(int argc, char *argv[]);
    ~App();

    const std::string fen() const;
    const std::string moves() const;
    const std::string filename() const;
    const bool verbose() const;
    const bool quiet() const;
    const bool help() const;
    const bool version() const;

    std::string fen();
    std::string moves();
    std::string filename();
    bool verbose();
    bool quiet();
    bool help();
    bool version();

    void fen(const std::string &fen);
    void moves(const std::string &moves);
    void filename(const std::string &filename);
    void verbose(const bool verbose);
    void quiet(const bool quiet);
    void help(const bool help);
    void version(const bool version);

    int run();

    void get_help [[noreturn]] (const std::string &msg = "");
    void get_version [[noreturn]] ();

    void parse_args(int argc, char *argv[]);
    void check_args();

  private:
    std::string fen_;      // starting fen or blank
    std::string moves_;    // starting moves to be played on game launch
    std::string filename_; // filename to load a play
    bool verbose_;         // verbose mode
    bool quiet_;           // quiet mode
    bool help_;            // display help
    bool version_;         // display version
};
