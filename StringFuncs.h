//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_STRINGFUNCS_H
#define TITKOSITO_STRINGFUNCS_H
#include <string>
#include <vector>


/**
 * Sztringkezelő segédfüggvényeket tartalmazó segédstruktúra.
 */
struct StringFuncs {
    /**
     * Feldarabol egy sztringet a megadott elválasztó mentén.
     * @param   s a feldarabolandó sztring
     * @param   delimiter az elválasztó sztring
     * @return  a feldarabolt részek vektora
     */
    static std::vector<std::string> split(std::string s, const std::string &delimiter);
    /**
     * Eltol egy kisbetűs karaktert az ábécében.
     * @param   c az eltolandó karakter
     * @param   shift az eltolás mértéke
     * @return  az eltolt karakter
     */
    static char shift_char(char c, int shift);
};



#endif //TITKOSITO_STRINGFUNCS_H
