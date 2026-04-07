//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_MYCIPHER_H
#define TITKOSITO_MYCIPHER_H
#include <string>

#include "Cipher.h"
#include "Registrar.h"

/**
 * Kulcsalapú, pozíciófüggő helyettesítő kódoló.
 */
class MyCipher : public Cipher {
    /// A kódoláshoz használt kulcsszó.
    std::string key;
    /// A kezdő eltolás értéke.
    int offset;
    /**
     * Ellenőrzi a kulcs formátumát.
     * @param   key az ellenőrizendő kulcs
     */
    static void validate_key(const std::string &key);
    /**
     * Ellenőrzi, hogy a szöveg csak megengedett karaktereket tartalmaz-e.
     * @param   text az ellenőrizendő szöveg
     */
    static void validate_text(const std::string &text);
public:
    /**
     * Konstruktor alapértelmezett offsettel.
     * @param   key a kódoláshoz használt kulcs
     */
    MyCipher(const char* key) : key(key), offset(0) {}
    /**
     * Konstruktor kulccsal és offsettel.
     * @param   key a kódoláshoz használt kulcs
     * @param   offset a kezdő eltolás
     */
    MyCipher(const char* key, int offset) : key(key), offset(offset) {}
    /**
     * Konstruktor paraméterlistából.
     * @param   params paraméterlista (kulcs, opcionális offset)
     */
    MyCipher(const std::vector<std::string>& params) : key(params[0]), offset(params.size() > 1 ? stoi(params[1]) : 0) {}
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
    ~MyCipher() override = default;
};

#endif //TITKOSITO_MYCIPHER_H
