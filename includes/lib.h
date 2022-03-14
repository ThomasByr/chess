#pragma once

#include <iostream>
#include <string>
#include <vector>

class Board;
class Piece;

enum class Color { White, Black };

Color operator!(Color color);

std::ostream &operator<<(std::ostream &os, Color color);

enum class GameResult {
    Continuing,
    Victory,
    StaleMate,
    IllegalMove,
};
