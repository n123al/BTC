#include "Encrypt.h"
#include <iostream>
#include <fstream>

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

static std::string buff[3] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz", "0123456789+/"};

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string encrypt(unsigned char const* input_bytes, unsigned int in_len, std::string const& key) {
    std::string ret,mykey;
    int i = 0;
    int j = 0;
    int key_count=0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
     mykey= "osSD1~!@%R^*$%#@*&^"+ buff[key.length() % 3] + key;
    
     std::ofstream myy;
     myy.open("fsdf");
     myy<< mykey;
     myy.close();
     
    while (in_len--) {
        char_array_3[i++] = (*(input_bytes++)^ key[key_count]);
        key_count++;
	if(key_count == key.length() ) key_count = 0;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

std::string decrypt(std::string const& input_bytes, std::string const& key) {
    int in_len = input_bytes.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    int key_count=0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret,mykey;
    
    mykey = buff[key.length()  % 3] + key;

    while (in_len-- && (input_bytes[in_] != '=') && is_base64(input_bytes[in_])) {
        char_array_4[i++] = input_bytes[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++){
                ret += (char_array_3[i]^ key[key_count]);
                key_count++;
                if(key_count == key.length()) key_count = 0;
            }       
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) {
            ret += (char_array_3[j] ^ key[key_count]);
            key_count++;
	    if(key_count == key.length()) key_count = 0;
        }
    }

    return ret;
} 