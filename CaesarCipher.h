//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_CAESARCIPHER_H
#define TITKOSITO_CAESARCIPHER_H
#include <string>


#include "Cipher.h"
#include "Registrar.h"


/**
 * Caesar-elven működő helyettesítő kódoló.
 */
class CaesarCipher : public Cipher {
    /// Az ábécé karakterein alkalmazott eltolás mértéke.
    int shift;
public:
    /**
     * Konstruktor eltolás alapján.
     * @param   shift az eltolás mértéke
     */
    CaesarCipher(int shift) : shift(shift) {}
    /**
     * Konstruktor paraméterlistából.
     * @param   params paraméterlista, ahol az első elem az eltolás
     */
    CaesarCipher(const std::vector<std::string>& params) : shift(params[0][0] == '\\' ? 0 : stoi(params[0])) {}
    /**
     * Visszaadja a kódoló szöveges leírását.
     * @return  a kódoló neve és paraméterei
     */
    const std::string getCipherString() const override;
    /**
     * Létrehoz egy dinamikus másolatot.
     * @return  a létrehozott másolat pointere
     */
    Cipher *clone() const override;
    /**
     * Titkosítja a kapott üzenetet.
     * @param   message titkosítandó üzenet
     * @return  titkosított szöveg
     */
    std::string encode(const std::string &message) override;
    /**
     * Visszafejti a kapott titkosított szöveget.
     * @param   ciphertext titkosított üzenet
     * @return  megfejtett nyílt szöveg
     */
    std::string decode(const std::string &ciphertext) override;
    /**
     * Alap destruktor.
     */
    ~CaesarCipher() override = default;
};




#endif //TITKOSITO_CAESARCIPHER_H
