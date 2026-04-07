## Terv - UML diagramok

### Osztálydiagram

```mermaid
classDiagram
    class MessageFile {
        -output_file_name: const std:: string: static
        +MessageFile()
        +loadFile(file_name: const std:: string&) std:: string: static
        +saveToFile(message: const std:: string&): static
        +~ MessageFile()
    }
    class CipherFile {
        +CipherFile()
        +loadFile(file_name: const std:: string&) CipherList*: staic
        +saveToFile(file_name: const std:: string&, cipher_list: CipherList*): staic
        +~ CipherFile()
    }

    class CipherFactory {
        <<singleton>>
        -ciphers: std:: unordered_map~std::string, std::function< Cipher*(const std::vector<std::string>)&>~)
        -parseCipherString(cipher_string: const std:: string&) std:: vector~std::string~: static
        +getInstance() CipherFactory&: static
        +registerCipher(cipher_name: const std:: string&, cipher: std:: function< Cipher*(const std:: vector<std:: string>&)>~)
        +createCipher(cipher_string: const std:: string&) Cipher* \n
        +cipherExists(const std:: string& cipher_name) bool const
        +~ CipherFactory()
    }

    class Registrar {
        <<template>>
        Registrar(const std:: string& name, const std:: vector~std::string~ & params)
    }

    class Cipher {
        <<interface>>
        +encode(message: std:: string)* std:: string
        +decode(ciphertext: std:: string)* std:: string
        +clone()* Cipher*
        +getCipherString()* const std:: string const
        +~ Cipher()*
    }

    class CaesarCipher {
        -shift: int
        +CaesarCipher(shift: int)
        +CaesarCipher(params: const std:: vector~std::string~ &)
        +encode(message: std:: string) std:: string
        +decode(ciphertext: std:: string) std:: string
        +clone() Cipher* \n
        +getCipherString() std:: string
        +~ CaesarCipher()
    }

    class MyCipher {
        -key: std:: string
        -offset: int
        -validate_key(const std:: string& key): static
        -validate_text(const std:: string& text): static
        +MyCipher(key: const char*, offset: int)
        +MyCipher(params: const std:: vector~std::string~ &)
        +encode(message: std:: string) std:: string
        +decode(ciphertext: std:: string) std:: string
        +clone() Cipher* \n
        +getCipherString() std:: string
        +~ MyCipher()
    }

    class TranspositionCipher {
        -matrix_size: int
        +TranspositionCipher(matrix_size: int)
        +TranspositionCipher(params: const std:: vector~std::string~ &)
        +encode(message: std:: string) std:: string
        +decode(ciphertext: std:: string) std:: string
        +clone() Cipher* \n
        +getCipherString() std:: string
        +~ TranspositionCipher()
    }

    class StringFuncs {
        +split(std:: string s, const std:: string& delimiter) std:: vector~std::string~: static
        +char shift_char(char c, int shift): static
    }

    class CipherList {
        -ciphers: std:: vector~Cipher*~
        +CipherList()
        +CipherList(other: const CipherList&)
        +operator=(other: const CipherList&) CipherList&
        +operator+(other: const CipherList&) CipherList
        +operator+=(const CipherList&) CipherList&
        +operator[](idx: size_t) Cipher&
        +operator[](idx: size_t) const Cipher& const
        +add(cipher: Cipher*) void
        +encode(message: const std:: string&) std:: string
        +decode(ciphertext: const std:: string&) std:: string
        +clone() CipherList* const
        +begin() std:: vector~Cipher *~:: iterator;
        +end() std:: vector~Cipher *~:: iterator;
        +begin() const std:: vector~Cipher *~:: const_iterator;
        +end() const std:: vector~Cipher *~:: const_iterator;
        +cbegin() const std:: vector~Cipher *~:: const_iterator;
        +cend() const std:: vector~Cipher *~:: const_iterator;
        +~ CipherList()
    }



CipherList o-- "0..* -ciphers" Cipher
CipherList ..> Cipher

Cipher <|-- TranspositionCipher
Cipher <|-- MyCipher
Cipher <|-- CaesarCipher

StringFuncs <.. MyCipher
StringFuncs <.. CaesarCipher

CipherFactory *-- "0..* -ciphers" Cipher
CipherFactory ..> Cipher

CipherFile ..> CipherList
CipherFile ..> CipherFactory

Registrar ..> CipherFactory
CipherFactory ..> StringFuncs
CipherFile ..> StringFuncs


```

A CipherFile::saveToFile() függvény a dinamikusan változó kódolások helyes működése végett van implementálva.

### Sekvenciadiagramok

A main függvény lefutása előtt a következő műveletek történnek:

```mermaid
sequenceDiagram
    autonumber
    participant Static Initialization
    create participant Registrar
    participant CipherFactory
    Static Initialization ->>+ Registrar: Registrar<Cipher>(cipher_name)
    Registrar ->>+ CipherFactory: getInstance()
    CipherFactory -->>- Registrar: CipherFactory&
    Registrar ->>+ CipherFactory: registerCipher(cipher_name, []() -> Cipher*)
    deactivate CipherFactory
    destroy Registrar
    Registrar ->> Static Initialization: Registrar object created, cipher registered

```

A main függvény végrehajtása során a következő műveletek történnek:

```mermaid
sequenceDiagram
    autonumber
    participant main
    participant MessageFile
    main ->>+ MessageFile: loadfile(file_name)
    MessageFile -->>- main: message_string
    participant CipherFile
    participant CipherFactory
    main ->>+ CipherFile: loadfile(file_name)
    CipherFile ->>+ StringFuncs: split(file_content, delimiter)
    StringFuncs -->>- CipherFile: cipherStrings*
    create participant CipherList
    participant StringFuncs
    CipherFile ->> CipherList: CipherList()
    loop for each cipher_string in cipher_strings
        CipherFile ->>+ CipherFactory: createCipher(cipher_string)
        CipherFactory ->> CipherFactory: parseCipherString(cipher_string)
        CipherFactory ->>+ StringFuncs: split(cipher_string, delimiter)
        StringFuncs ->>- CipherFactory: cipher_name, cipher_parameters
        create participant Cipher
        CipherFactory ->> Cipher: ciphers[cipher_name](cipher_parameters)
        Cipher -->> CipherFactory: Cipher*
        CipherFactory -->>- CipherFile: Cipher*
        CipherFile ->>+ CipherList: add(Cipher*)
        deactivate CipherList
    end
    CipherList -->> CipherFile: CipherList*
    CipherFile -->>- main: CipherList*
    main ->>+ CipherList: encode(message_string)/decode(message_string)

    loop for each cipher in CipherList
        CipherList ->>+ Cipher: encode/decode(message_string)
        Cipher -->>- CipherList: coded_message_string
    end

    CipherList -->>- main: coded_message_string
    main ->>+ MessageFile: saveToFile(coded_message_string)
    deactivate MessageFile
    main ->>+ CipherFile: saveToFile(file_name, CipherList*)
    loop for each cipher in CipherList
        CipherFile ->>+ Cipher: getCipherString()
        Cipher -->>- CipherFile: cipher_string
        CipherFile ->> CipherFile: append cipher_string to save_string
    end
    deactivate CipherFile
```
