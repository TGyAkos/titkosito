//
// Created by user on 06/04/2026.
//

#include "CipherFile.h"

#include <fstream>
#include <vector>

#include "Cipher.h"
#include "CipherFactory.h"
#include "StringFuncs.h"

CipherList *CipherFile::loadFile(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file " + file_name);
    const std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    const std::vector<std::string> cipher_strings = StringFuncs::split(file_content, "-");
    CipherList *rt_list = new CipherList();
    for (const std::string& cipher_string: cipher_strings)
        rt_list->addCipher(CipherFactory::getInstance().createCipher(cipher_string));
    return rt_list;
}
void CipherFile::saveToFile(const std::string &file_name, CipherList *cipher_list) {
    std::ofstream file(file_name);
    bool first = true;
    for (const Cipher *cipher : *cipher_list) {
        if (!first) file << "-";
        file << cipher->getCipherString();
        first = false;
    }
}