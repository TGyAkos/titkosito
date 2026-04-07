//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_CIPHERFILE_H
#define TITKOSITO_CIPHERFILE_H
#include <string>
#include <vector>

#include "CipherList.h"

/**
 * Kódoló konfigurációkat fájlba mentő és fájlból betöltő segédosztály.
 */
class CipherFile {

public:
    /**
     * Alap konstruktor.
     */
    CipherFile() = default;
    /**
     * Betölti a kódolólistát egy konfigurációs fájlból.
     * @param   file_name a beolvasandó fájl neve
     * @return  dinamikusan foglalt kódolólista pointere
     */
    static CipherList* loadFile(const std::string& file_name);
    /**
     * Elmenti a kódolólistát a megadott fájlba.
     * @param   file_name a célfájl neve
     * @param   cipher_list a mentendő kódolólista
     */
    static void saveToFile(const std::string& file_name, CipherList* cipher_list);
    /**
     * Alap destruktor.
     */
    ~CipherFile() = default;
};


#endif // TITKOSITO_CIPHERFILE_H
