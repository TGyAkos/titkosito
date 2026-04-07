//
// Created by user on 06/04/2026.
//

#include "StringFuncs.h"

#include <stdexcept>

std::vector<std::string> StringFuncs::split(std::string s, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        std::string token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}
char StringFuncs::shift_char(const char c, const int shift) {
    if (c == ' ')
        return c;
    const int base = c - 'a';
    int s = shift % 26;
    if (s < 0)
        s += 26;
    return 'a' + (base + s) % 26;
}
