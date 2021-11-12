// cpp file for the HuffmanTree class

#include <iomanip>
#include <iostream>
#include <fstream>
#include "huffmanTree.h"

// Constructor
HuffmanTree::HuffmanTree() {}

// Clears the tree and deletes all dynamically allocated memory
void HuffmanTree::Clear(Node *n) {
    if (n->left != nullptr) {
        Clear(n->left);
    }
    if (n->right != nullptr) {
        Clear(n->right);
    }
    delete n;
}

// Destructor that clears all roots of the tree (Ideally only 1 remains)
HuffmanTree::~HuffmanTree() {
    for (size_t i = 0; i < roots.size(); i++) {
        Clear(roots.at(i));
    }
    roots.clear();
}

// Remove function that removes a node with the same values as the input Row from the roots vector and outputs the Node*
Node *HuffmanTree::Remove(Row row) {
    for (size_t i = 0; i < roots.size(); i++) {
        if (roots.at(i)->row.character == row.character) {
            Node *node = roots.at(i);
            roots.erase(roots.begin() + i);
            return node;
        }
    }
    return nullptr;
}

// Adds a root node and/or children nodes depending on whether they already exist.  Outputs the Row of the root node for updating the frequency table
Row HuffmanTree::Add(const Row &left, const Row &right) {
    Node *rootNode;
    Node *leftNode;
    Node *rightNode;

    if (left.character.size() == 1) {
        leftNode = new Node(left);
    } else {
        leftNode = Remove(left);
    }

    if (right.character.size() == 1) {
        rightNode = new Node(right);
    } else {
        rightNode = Remove(right);
    }

    rootNode = new Node(leftNode, rightNode, Row(left, right));
    roots.push_back(rootNode);
    treeOutput.push_back(left);
    treeOutput.push_back(right);
    return rootNode->row;
}

// Recursive function for Encode, adds 1 or 0 to the string depending on whether the left or right path is taken
string HuffmanTree::EncodeRecurse(char c, Node *n) {
    if (n->left != nullptr && n->left->row.character.find(c) != string::npos) {
        return "1" + EncodeRecurse(c, n->left);
    } else if (n->right != nullptr) {
        return "0" + EncodeRecurse(c, n->right);
    } else {
        return "";
    }
}

// Starter for the recursive function, starts it at the root of the tree and returns the full path
string HuffmanTree::Encode(char c) {
    Node *n = roots.at(0);
    return EncodeRecurse(c, n);
}

// Recursive function for printing the tree, used for testing
void HuffmanTree::PrintTreeRec(Node *n, int indent) {
    for (int i = 0; i < indent * 1; i++) {
        cout << " ";
    }
    string a = n->row.character;
    for (size_t i = 0; i < a.size(); i++) {
        if (a.at(i) == '\n') {
            a.at(i) = '|';
        }
    }
    cout << a << ", " << n->row.frequency << endl;
    if (n->left != nullptr) {
        PrintTreeRec(n->left, indent + 2);
    }
    if (n->right != nullptr) {
        PrintTreeRec(n->right, indent + 2);
    }
}

// Function to start the recursive function, starts the function at the root.  used for testing
void HuffmanTree::PrintTree() {
    Node *n = roots.at(0);
    PrintTreeRec(n, 0);
}

// Function to save the tree at the beginning of a file so it can be decoded
void HuffmanTree::SaveTree(ostream &output) {
    output << treeOutput.size() << "\n";
    for (Row r : treeOutput) {
        string a = r.character;
        size_t i;
        while ((i = a.find("\\", i + 2)) != string::npos) {
            a.replace(i, 1, "\\\\");
        }
        while ((i = a.find("\n")) != string::npos) {
            a.replace(i, 1, "\\n");
        }
        while ((i = a.find("\r")) != string::npos) {
            a.replace(i, 1, "\\r");
        }
        output << a << "\n" << r.frequency << "\n";
    }
}

// Replace char function to undo the saving of \n, \r, and \ characters
void HuffmanTree::ReplaceChar(string &a) {
    size_t i;
    while ((i = a.find("\\\\", i + 1)) != string::npos) {
        a.replace(i, 2, "\\");
    }
    while ((i = a.find("\\n")) != string::npos) {
        a.replace(i, 2, "\n");
    }
    while ((i = a.find("\\r")) != string::npos) {
        a.replace(i, 2, "\r");
    }
}

// Load tree function that inputs the file and creates the tree from the file
void HuffmanTree::loadTree(istream &input) {
    size_t length;
    input >> length;
    string tmp;
    getline(input, tmp);
    for (size_t i = 0; i < length; i += 2) {
        string characterL;
        getline(input, characterL);
        string frequencyL;
        getline(input, frequencyL);
        string characterR;
        getline(input, characterR);
        string frequencyR;
        getline(input, frequencyR);

        Row left;
        Row right;


        ReplaceChar(characterL);
        left.character = characterL;
        left.frequency = stoi(frequencyL);

        ReplaceChar(characterR);
        right.character = characterR;
        right.frequency = stoi(frequencyR);

        Add(left, right);
    }
}

// Recursive function for finding a character in the leaf nodes with a specific path, travels down the tree according to the path until it finds the character.
string HuffmanTree::FindCharRec(const string &input, size_t &pos, Node *n) {
    if (n->left == nullptr) {
        return n->row.character;
    }
    if (input.at(pos) == '1') {
        pos++;
        return FindCharRec(input, pos, n->left);
    }
    if (input.at(pos) == '0') {
        pos++;
        return FindCharRec(input, pos, n->right);
    }
    return "";
}

// Decodes the string using the recursive function FindCharRec, outputs the decoded string
string HuffmanTree::DecodeString(const string &input) {
    size_t pos = 0;
    string output;
    while (pos < input.size()) {
        output += FindCharRec(input, pos, roots[0]);
    }
    return output;
}