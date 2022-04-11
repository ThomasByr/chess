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
        panic("Invalid color");
    }
}

std::string repeat(std::string str, const unsigned n) {
    if (n == 0) {
        str.clear();
        str.shrink_to_fit();
        return str;
    } else if (n == 1 || str.empty()) {
        return str;
    }
    const auto period = str.size();
    if (period == 1) {
        str.append(n - 1, str.front());
        return str;
    }
    str.reserve(period * n);
    unsigned m = 2;
    for (; m < n; m *= 2)
        str += str;
    str.append(str.c_str(), (n - (m / 2)) * period);
    return str;
}

std::string operator*(std::string str, unsigned n) {
    return repeat(std::move(str), n);
}

std::string input(std::string prompt) {
    std::string s;
    std::cout << prompt;
    std::cout.flush();

    std::getline(std::cin, s);
    return s;
}

std::string trim(const std::string &s) {
    std::string::size_type first = s.find_first_not_of(' ');
    std::string::size_type last = s.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return s.substr(first, (last - first + 1));
}

std::string to_lower(const std::string &s) {
    std::string r;
    for (char c : s) {
        r += tolower(c);
    }
    return r;
}
