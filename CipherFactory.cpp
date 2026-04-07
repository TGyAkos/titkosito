//
// Created by user on 06/04/2026.
//

#include "CipherFactory.h"

#include <stdexcept>

#include "StringFuncs.h"

std::vector<std::string> CipherFactory::parseCipherString(const std::string &cipher_string) {
    std::vector<std::string> rt_vector;
    std::vector<std::string> cipher_parts = StringFuncs::split(cipher_string, ":");
    if (cipher_parts.size() != 2)
        throw std::runtime_error("Invalid cipher string format: After cipher name there must be exactly one ':' character");
    rt_vector.push_back(cipher_parts[0]);
    std::vector<std::string> cipher_parameters = StringFuncs::split(cipher_parts[1], ",");
    rt_vector.insert(rt_vector.end(), cipher_parameters.begin(), cipher_parameters.end());
    return rt_vector;
}
CipherFactory &CipherFactory::getInstance() {
    static CipherFactory instance;
    return instance;
}
void CipherFactory::registerCipher(const std::string &name, std::function<Cipher*(const std::vector<std::string>&)> cipher) const {
    (*ciphers)[name] = cipher;
}
Cipher* CipherFactory::createCipher(const std::string& cipher_string) const {
    auto parts = parseCipherString(cipher_string);
    if (parts.empty()) throw std::runtime_error("Invalid cipher string format could not be parsed");

    const std::string& name = parts[0];
    std::vector<std::string> params(parts.begin() + 1, parts.end());

    auto it = ciphers->find(name);
    if (it == ciphers->end())
        throw std::runtime_error("Invalid cipher name " + name);
    return it->second(params);
}
bool CipherFactory::cipherExists(const std::string &name) const { return ciphers->find(name) != ciphers->end(); }
void CipherFactory::clearRegistry() { ciphers->clear(); delete ciphers; ciphers = nullptr;}
CipherFactory::~CipherFactory() { if (ciphers) {ciphers->clear(); delete ciphers;}}
