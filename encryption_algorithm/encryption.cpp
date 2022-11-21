//
// Created by Pavel Erokhin on 20.11.2022.
//

#include "header.hpp"

void encryption(std::vector<unsigned char> &bytes, int key) {
    std::vector<unsigned int> temp_vec;
    srand(key);
    unsigned int leftShift = 2;
    for (auto iter: bytes) {
        temp_vec.push_back(static_cast<unsigned int>(iter));
    }
    std::ofstream outputFile;
    outputFile.open("test", std::ios::binary);
    unsigned int tmp;
    unsigned int tmpbyte;
    for (size_t i = 0; i < temp_vec.size(); ++i) {
        unsigned char b1=temp_vec[i], b2=temp_vec[i+1], b3=temp_vec[i+2], b4=temp_vec[i+3];
        unsigned int gamma1 = rand();
        unsigned int gamma2 = rand();
        tmpbyte = b1;
        tmpbyte ^= gamma1 & 0xFF;
        tmp = static_cast<unsigned int>(tmpbyte);
        tmp <<= 8;
        tmpbyte = b2;
        tmpbyte ^= (gamma1>>8) & 0xFF;
        tmp |= static_cast<unsigned int>(tmpbyte);
        tmp ^= gamma1;
        tmp <<= 8;
        tmp |= static_cast<unsigned int>(b3);
        tmp <<= 8;
        tmp |= static_cast<unsigned int>(b4);
        tmp ^= gamma2;
        tmp = ((tmp << leftShift) | (tmp >> (32-leftShift))) & 0xFFFFFFFF;

        char r1 = tmp >> 24;
        char r2 = tmp >> 16;
        char r3 = tmp >> 8;
        char r4 = tmp;
        outputFile.write(&r1, sizeof(r1));
        outputFile.write(&r2, sizeof(r2));
    }
    for (size_t j = 0; j < temp_vec.size(); ++j) {
        bytes[j] = static_cast<unsigned char>(temp_vec[j]);
    }
