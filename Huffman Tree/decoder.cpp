// cpp file for the Decoder class

#include <iostream>
#include <fstream>
#include <cmath>
#include "decoder.h"
#include "huffmanTree.h"

// decodeBits function to decode the binary representation into a binary string, outputs the binary string
string Decoder::decodeBits(int arr[], size_t size, size_t arrSize) {
    string output = "";
    size_t pos = arrSize - 1;
    size_t rem = size % (8 * sizeof(int));
    cout << "POS: " << pos << " REM: " << rem << endl;
    for (size_t outerCount = 0; outerCount < size; outerCount++) {
        if(outerCount == rem || (size - outerCount) % (8 * sizeof(int)) == 0){
            pos--;
        }
        output += arr[pos] & 1 ? '1' : '0';
        arr[pos] >>= 1;
    }
    reverse(output.begin(), output.end());
    return output;
}

// decode function that inputs an input and output file and outputs the decoded message into the file
void Decoder::decode(string inputFile, string outputFile) {
    ifstream fin;
    ofstream fout;

    fin.open(inputFile);
    fout.open(outputFile);

    if (fin.is_open() && fout.is_open()) {
        HuffmanTree hTree;
        hTree.loadTree(fin);

        size_t size = 0;
        fin >> size;
        string input;
        getline(fin, input);
        int arrSize = (int) ceil(size / (8.0 * sizeof(int)));
        int arr[arrSize];
        fin.read((char *) arr, sizeof(arr));
        input = decodeBits(arr, size, arrSize);
        string output = hTree.DecodeString(input);
        fout << output;
    }
    else{
        cout << "FILE DID NOT OPEN" << endl;
    }
    fin.close();
    fout.close();
}