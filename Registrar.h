//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_REGISTRAR_H
#define TITKOSITO_REGISTRAR_H
#include <string>

#include "CipherFactory.h"

/**
 * Sablon regisztráló segédstruktúra, amely statikus inicializáláskor
 * automatikusan bejegyzi a kódolót a gyárba.
 * @tparam T a regisztrálandó kódoló típusa
 */
template<typename T>
struct Registrar {
    /**
     * Konstruktor, amely elvégzi a típus regisztrációját.
     * @param   name a kódoló neve a gyárban
     */
    Registrar(const std::string &name) {
        CipherFactory::getInstance().registerCipher(
                name, [](const std::vector<std::string> &params) -> Cipher * { return new T(params); });
    }
};


#endif // TITKOSITO_REGISTRAR_H
