/**
 * \file test.cpp
 *
 * Cipher nevű szorgalmi feladat tesztjei gtest_lite eszközeivel megvalósítva
 * A szorgalmi feladat megoldásához ezt az állományt nem kell beadni (feltölteni).
 *
 */

#ifndef TITKOSITO_TEST_H
#define TITKOSITO_TEST_H

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "CaesarCipher.h"
#include "CipherFactory.h"
#include "CipherFile.h"
#include "CipherList.h"
#include "MessageFile.h"
#include "MyCipher.h"
#include "StringFuncs.h"
#include "TranspositionCipher.h"
#include "gtest_lite.h"
#include "memtrace.h"

void tests() {
    GTINIT(std::cin);
        //Caesar titkosítás ellenőrzése
        TEST(Caesar shift=4, _alma) {
            CaesarCipher cc(4);
            std::string alma = cc.encode("alma");
            EXPECT_STREQ("epqe", alma.c_str());
            std::string almacr = cc.decode(alma);
            EXPECT_STREQ("alma", almacr.c_str());
        } END

        TEST(Caesar shift=3, _uvwxyz) {
            CaesarCipher cc(3);
            std::string a = cc.encode("uvwxyz");
            EXPECT_STREQ("xyzabc", a.c_str());
            std::string b = cc.decode(a);
            EXPECT_STREQ("uvwxyz", b.c_str());
        } END

        TEST(Caesar shift=-10, _caesar) {
            CaesarCipher cc(-10);
            std::string a = cc.encode("caesar");
            EXPECT_STREQ("squiqh", a.c_str());
            std::string b = cc.decode(a);
            EXPECT_STREQ("caesar", b.c_str());
        } END

        TEST(Caesar shift=1000, _caesar) {
            CaesarCipher cc(1000);
            std::string a = cc.encode("caesar");
            EXPECT_STREQ("omqemd", a.c_str());
            std::string b = cc.decode(a);
            EXPECT_STREQ("caesar", b.c_str());
        } END

        TEST(Caesar shift=10, _ez egy uzenet) {
            CaesarCipher cc(10);
            const std::string str = "ez egy uzenet";
            std::string a = cc.encode(str);
            EXPECT_STREQ("oj oqi ejoxod", a.c_str());
            std::string b = cc.decode(a);
            EXPECT_STREQ("ez egy uzenet", b.c_str());
        } END

        TEST(My_Cipher key=abc counter=0, _titkositas) {
            MyCipher mc("abc");
            std::string a = mc.encode("titkositas");
            EXPECT_STREQ("tkxntzobkb", a.c_str());
            std::string b = mc.decode(a);
            EXPECT_STREQ("titkositas", b.c_str());
        } END

    //My cipher tesztek
        TEST(const My_Cipher key=cipher counter=10, _titkositas) {
            const MyCipher mc("cipher", 10);
            Cipher * const clone = mc.clone();
            std::string a = clone->encode("titkositas");
            EXPECT_STREQ("fbuegyashs", a.c_str());
            std::string b = clone->decode(a);
            EXPECT_STREQ("titkositas", b.c_str());
            delete clone;
        } END

        TEST(My_Cipher key=xyz counter=-3, _virtualis destruktor) {
            MyCipher mc("xyz", -3);
            std::string a = mc.encode("virtualis destruktor");
            EXPECT_STREQ("pepqtblkw ilybbdvgaf", a.c_str());
            std::string b = mc.decode(a);
            EXPECT_STREQ("virtualis destruktor", b.c_str());
        } END

    //Transposition cipher tesztek
        TEST(TranspositionCipher size=4, _titkositas) {
            TranspositionCipher tc(4);
            std::string a = tc.encode("titkositas");
            EXPECT_STREQ("toaisstikt", a.c_str());
            std::string b = tc.decode(a);
            EXPECT_STREQ("titkositas", b.c_str());
        } END

        TEST(TranspositionCipher size=3, _no_padding_and_capacity_limit) {
            TranspositionCipher tc(3);
            std::string encoded = tc.encode("abcdefg");
            EXPECT_STREQ("adgbecf", encoded.c_str());
            std::string decoded = tc.decode(encoded);
            EXPECT_STREQ("abcdefg", decoded.c_str());
            EXPECT_THROW(tc.encode("abcdefghij"), const std::runtime_error&);
        } END

    //CipherList tesztek
        TEST(Cipher_List: caesar + mycipher, _meg tobb szorgalmit prog2bol) {
            CipherList List;
            const CaesarCipher caesar(6);
            const MyCipher myCipher("abc", -2);
            List.addCipher(caesar.clone());
            List.addCipher(myCipher.clone());
            std::string str1 = List.encode("meg tobb szorgalmit progkettobol");
            EXPECT_STREQ("qko czln fofhyuehfp pqpjmizyvkwv", str1.c_str());
            std::string str2 = List.decode(str1);
            EXPECT_STREQ("meg tobb szorgalmit progkettobol", str2.c_str());
        } END

    CipherList List; //kell majd a következőkhöz is
        TEST(Cipher_List: inner List, _pointert mindenhova_alfa) {
            CipherList inner;
            inner.addCipher(new MyCipher("List"));
            inner.addCipher(new CaesarCipher(10));
            List += inner; //teszteli az operator+=-t is
            List += List; //ennek sem kellene gondot okoznia
            std::string str1 = List.encode("pointert mindenhova");
            EXPECT_STREQ("taqzfyhn ogpfotryno", str1.c_str());
            std::string str2 = List.decode(str1);
            EXPECT_STREQ("pointert mindenhova", str2.c_str());
        } END

        TEST(Cipher_List: inner List, _pointert mindenhova_beta) {
            std::srand(std::time(nullptr));
            CipherList inner;
            inner.addCipher(new MyCipher("List"));
            inner.addCipher(new CaesarCipher(std::rand() % 26));
            List += inner; //teszteli az operator+=-t is
            List += List; //ennek sem kellene gondot okoznia
            std::string str = List.decode(List.encode("pointert mindenhova"));
            EXPECT_STREQ("pointert mindenhova", str.c_str());
        } END


        //Cipher Kivétel tesztek
        TEST(Kivetelek, MyCipher) {
            MyCipher mc("a");
            try {
                EXPECT_THROW_THROW(mc.encode("_"), const std::runtime_error&);
            } catch (const std::runtime_error& e) {
            }
        } END

        //StringFuncs tesztek
        TEST(StringFuncs, split_and_shift_char) {
            std::vector<std::string> tokens = StringFuncs::split("a:b:c", ":");
            EXPECT_EQ(3, static_cast<int>(tokens.size()));
            EXPECT_STREQ("a", tokens[0].c_str());
            EXPECT_STREQ("b", tokens[1].c_str());
            EXPECT_STREQ("c", tokens[2].c_str());
            EXPECT_EQ('c', StringFuncs::shift_char('a', 2));
            EXPECT_EQ('z', StringFuncs::shift_char('b', -2));
            EXPECT_EQ(' ', StringFuncs::shift_char(' ', 17));
        } END

        //CipherFactory tesztek
        TEST(CipherFactory, exists_and_create) {
            CipherFactory& factory = CipherFactory::getInstance();
            EXPECT_TRUE(factory.cipherExists("CaesarCipher"));
            EXPECT_TRUE(factory.cipherExists("MyCipher"));
            EXPECT_TRUE(factory.cipherExists("TranspositionCipher"));

            Cipher* c1 = factory.createCipher("CaesarCipher:2");
            Cipher* c2 = factory.createCipher("MyCipher:abc,1");
            Cipher* c3 = factory.createCipher("TranspositionCipher:4");

            EXPECT_STREQ("CaesarCipher:2", c1->getCipherString().c_str());
            EXPECT_STREQ("MyCipher:abc,1", c2->getCipherString().c_str());
            EXPECT_STREQ("TranspositionCipher:4", c3->getCipherString().c_str());

            delete c1;
            delete c2;
            delete c3;
        } END

        TEST(CipherFactory, invalid_inputs_throw) {
            CipherFactory& factory = CipherFactory::getInstance();
            EXPECT_THROW(factory.createCipher("CaesarCipher"), const std::runtime_error&);
            EXPECT_THROW(factory.createCipher("UnknownCipher:1"), const std::runtime_error&);
            EXPECT_THROW(factory.createCipher("CaesarCipher:1:2"), const std::runtime_error&);
        } END

        //CipherList tesztek
        TEST(CipherList, operators_index_and_clone) {
            CipherList first;
            first.addCipher(new CaesarCipher(1));
            CipherList second;
            second.addCipher(new MyCipher("abc", 0));

            CipherList merged = first + second;
            EXPECT_STREQ("CaesarCipher:1", merged[0].getCipherString().c_str());
            EXPECT_STREQ("MyCipher:abc,0", merged[1].getCipherString().c_str());
            EXPECT_THROW(merged[2], const std::out_of_range&);

            CipherList assigned;
            assigned = merged;
            std::string msg = "alma korte";
            EXPECT_STREQ(merged.encode(msg).c_str(), assigned.encode(msg).c_str());

            CipherList* cloned = merged.clone();
            EXPECT_STREQ(merged.decode(merged.encode(msg)).c_str(), cloned->decode(cloned->encode(msg)).c_str());
            delete cloned;
        } END

        //CipherFile,MessageFile tesztek
        TEST(CipherFile_MessageFile, message_and_cipher_temp_files) {
            const std::string msg_file = "./messagetest.txt";
            const std::string cipher_file = "./codetest.txt";
            std::ofstream out(msg_file);
            out << "hello from temp file";
            out.close();
            EXPECT_STREQ("hello from temp file", MessageFile::loadFile(msg_file).c_str());

            CipherList original;
            original.addCipher(new CaesarCipher(3));
            original.addCipher(new MyCipher("abc", 2));
            CipherFile::saveToFile(cipher_file, &original);

            CipherList* loaded = CipherFile::loadFile(cipher_file);
            std::string input = "hello from temp file";
            EXPECT_STREQ(original.encode(input).c_str(), loaded->encode(input).c_str());
            EXPECT_STREQ(input.c_str(), loaded->decode(loaded->encode(input)).c_str());

            delete loaded;
            std::remove(msg_file.c_str());
            std::remove(cipher_file.c_str());
        } END

        TEST(End_to_End, simulated_main_encode_flow_without_executable) {
            const std::string msg_file = "messagetest", cipher_file = "codetest", result_file = "./testresult.txt";
            std::string backup_result;
            bool result_existed = false;

            std::ifstream in(result_file);
            if (in.is_open()) {
                result_existed = true;
                backup_result = std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
            }
            in.close();

            std::ofstream msg_out(msg_file);
            msg_out << "hello world";
            msg_out.close();

            std::ofstream cipher_out(cipher_file);
            cipher_out << "CaesarCipher:2-MyCipher:abc,1-TranspositionCipher:4";
            cipher_out.close();

            const std::string message_string = MessageFile::loadFile(msg_file);
            CipherList* cipher_list = CipherFile::loadFile(cipher_file);
            const std::string coded_message_string = cipher_list->encode(message_string);

            MessageFile::saveToFile(coded_message_string);
            CipherFile::saveToFile(cipher_file, cipher_list);

            EXPECT_STREQ(coded_message_string.c_str(), MessageFile::loadFile(result_file).c_str());

            CipherList* persisted = CipherFile::loadFile(cipher_file);
            EXPECT_STREQ(message_string.c_str(), persisted->decode(coded_message_string).c_str());

            delete persisted;
            delete cipher_list;
            std::remove(msg_file.c_str());
            std::remove(cipher_file.c_str());

            if (result_existed) {
                std::ofstream out(result_file);
                out << backup_result;
            } else {
                std::remove(result_file.c_str());
            }
        } END

    GTEND(std::cerr);
}

#endif // TITKOSITO_TEST_H
