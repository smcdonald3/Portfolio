/*
 Filename: encoder.h
 Description: encoder class to encode strings, given input file with message and outputs a CodedTable that can be used to encode the file
 Author: Samuel McDonald
 Date: 6/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_MCDONALDS7_ENCODER_H
#define HUFFMAN_MCDONALDS7_ENCODER_H

#include <string>
#include "codedTable.h"
#include "frequencyTable.h"
#include "huffmanTree.h"

using namespace std;

class Encoder {
    HuffmanTree hTree;
    FrequencyTable fTable;

public:

    CodedTable GenerateHuffmanTree(string inputFile);

    void SaveTree(ostream& output);
};


#endif //HUFFMAN_MCDONALDS7_ENCODER_H
