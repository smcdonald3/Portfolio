//
// Created by samue on 6/12/2020.
//

#include <fstream>
#include <iostream>
#include "encoder.h"

// Function to generate the huffman tree then generate the CodedTable from the tree, returns the generated CodedTable
CodedTable Encoder::GenerateHuffmanTree(string inputFile){
    ifstream fin;
    fin.open(inputFile);
    if(fin.is_open()){
        char buffer[1000];
        while(true){
            fin.read(buffer, 1000);
            for(int i = 0; i < fin.gcount(); i++){
                fTable.Add(string(1, buffer[i]));
            }
            if(fin.eof()){
                break;
            }
        }
    }
    fin.close();

    fTable.MapToVector();

    while(true){
        Row left = fTable.GetEnd();
        Row right = fTable.GetEnd();
        Row r = hTree.Add(left, right);
        if(fTable.isEmpty()){
            break;
        }
        fTable.AddFreq(r);
    }

    vector<string> keys = fTable.GetKeys();

    CodedTable code;

    for(string k : keys){
        code.Add(k, hTree.Encode(k.at(0)));
    }

    return code;
}

// Function to save the huffman tree to the output file
void Encoder::SaveTree(ostream& output){
    hTree.SaveTree(output);
}