#include "lib.h"

void panic(const std::string &msg) {
    std::stringstream ss;
    ss << "panic: " << msg << " (" << strerror(errno) << ")" << std::endl;
    throw std::runtime_error(ss.str());
}

Color operator!(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}

std::ostream &operator<<(std::ostream &os, Color color) {
    switch (color) {
    case Color::White:
        return os << "White";
    case Color::Black:
        return os << "Black";
    default:
        return os << "Unknown";
    }
}
