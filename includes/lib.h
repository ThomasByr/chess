#pragma once

#include <iostream>
#include <string>
#include <vector>

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
