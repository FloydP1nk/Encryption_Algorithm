#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(int argc, const char *argv[]) {

    std::string message = "qwertyo";

    const char *data = message.data();
    int size = message.size();

    std::vector<char> bytes(size);
    for (int i = 0; i < size; i++) {
        bytes[i] = data[i];
    }
    unsigned int key = 4;
    unsigned int leftShift = 3;
    srand(key);

    std::ofstream outputFile;
    outputFile.open("file", std::ios::binary);

    unsigned int tmp;
//    unsigned int tmpbyte;
    for (size_t i = 0; i < bytes.size(); ++i) {
        unsigned int gamma1 = rand();
        unsigned int gamma2 = rand();
        unsigned char b1 = bytes[i];
        unsigned char b2 = i + 1 < bytes.size() ? bytes[i + 1] : 0u;
        unsigned char b3 = i + 2 < bytes.size() ? bytes[i + 2] : 0u;
        unsigned char b4 = i + 3 < bytes.size() ? bytes[i + 3] : 0u;

        tmp = static_cast<unsigned int>(b1);
        tmp <<= 8;
        tmp |= static_cast<unsigned int>(b2);
        tmp ^= gamma1; /// Гаммируем первую часть блока
        tmp <<= 8;
        tmp |= static_cast<unsigned int>(b3);
        tmp <<= 8;
        tmp |= static_cast<unsigned int>(b4);
        tmp ^= gamma2; /// Гаммируем вторую часть блока
        unsigned int encrypted_block =
                ((tmp << leftShift) | (tmp >> (32 - leftShift))) & 0xFFFFFFFF;

        char r1 = encrypted_block >> 24u;
        char r2 = encrypted_block >> 16u;
        char r3 = encrypted_block >> 8u;
        char r4 = encrypted_block;
        outputFile.write(&r1, sizeof(r1));
        outputFile.write(&r2, sizeof(r2));
        outputFile.write(&r3, sizeof(r3));
        outputFile.write(&r4, sizeof(r4));
    }
    outputFile.close();


    srand(key);
    std::ifstream readFile;
    readFile.open("test", std::ios::binary);

    std::vector<char> encryptedData((std::istreambuf_iterator<char>(readFile)),
                                    std::istreambuf_iterator<char>());
    readFile.close();

    std::vector<char> decryptedData(encryptedData.size());

    for (int i = 0; i < encryptedData.size(); ++i) {
        unsigned int gamma1 = rand();
        unsigned int gamma2 = rand();
        unsigned char b1 = encryptedData[i];
        unsigned char b2 = i + 1 < encryptedData.size() ? encryptedData[i + 1] : 0u;
        unsigned char b3 = i + 2 < encryptedData.size() ? encryptedData[i + 2] : 0u;
        unsigned char b4 = i + 3 < encryptedData.size() ? encryptedData[i + 3] : 0u;

        unsigned int encrypted_block = /// Формируем блок
                ((static_cast<unsigned int>(b1) << 24u) | (static_cast<unsigned int>(b2) << 16u) |
                 (static_cast<unsigned int>(b3) << 8u) | (static_cast<unsigned int>(b4)));

        unsigned int shifted_encrypted_block = /// Делаем обратный сдвиг
                ((encrypted_block & 0xFFFFFFFF) >> leftShift) | encrypted_block << (32 - leftShift);

        unsigned int result = /// Обратное гаммирование
                ((shifted_encrypted_block >> 16) ^ gamma1) | ((shifted_encrypted_block) ^ gamma2);

        unsigned char r1 = result >> 24;
        unsigned char r2 = result >> 16;
        unsigned char r3 = result >> 8;
        unsigned char r4 = result;
        decryptedData[i] = r1;
        decryptedData[i + 1] = r2;
        decryptedData[i + 2] = r3;
        decryptedData[i + 3] = r4;
    }
    for (unsigned int i = 0; i < decryptedData.size(); i++) { /// Вывод
        std::cout << decryptedData[i];
    }
    return 0;
}
