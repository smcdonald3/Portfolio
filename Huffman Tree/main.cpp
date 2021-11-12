// main.cpp for running the huffmanTree lab, created by Samuel W. McDonald on 6/12/2020

#include <iostream>
#include <cstring>
#include <fstream>
#include "encoder.h"
#include "decoder.h"

using namespace std;

// receives 4 inputs: ./huffman -encode inputfile outputfile

int main(int argc, char *argv[]) {
    //checks for 4 arguments
    if (argc < 4) {
        cerr << "Please enter three arguments (-encode or -decode, inputfile, outputfile)" << endl;
        return 1;
    }
    if (strcmp(argv[1], "-encode") == 0) {
        // uses Encoder class to generate a CodedTable
        Encoder encode;
        CodedTable code = encode.GenerateHuffmanTree(argv[2]);
        code.MapToVector();
        cout << code;

        // outputs the huffman tree and encoded message in binary
        ofstream fout;
        fout.open(argv[3]);
        if (fout.is_open()) {
            encode.SaveTree(fout);
            code.EncodeFile(argv[2], fout);
            fout.close();
        }
    }
    else if(strcmp(argv[1], "-decode") == 0){
        // uses Decoder class to decode and output the message
        Decoder decode;
        decode.decode(argv[2], argv[3]);
    }
}