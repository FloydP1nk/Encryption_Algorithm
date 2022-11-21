#include "header.hpp"

int main() {
    //std::string text = argv[1];
    std::string message = "qwerty ";
    //int key = atoi(argv[2]);
    unsigned int leftShift = 3;
    int key = 4;
    size_t size = message.size();
    std::vector<unsigned char> bytes(size);

    for (size_t i = 0; i < message.size(); ++i) { /// Создаем вектор символов
        bytes[i] = message[i];
    }
    for (auto &iter: bytes) { /// Сдвиг
        iter = iter << leftShift | iter >> (8 - leftShift);
    }
    encryption(bytes, key);

    for (auto &iter: bytes) { /// Вывод преобразованного сообщения
        std::cout << iter;
    }

    std::ofstream f1;
    f1.open("file.txt", std::ios::binary);
    for (auto i: bytes) { /// Вывод
        char ch = static_cast<char>(i);
        f1.write(&ch, sizeof(ch));
    }
    f1.close();
    /////////////////

    std::ifstream f2;
    f2.open("file.txt", std::ios::binary);

    std::vector<char> encryptedData((std::istreambuf_iterator<char>(f2)),
                                    std::istreambuf_iterator<char>());
    f2.close();
    for (size_t i = 0; i < size; ++i) {
        bytes[i] = static_cast<unsigned char>(encryptedData[i]);
    }
    std::cout << std::endl;

    decryption(bytes, key);

    for (auto &iter: bytes) { /// Обратный сдвиг
        iter = iter << (8 - leftShift) | iter >> leftShift;
    }

    for (auto &iter: bytes) { /// Вывод
        std::cout << iter;
    }
}
