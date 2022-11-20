//
// Created by Pavel Erokhin on 20.11.2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef ENCRYPTION_ALGORITHM_HEADER_HPP
#define ENCRYPTION_ALGORITHM_HEADER_HPP

void encryption(std::vector<unsigned char>& bytes, int key);
void decryption(std::vector<unsigned char>& bytes, int key);

#endif //ENCRYPTION_ALGORITHM_HEADER_HPP
