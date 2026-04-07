//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_CIPHERLIST_H
#define TITKOSITO_CIPHERLIST_H
#include <string>
#include <vector>

#include "Cipher.h"


/**
 * Kódoló objektumok sorrendbe rendezett listája, láncolt kódoláshoz/dekódoláshoz.
 */
class CipherList {
    /// A listában tárolt kódolók dinamikus pointerei.
    std::vector<Cipher *> ciphers;
public:
    /// Nem konstans bejáró típus.
    using iterator = std::vector<Cipher *>::iterator;
    /// Konstans bejáró típus.
    using const_iterator = std::vector<Cipher *>::const_iterator;
    /**
     * Alap konstruktor.
     */
    CipherList() = default;
    /**
     * Másoló konstruktor mély másolással.
     * @param   other a másolandó kódolólista
     */
    CipherList(const CipherList &other);
    /**
     * Értékadó operátor mély másolással.
     * @param   other a másolandó kódolólista
     * @return  az aktuális objektum referenciaja
     */
    CipherList &operator=(const CipherList &other);
    /**
     * Két kódolólista összefűzése új listába.
     * @param   other a hozzáfűzendő kódolólista
     * @return  az összefűzött új lista
     */
    CipherList operator+(const CipherList &other) const;
    /**
     * Hozzáfűz egy másik listát az aktuálishoz.
     * @param   other a hozzáfűzendő kódolólista
     * @return  az aktuális objektum referenciaja
     */
    CipherList &operator+=(const CipherList &other);
    /**
     * Elér egy kódolót index alapján.
     * @param   idx a kért index
     * @return  hivatkozás a kiválasztott kódolóra
     */
    Cipher &operator[](size_t idx);
    /**
     * Elér egy kódolót index alapján konstans környezetben.
     * @param   idx a kért index
     * @return  konstans hivatkozás a kiválasztott kódolóra
     */
    const Cipher &operator[](size_t idx) const;
    /**
     * Új kódolót ad a lista végéhez.
     * @param   cipher a hozzáadandó kódoló pointere
     */
    void addCipher(Cipher *cipher);
    /**
     * Sorban alkalmazza a listában lévő kódolókat a szövegre.
     * @param   message titkosítandó üzenet
     * @return  titkosított szöveg
     */
    std::string encode(const std::string &message) const;
    /**
     * Fordított sorrendben visszafejti a listával titkosított szöveget.
     * @param   ciphertext titkosított üzenet
     * @return  megfejtett nyílt szöveg
     */
    std::string decode(const std::string &ciphertext) const;
    /**
     * Létrehoz egy dinamikus másolatot a listáról.
     * @return  a létrehozott másolat pointere
     */
    CipherList *clone() const;
    /**
     * Visszaadja a lista elejére mutató iterátort.
     * @return  nem konstans iterátor az első elemre
     */
    iterator begin();
    /**
     * Visszaadja a lista végét jelölő iterátort.
     * @return  nem konstans végiterátor
     */
    iterator end();
    /**
     * Visszaadja a lista elejére mutató konstans iterátort.
     * @return  konstans iterátor az első elemre
     */
    const_iterator begin() const;
    /**
     * Visszaadja a lista végét jelölő konstans iterátort.
     * @return  konstans végiterátor
     */
    const_iterator end() const;
    /**
     * Visszaadja a lista elejére mutató konstans iterátort.
     * @return  konstans iterátor az első elemre
     */
    const_iterator cbegin() const;
    /**
     * Visszaadja a lista végét jelölő konstans iterátort.
     * @return  konstans végiterátor
     */
    const_iterator cend() const;
    /**
     * Felszabadítja a listában tárolt dinamikus objektumokat.
     */
    ~CipherList();
};


#endif // TITKOSITO_CIPHERLIST_H
