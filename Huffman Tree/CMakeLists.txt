cmake_minimum_required(VERSION 3.10)
project(huffman_mcdonalds7)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffman_mcdonalds7 main.cpp huffmanTree.h huffmanTree.cpp frequencyTable.h frequencyTable.cpp encoder.h encoder.cpp codedTable.h codedTable.cpp decoder.h decoder.cpp)
