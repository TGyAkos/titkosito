//
// Created by user on 06/04/2026.
//

#ifndef TITKOSITO_MESSAGEFILE_H
#define TITKOSITO_MESSAGEFILE_H
#include <string>

/**
 * Üzenetfájlok beolvasását és mentését végző segédosztály.
 */
class MessageFile {
    /// Kimenetett fájl neve, ahová a saveToFile metódus ír.
    static const char* output_file_name;
public:
    /**
     * Alap konstruktor.
     */
    MessageFile() = default;
    /**
     * Beolvassa egy fájl teljes tartalmát.
     * @param   file_name a beolvasandó fájl neve
     * @return  a fájl teljes szöveges tartalma
     */
    static std::string loadFile(const std::string& file_name);
    /**
     * Elmenti a kapott üzenetet az alapértelmezett kimeneti fájlba.
     * @param   message a kimentendő üzenet
     */
    static void saveToFile(const std::string& message);
    /**
     * Alap destruktor.
     */
    ~MessageFile() = default;
};



#endif //TITKOSITO_MESSAGEFILE_H
