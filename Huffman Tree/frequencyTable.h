/*
 Filename: frequencyTable.h
 Description: Declaration of the class frequencyTable to represent the table containing the key and frequency of use
 Author: Samuel McDonald
 Date: 6/12/2020
 Course: Data Structures II
*/

#include <string>
#include <map>
#include <vector>
#include <algorithm>

#ifndef HUFFMAN_MCDONALDS7_FREQUENCYTABLE_H
#define HUFFMAN_MCDONALDS7_FREQUENCYTABLE_H

using namespace std;

// struct for Row, used to store the character and its frequency
struct Row {
    string character;
    size_t frequency;

    Row() {}

    Row(const Row &a, const Row &b) {
        character = a.character + b.character;
        frequency = a.frequency + b.frequency;
    }
};

bool SortByVal(const Row &a, const Row &b);

class FrequencyTable {
    map<string, size_t> itemTable;
    vector<Row> freqTable;


public:
    void MapToVector();

    FrequencyTable();

    ~FrequencyTable();

    void Add(string input);

    size_t GetFrequency(string character);

    Row GetEnd();

    void AddFreq(Row combination);

    bool isEmpty();

    vector<string> GetKeys();

    friend ostream& operator<<(ostream& out, const FrequencyTable& ft);
};


#endif //HUFFMAN_MCDONALDS7_FREQUENCYTABLE_H
