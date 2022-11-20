//
// Created by Pavel Erokhin on 20.11.2022.
//

#include "header.hpp"

void decryption(std::vector<unsigned char> &bytes, int key) {
    std::vector<unsigned int> temp_vec;
    srand(key);
    for (auto iter: bytes) {
        temp_vec.push_back(static_cast<unsigned int>(iter));
    }
    for (auto &iter: temp_vec) {
        unsigned int gamma = rand();
        gamma = gamma & 255;
        unsigned int xored = (iter ^ gamma) & 255;
        iter = xored;
    }
    for (size_t j = 0; j < temp_vec.size(); ++j) {
        bytes[j] = static_cast<unsigned char>(temp_vec[j]);
    }
}
