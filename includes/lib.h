#pragma once

#include <iostream>
#include <string>
#include <vector>

class Square;
class Move;
class Position;
class Board;
class Piece;

class Pawn;

enum class Color { White, Black };

Color operator!(Color color);

std::ostream &operator<<(std::ostream &os, Color color);

enum class GameResult {
    Continuing,
    Victory,
    StaleMate,
    IllegalMove,
};
