#pragma once

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
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

Color operator!(Color color);

std::ostream &operator<<(std::ostream &os, Color color);
