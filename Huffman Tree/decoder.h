/*
 Filename: decoder.h
 Description: Decoder class to decode strings, given input file with encoded message + tree and outputs the decoded message to output file
 Author: Samuel McDonald
 Date: 6/12/2020
 Course: Data Structures II
*/


#ifndef HUFFMAN_MCDONALDS7_DECODER_H
#define HUFFMAN_MCDONALDS7_DECODER_H

#include <string>
using namespace std;

class Decoder {
public:
    string decodeBits(int arr[], size_t size, size_t arrSize);
    void decode(string inputFile, string outputFile);
};


#endif //HUFFMAN_MCDONALDS7_DECODER_H
