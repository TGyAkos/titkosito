//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_CIPHERFACTORY_H
#define TITKOSITO_CIPHERFACTORY_H
#include <functional>
#include <string>
#include <unordered_map>

#include "Cipher.h"


/**
 * Singleton gyár osztály, amely a kódolók regisztrálását és létrehozását végzi.
 */
class CipherFactory {
    /// Kódolónév -> létrehozó függvény társítások tárolója.
    std::unordered_map<std::string, std::function<Cipher*(const std::vector<std::string>&)>>* ciphers;
    /**
     * Feldarabolja a kódoló leíró stringet névre és paraméterekre.
     * @param   cipher_string a feldolgozandó kódoló leírás
     * @return  az első elem a kódolónév, utána a paraméterek
     */
    static std::vector<std::string> parseCipherString(const std::string& cipher_string);
    /**
     * Privát konstruktor, hogy ne lehessen példányosítani.
     */
    CipherFactory() : ciphers(new std::unordered_map<std::string, std::function<Cipher*(const std::vector<std::string>&)>>()) {}
public:
    /**
     * Visszaadja a gyár egyetlen példányát.
     * @return  a singleton gyár referenciaja
     */
    static CipherFactory& getInstance();
    /**
     * Regisztrál egy új kódolót a gyárban.
     * @param   name a kódoló neve
     * @param   cipher a kódoló létrehozó függvénye
     */
    void registerCipher(const std::string& name, std::function<Cipher*(const std::vector<std::string>&)> cipher) const;
    /**
     * Létrehoz egy kódolót a leíró string alapján.
     * @param   name kódoló leírás (név és paraméterek)
     * @return  a létrehozott kódoló objektum pointere
     */
    Cipher* createCipher(const std::string& name) const;
    /**
     * Ellenőrzi, hogy létezik-e a megadott nevű kódoló.
     * @param   name a keresett kódoló neve
     * @return  igaz, ha a kódoló regisztrálva van
     */
    bool cipherExists(const std::string& name) const;
    /**
      * Kiüríti a regisztrált kódolók tárolóját.
      * Ezt célszerű még a program futása közben meghívni,
      * hogy ne statikus destrukció során történjen a felszabadítás.
      */
    void clearRegistry();
    /**
     * Alap destruktor.
     */
    ~CipherFactory();
};



#endif //TITKOSITO_CIPHERFACTORY_H
