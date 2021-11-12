// cpp file for the frequencyTable class

#include <iostream>
#include <cstring>
#include "frequencyTable.h"

// Constructor
FrequencyTable::FrequencyTable(){}

// Destructor
FrequencyTable::~FrequencyTable(){}

// Add function for adding characters into the frequency table, increasing frequency
void FrequencyTable::Add(string input){
    if(itemTable.find(input) == itemTable.end()){
        itemTable[input] = 1;
    }
    else{
        itemTable[input] += 1;
    }
}

// outputs the frequency of a character
size_t FrequencyTable::GetFrequency(string character){
    if(itemTable.find(character) == itemTable.end()){
        return 0;
    }
    return itemTable[character];
}

//Sort in descending order, used for the std::sort function
bool SortByVal(const Row &a, const Row &b){
    if(a.frequency == b.frequency){
        if(a.character.at(0) > b.character.at(0)){
            return true;
        }
    }
    return (a.frequency > b.frequency);
}

// function to take all values stored in the Map and copy them to a Vector, thus allowing easy sorting
void FrequencyTable::MapToVector(){
    freqTable.clear();
    map<string, size_t>::iterator it;
    for(it = itemTable.begin(); it != itemTable.end(); it++){
        Row tmp;
        tmp.character = it->first;
        tmp.frequency = it->second;
        freqTable.push_back(tmp);
    }
    sort(freqTable.begin(), freqTable.end(), SortByVal);
}

// Gets and removes the last item in the frequency table, used to create the huffman tree
Row FrequencyTable::GetEnd(){
    Row tmp = freqTable.at(freqTable.size()-1);
    freqTable.erase(freqTable.end()-1);
    return tmp;
}

// Adds the frequency given to the table, placing it in a sorted position
void FrequencyTable::AddFreq(Row combination){
    vector<Row>::iterator it;
    for(it = freqTable.begin(); it != freqTable.end(); it++){
        if(it->frequency < combination.frequency){
            freqTable.insert(it, combination);
            return;
        }
    }
    freqTable.push_back(combination);
    //sort(freqTable.begin(), freqTable.end(), SortByVal);
}

// checks if the table is empty, outputs true if it is
bool FrequencyTable::isEmpty(){
    return freqTable.empty();
}

// gets all keys from the frequency table, outputs them as a vector<string>
vector<string> FrequencyTable::GetKeys(){
    vector<string> output;
    for(auto& pair : itemTable){
        output.push_back(pair.first);
    }
    return output;
}

// printing operator override for the frequency table, used for testing
ostream& operator<<(ostream& out, const FrequencyTable& ft){
    for(auto& codePair: ft.freqTable){
        if(codePair.character == "\n"){
            cout << "{key: CR, code: " << codePair.frequency << "}" << endl;
        }
        else if(codePair.character == "\r"){
            cout << "{key: LF, code: " << codePair.frequency << "}" << endl;
        }
        else{
            string a = codePair.character;
            for(size_t i = 0; i < a.size(); i++){
                if(a.at(i) == '\n'){
                    a.at(i) = '|';
                }
            }
            cout << "{key:  " << a << ", code: " << codePair.frequency << "}" << endl;
        }
    }
    return out;
}