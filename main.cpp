#include <iostream>

#include "CipherFactory.h"
#include "CipherFile.h"
#include "CipherList.h"
#include "MessageFile.h"
#include "gtest_lite.h"
#include "memtrace.h"


#define INCLUDE_TESTS

#ifdef INCLUDE_TESTS
#include "test.h"
const char* MessageFile::output_file_name = "./testresult.txt";
#else
const char* MessageFile::output_file_name = "./result.txt";
#endif

int main(int argc, char *argv[]) {
#ifdef INCLUDE_TESTS
        tests();
        CipherFactory::getInstance().clearRegistry();
        return 0;
#endif
    try {
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
        CipherFactory::getInstance().clearRegistry();
        return 0;
    } catch (std::exception &e) {
        CipherFactory::getInstance().clearRegistry();
        std::cerr << e.what() << std::endl;
    }
}
