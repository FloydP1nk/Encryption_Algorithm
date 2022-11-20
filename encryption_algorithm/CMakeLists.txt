cmake_minimum_required(VERSION 3.23)
project(encryption_algorithm)

set(CMAKE_CXX_STANDARD 23)

add_executable(encryption_algorithm main.cpp header.hpp encryption.cpp decryption.cpp)
