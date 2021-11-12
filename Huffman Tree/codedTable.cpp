// cpp file for the codedTable class

#include "codedTable.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cmath>

// Function to sort the codes (1000101 etc) by size for the std::sort function
bool SortByVal(const Code &a, const Code &b){
    if(a.code.size() < b.code.size()){
        return true;
    }
    else if(a.code.size() > b.code.size()){
        return false;
    }
    else return (strcmp(a.code.c_str(), b.code.c_str()) < 0);
}

// function to take all values stored in the Map and copy them to a Vector, thus allowing easy sorting
void CodedTable::MapToVector(){
    codeVector.clear();
    for(auto& pair : codeTable){
        Code tmp;
        tmp.character = pair.first;
        tmp.code = pair.second;
        codeVector.push_back(tmp);
    }
    sort(codeVector.begin(), codeVector.end(), SortByVal);
}

// Print operator overload for the CodedTable class, prints in JSON-like format
ostream& operator<<(ostream& out, const CodedTable& ct){

    for(const Code& codePair : ct.codeVector){
        if(codePair.character == "\n"){
            cout << "{key: CR, code: " << codePair.code << "}" << endl;
        }
        else if(codePair.character == "\r"){
            cout << "{key: LF, code: " << codePair.code << "}" << endl;
        }
        else{
            cout << "{key:  " << codePair.character << ", code: " << codePair.code << "}" << endl;
        }
    }
    return out;
}

// Adds a code pair to the code Map
void CodedTable::Add(string character, string code){
    codeTable[character] = code;
}

// Outputs the binary representation given a binary string, used to write to a file
void CodedTable::OutputBitwise(ostream& out, const string& output){
    int size = (int)ceil(output.size() / (8.0 * sizeof(int)));
    int arr[size];
    size_t pos = -1;
    for(size_t outerCount = 0; outerCount < output.size(); outerCount++){
        if(outerCount % (8 * sizeof(int)) == 0){
            pos++;
            arr[pos] = 0;
        }
        if(output.at(outerCount) == '1'){
            arr[pos] = (arr[pos] << 1) + 1;
        }
        else if(output.at(outerCount) == '0'){
            arr[pos] <<= 1;
        }
    }
    out.write((char*)arr, sizeof(arr));
}

// creates the encoding based on the code generated from the huffman tree
void CodedTable::EncodeFile(string inputFile, ostream& fout){
    ifstream fin;
    fin.open(inputFile);
    string output;
    if(fin.is_open()){
        char buffer[1000];
        while(true){
            fin.read(buffer, 1000);
            for(int i = 0; i < fin.gcount(); i++){
                output += codeTable[string(1, buffer[i])];
            }
            if(fin.eof()){
                break;
            }
        }
    }
    fout << output.size() << "\n";
    OutputBitwise(fout, output);
    fin.close();
}