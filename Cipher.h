//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_CIPHER_H
#define TITKOSITO_CIPHER_H



/**
 * Absztrakt ősosztály, amely a kódolók közös interfészét definiálja.
 */
class Cipher {
public:
    /**
     * Titkosítja a kapott stringet
     * @param   message titkosítandó üzenet
     * @return  a message szöveg titkosított változata
     */
    virtual std::string encode(const std::string& message) = 0;
    /**
     * Dekódolja a kapott stringet
     * @param   ciphertext titkosított üzenet
     * @return  a megfejtett nyílt szöveg
     */
    virtual std::string decode(const std::string& ciphertext) = 0;
    /**
     * Létrehoz egy másolatot dinamikusan
     * @return  a létrehozott objektumra mutató pointer
     */
    virtual Cipher* clone() const = 0;
    /**
     * Visszaadja a kódolás nevét és paramétereit egy stringben, ami alapján újra létre lehet hozni a kódolót
     * @return a létrehozott szöveg
     */
    virtual const std::string getCipherString() const = 0;
    /**
     * Alap destruktor
     */
    virtual ~Cipher() { };
};



#endif //TITKOSITO_CIPHER_H
