//AUTHOR: Jack Fontenot
//Assignment Title: Program 1
//Assignment Description: Huffman Coding
//Due Date: 9/7/2025
//Date Created: 8/29/2025
//Date Last Modified: 9/7/2025

#include <iostream>
#include "huffman.h"
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<char, int> freqTable;
    buildFrequencyTable("test.txt", freqTable);

    HuffmanNode* root = buildHuffmanTree(freqTable);

    unordered_map<char, std::string> codebook;
    buildCodebook(root, "", codebook);
    serializeCodebook(codebook, "codebook.txt");

    encodeFile("test.txt", "encoded.bin", codebook);

    unordered_map<char, std::string> decodedCodebook;
    deserializeCodebook(decodedCodebook, "codebook.txt");
    HuffmanNode* decodedRoot = rebuildTreeFromCodebook(decodedCodebook);
    decodeFile("encoded.bin", "decoded.txt", decodedRoot);

    delete root;
    delete decodedRoot;
    return 0;
}
