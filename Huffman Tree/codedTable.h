/*
 Filename: codedTable.h
 Description: Declaration of the class CodedTable to represent the table containing the key and encoded counterpart
 Author: Samuel McDonald
 Date: 6/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_MCDONALDS7_CODEDTABLE_H
#define HUFFMAN_MCDONALDS7_CODEDTABLE_H

#include <map>
#include <string>
#include <ostream>
#include <vector>

using namespace std;

// struct for storing a character and its respective code
struct Code{
    string character;
    string code;
};

bool SortByVal(const Code &a, const Code &b);

class CodedTable {
    map<string, string> codeTable;
    vector<Code> codeVector;

public:
    void Add(string character, string code);
    void EncodeFile(string inputFile, ostream& fout);
    friend ostream& operator<<(ostream& out, const CodedTable& ct);
    void MapToVector();
    void OutputBitwise(ostream& out, const string& output);
};


#endif //HUFFMAN_MCDONALDS7_CODEDTABLE_H
