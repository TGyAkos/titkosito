//
// Created by user on 06/04/2026.
//

#include "TranspositionCipher.h"
#include <stdexcept>

#include "Registrar.h"

static Registrar<TranspositionCipher> regTranspositionCipher("TranspositionCipher");

void TranspositionCipher::validate_text(const std::string &text) {
    for (char i : text)
        if (!(i == ' ' || (i >= 'a' && i <= 'z')))
            throw std::runtime_error("Invalid character in message");
}
const std::string TranspositionCipher::getCipherString() const {
    return "TranspositionCipher:" + std::to_string(matrix_size);
}
std::string TranspositionCipher::encode(const std::string &message) {
    validate_text(message);
    const size_t n = matrix_size, capacity = n * n, len = message.size();
    if (len > capacity)
        throw std::runtime_error("Matrix cannot fit message");
    std::vector<std::vector<char>> matrix(n, std::vector<char>(n, '\0'));
    size_t idx = 0;
    for (size_t col = 0; col < n && idx < len; ++col)
        for (size_t row = 0; row < n && idx < len; ++row)
            matrix[row][col] = message[idx++];
    std::string encoded;
    encoded.reserve(len);
    for (size_t row = 0; row < n; ++row)
        for (size_t col = 0; col < n; ++col)
            if (col * n + row < len)
                encoded += matrix[row][col];
    return encoded;
}
std::string TranspositionCipher::decode(const std::string &ciphertext) {
    validate_text(ciphertext);
    const size_t n = matrix_size, capacity = n * n, len = ciphertext.size();
    if (len > capacity)
        throw std::runtime_error("Invalid ciphertext size for matrix");
    std::vector<std::vector<char>> matrix(n, std::vector<char>(n, '\0'));
    size_t idx = 0;
    for (size_t row = 0; row < n; ++row)
        for (size_t col = 0; col < n; ++col)
            if (col * n + row < len)
                matrix[row][col] = ciphertext[idx++];
    std::string decoded;
    decoded.reserve(len);
    for (size_t col = 0; col < n; ++col)
        for (size_t row = 0; row < n; ++row)
            if (col * n + row < len)
                decoded += matrix[row][col];
    return decoded;
}
Cipher *TranspositionCipher::clone() const {
    return new TranspositionCipher(matrix_size);
}
