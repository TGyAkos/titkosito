//
// Created by user on 06/04/2026.
//

#include "CipherList.h"

#include <stdexcept>

CipherList::CipherList() {}
CipherList::CipherList(const CipherList &other) {
    for (Cipher *cipher: other.ciphers)
        ciphers.push_back(cipher->clone());
}
CipherList &CipherList::operator=(const CipherList &other) {
    if (this == &other)
        return *this;
    for (const Cipher *cipher: ciphers)
        delete cipher;
    ciphers.clear();
    for (Cipher *cipher: other.ciphers)
        ciphers.push_back(cipher->clone());
    return *this;
}
CipherList CipherList::operator+(const CipherList& other) const {
    CipherList result(*this);
    result += other;
    return result;
}
CipherList& CipherList::operator+=(const CipherList& other) {
    if (this == &other) {
        CipherList tmp(other);
        return (*this += tmp);
    }
    for (const Cipher* cipher : other)
        addCipher(cipher->clone());
    return *this;
}
Cipher &CipherList::operator[](size_t idx) {
    if (idx >= ciphers.size() || ciphers.empty())
        throw std::out_of_range("Cipher index out of range");
    return *ciphers[idx];
}
const Cipher &CipherList::operator[](size_t idx) const {
    if (idx >= ciphers.size() || ciphers.empty())
        throw std::out_of_range("Cipher index out of range");
    return *ciphers[idx];
}
void CipherList::addCipher(Cipher *cipher) { ciphers.push_back(cipher); }
std::string CipherList::encode(const std::string &message) {
    std::string out = message;
    for (Cipher *cipher: ciphers)
        out = cipher->encode(out);
    return out;
}
std::string CipherList::decode(const std::string &ciphertext) {
    std::string out = ciphertext;
    for (size_t i = ciphers.size(); i > 0; --i)
        out = ciphers[i-1]->decode(out);
    return out;
}
CipherList *CipherList::clone() const { return new CipherList(*this); }
CipherList::iterator CipherList::begin() { return ciphers.begin(); }
CipherList::iterator CipherList::end() { return ciphers.end(); }
CipherList::const_iterator CipherList::begin() const { return ciphers.begin(); }
CipherList::const_iterator CipherList::end() const { return ciphers.end(); }
CipherList::const_iterator CipherList::cbegin() const { return ciphers.cbegin(); }
CipherList::const_iterator CipherList::cend() const { return ciphers.cend(); }
CipherList::~CipherList() {
    for (Cipher *cipher: ciphers)
        delete cipher;
    ciphers.clear();
}
