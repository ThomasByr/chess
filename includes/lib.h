#pragma once

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define __AUTHOR__ "ThomasByr"

#define __VERSION_MAJOR__ 0
#define __VERSION_MINOR__ 1
#define __VERSION_PATCH__ 0

#ifndef DEBUG
#define std_debug(msg) (void)msg;
#else
#define std_debug(msg) std::cout << msg << std::endl;
#endif

#define chk(op)           \
    do {                  \
        if ((op) == -1) { \
            panic(#op);   \
        }                 \
    } while (0)

void panic [[noreturn]] (const std::string &msg);

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

std::string input(std::string prompt);

std::string trim(const std::string &s);

std::string to_lower(const std::string &s);
