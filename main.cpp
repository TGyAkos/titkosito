#include <iostream>

#include "CipherFile.h"
#include "CipherList.h"
#include "MessageFile.h"
#include "gtest_lite.h"
#include "memtrace.h"

std::string MessageFile::output_file_name = "../result.txt";

// #define INCLUDE_TESTS

#ifdef INCLUDE_TESTS
#include "test.h"
#endif


int main(int argc, char *argv[]) {
    try {
#ifdef INCLUDE_TESTS
        tests();
        return 0;
#endif
        std::string message_file_name, cipher_file_name, coded_message_string;
        bool isDecoding = false;
        if (strcmp(argv[1], "-r") == 0) {
            message_file_name = argv[2];
            cipher_file_name = argv[3];
            isDecoding = true;
        } else {
            message_file_name = argv[1];
            cipher_file_name = argv[2];
        }
        std::string message_string = MessageFile::loadFile(message_file_name);
        CipherList *cipher_list = CipherFile::loadFile(cipher_file_name);
        if (isDecoding)
            coded_message_string = cipher_list->decode(message_string);
        else
            coded_message_string = cipher_list->encode(message_string);
        MessageFile::saveToFile(coded_message_string);
        CipherFile::saveToFile(cipher_file_name, cipher_list);
        delete cipher_list;
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
