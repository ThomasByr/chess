#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include <getopt.h>
#include <unistd.h>

#define __AUTHOR__ "ThomasByr"

#define __VERSION_MAJOR__ 0
#define __VERSION_MINOR__ 1
#define __VERSION_PATCH__ 2

#define TIMEOUT 3000

#define RST "\x1b[m\x1b[0m"

#define FG_RED "\x1b[0;31m"
#define FG_GRN "\x1b[0;32m"
#define FG_YEL "\x1b[0;33m"
#define FG_BLU "\x1b[0;34m"
#define FG_MAG "\x1b[0;35m"
#define FG_CYN "\x1b[0;36m"
#define FG_WHT "\x1b[0;37m"

#define BG_BLU "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GRN "\x1b[42m"
#define BG_ORA "\x1b[43m"
#define BG_CYN1 "\x1b[44m"
#define BG_YEL "\x1b[45m"
#define BG_CYN2 "\x1b[46m"
#define BG_WHT "\x1b[47m"

#ifndef DEBUG
#define std_debug(msg) (void)msg;
#define assert_debug(cond) (void)(cond);
#else
#define std_debug(msg) std::cout << msg << std::endl;
#define assert_debug(cond) assert(cond);

#endif

#define chk(op)           \
    do {                  \
        if ((op) == -1) { \
            panic(#op);   \
        }                 \
    } while (0)

void panic [[noreturn]] (const std::string &msg);
bool ask(const std::string &msg);

class App;
class Square;
class Move;
class Position;
class Board;
class GameResult;
class Piece;

class Pawn;
class King;
class Queen;
class Knight;
class Bishop;
class Rook;

/**
 * @brief The Color class
 *
 * This class represents the color of a player/piece.
 */
enum class Color { White, Black };

/**
 * @brief The State class
 *
 * This class represents the state of the program for debug purposes.
 */
enum class State {
    CPU_THINKING,
    WAITING_FOR_INPUT,
    PROGRAM_STARTING,
    SORTING_MOVES,
    MOVING_PIECE,
    CHECKING_CHECK,
    CHECKING_CHECKMATE,
    CHECKING_STALEMATE,
    GETTING_LEGAL_MOVES,
    PLAYING_MOVES,
    HANDLING_SIGNAL,
    REGISTERING_EXIT,
    PARSING_MOVE,
    DISPLAYING_CPU_MOVE,
    PARSING_ARGS,
    CHECKING_ARGS,
    WRITING_OSTREAM,
};

/**
 * @brief not operator for enum class Color
 *
 * @param color color
 * @return Color - enum class
 */
Color operator!(Color color);

/**
 * @brief fmt a color
 *
 * @param os ostream
 * @param color color
 * @return std::ostream& - ostream
 */
std::ostream &operator<<(std::ostream &os, Color color);

/**
 * @brief fmt a state
 *
 * @param os ostream
 * @param state state
 * @return std::ostream& - ostream
 */
std::ostream &operator<<(std::ostream &os, State state);

/**
 * @brief implements repeat for a string
 *
 * @param str string
 * @param n unsigned
 * @return std::string - new string
 */
std::string repeat(std::string str, const unsigned n);

/**
 * @brief * operator for a string and an unsigned
 *
 * @param str string
 * @param n unsigned
 * @return std::string - new string
 */
std::string operator*(std::string str, unsigned n);

/**
 * @brief launches a thread to handle input
 * so that the main thread can continue
 *
 * @param str place to store input
 * @param prompt prompt to display
 */
void input(std::string &str, const std::string &prompt);

/**
 * @brief removes whitespace from the beginning and end of a string
 *
 * @param s string
 * @return std::string - new string
 */
std::string trim(const std::string &s);

/**
 * @brief makes a string lowercase
 *
 * @param s string
 * @return std::string - new string
 */
std::string to_lower(const std::string &s);

/**
 * @brief get string representation of time
 *
 * @param time time
 * @return std::string - string representation of time
 */
std::string time_to_string(const int64_t &time);

extern State state;
