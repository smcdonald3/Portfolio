/*
 Filename: huffmanTree.h
 Description: Declaration of the class HuffmanTree to represent the binary huffman tree that is created to express the data
 Author: Samuel McDonald
 Date: 6/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_MCDONALDS7_HUFFMANTREE_H
#define HUFFMAN_MCDONALDS7_HUFFMANTREE_H

#include "frequencyTable.h"
#include <assert.h>

// Struct for Node, used as the nodes of the tree
struct Node{
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Row row;

    Node(Row row) : row(row){}
    Node(Node* left, Node* right, Row row) : left(left), right(right), row(row){
        left->parent = this;
        right->parent = this;
    }
};

class HuffmanTree {
    vector<Node*> roots;
    vector<Row> treeOutput;

public:
    HuffmanTree();
    ~HuffmanTree();

    Row Add(const Row& left, const Row& right);
    void Clear(Node* n);
    Node* Remove(Row row);
    string EncodeRecurse(char c, Node* n);
    string Encode(char c);
    void PrintTreeRec(Node* n, int indent);
    void PrintTree();
    void SaveTree(ostream& output);
    void ReplaceChar(string& a);
    void loadTree(istream& input);
    string FindCharRec(const string& input, size_t& pos, Node* n);
    string DecodeString(const string& input);
};


#endif //HUFFMAN_MCDONALDS7_HUFFMANTREE_H
