//
// Created by user on 06/04/2026.
//

#include "MyCipher.h"

#include <stdexcept>

#include "StringFuncs.h"

static Registrar<MyCipher> regMyCipher("MyCipher");

const std::string MyCipher::getCipherString() const {
    return "MyCipher:" + key + "," + std::to_string(offset);
}

void MyCipher::validate_key(const std::string &key) {
    if (key.empty())
        throw std::runtime_error(std::string("Key cannot be empty"));
    for (char i : key)
        if ((i < 'a' || i > 'z') && (i < 'A' || i > 'Z'))
            throw std::runtime_error(std::string("Invalid character '") + i + std::string("'"));
}
void MyCipher::validate_text(const std::string &text) {
    for (char i : text)
        if (!(i == ' ' || (i >= 'a' && i <= 'z')))
            throw std::runtime_error(std::string("Invalid character '") + i + std::string("'"));
}
Cipher *MyCipher::clone() const {
    return new MyCipher(key.c_str(), offset);
}
std::string MyCipher::encode(const std::string &message) {
    validate_key(key);
    validate_text(message);
    std::string out = message;
    const size_t key_len = key.size();
    for (size_t i = 0; i < out.size(); ++i) {
        int key_shift = key[i % key_len] - 'a';
        out[i] = StringFuncs::shift_char(out[i], offset + i + key_shift);
    }
    return out;
}
std::string MyCipher::decode(const std::string &ciphertext) {
    validate_key(key);
    validate_text(ciphertext);
    std::string out = ciphertext;
    const size_t key_len = key.size();
    for (size_t i = 0; i < out.size(); ++i) {
        int key_shift = key[i % key_len] - 'a';
        out[i] = StringFuncs::shift_char(out[i], -(offset + i + key_shift));
    }
    return out;
}
