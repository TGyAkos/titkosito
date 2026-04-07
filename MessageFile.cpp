//
// Created by user on 06/04/2026.
//

#include "MessageFile.h"

#include <fstream>
#include <stdexcept>

std::string MessageFile::loadFile(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + file_name);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}
void MessageFile::saveToFile(const std::string& message) {
    std::ofstream file(output_file_name);
    if (!file.is_open())
        throw std::runtime_error(std::string("Could not open file: ") + output_file_name);
    file << message;
}
