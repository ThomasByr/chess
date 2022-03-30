#pragma once

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

void panic [[noreturn]] (const std::string &msg);

class Square;
class Move;
class Position;
class Board;
class GameResult;
class Piece;

class Pawn;

/**
 * @brief The Color class
 *
 * This class represents the color of a player.
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
