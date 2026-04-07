//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_TRANSPOSITIONCIPHER_H
#define TITKOSITO_TRANSPOSITIONCIPHER_H
#include <string>
#include <vector>


#include "Cipher.h"


/**
 * Mátrixos felcserélésen alapuló transzpozíciós kódoló.
 */
class TranspositionCipher : public Cipher {
    /// A négyzetes mátrix oldalmérete.
    size_t matrix_size;
    /**
     * Ellenőrzi, hogy a szöveg csak megengedett karaktereket tartalmaz-e.
     * @param   text az ellenőrizendő szöveg
     */
    static void validate_text(const std::string &text);
public:
    /**
     * Konstruktor a mátrix méretével.
     * @param   size a mátrix oldalmérete
     */
    TranspositionCipher(size_t size) : matrix_size(size) {}
    /**
     * Konstruktor paraméterlistából.
     * @param   params paraméterlista, ahol az első elem a méret
     */
    TranspositionCipher(const std::vector<std::string>& params) : matrix_size(params[0][0] == '\\' ? 0 : stoi(params[0])) {}
    /**
     * Visszaadja a kódoló szöveges leírását.
     * @return  a kódoló neve és paraméterei
     */
    const std::string getCipherString() const override;
    /**
     * Titkosítja a kapott üzenetet transzpozícióval.
     * @param   message titkosítandó üzenet
     * @return  titkosított szöveg
     */
    std::string encode(const std::string &message) override;
    /**
     * Visszafejti a transzpozícióval titkosított szöveget.
     * @param   ciphertext titkosított üzenet
     * @return  megfejtett nyílt szöveg
     */
    std::string decode(const std::string &ciphertext) override;
    /**
     * Létrehoz egy dinamikus másolatot.
     * @return  a létrehozott másolat pointere
     */
    Cipher *clone() const override;
    /**
     * Alap destruktor.
     */
    ~TranspositionCipher() override = default;
};



#endif //TITKOSITO_TRANSPOSITIONCIPHER_H
