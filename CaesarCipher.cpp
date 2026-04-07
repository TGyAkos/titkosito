//
// Created by user on 06/04/2026.
//

#include "CaesarCipher.h"

#include "StringFuncs.h"

static Registrar<CaesarCipher> regCaesarCipher("CaesarCipher");

const std::string CaesarCipher::getCipherString() const {
    return "CaesarCipher:" + std::to_string(shift);
}
Cipher *CaesarCipher::clone() const {
    return new CaesarCipher(shift);
}
std::string CaesarCipher::encode(const std::string &message) {
    std::string out = message;
    for (size_t i = 0; i < out.size(); ++i)
        if (message[i] == ' ' || (message[i] >= 'a' && message[i] <= 'z'))
            out[i] = StringFuncs::shift_char(out[i], shift);
        else if (message[i] >= 'A' && message[i] <= 'Z')
            out[i] = StringFuncs::shift_char(tolower(out[i]), shift);
        else
            out[i] = message[i];
    return out;
}
std::string CaesarCipher::decode(const std::string &ciphertext) {
    std::string out = ciphertext;
    for (size_t i = 0; i < out.size(); ++i)
        if (ciphertext[i] == ' ' || (ciphertext[i] >= 'a' && ciphertext[i] <= 'z'))
            out[i] = StringFuncs::shift_char(out[i], -shift);
        else
            out[i] = ciphertext[i];
    return out;
}
