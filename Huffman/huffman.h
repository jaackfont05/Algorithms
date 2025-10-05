//AUTHOR: Jack Fontenot
//Assignment Title: Program 1
//Assignment Description: Huffman Coding
//Due Date: 9/7/2025
//Date Created: 8/29/2025
//Date Last Modified: 9/7/2025
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct HuffmanNode{
    int f;
    char c = '\0';
    HuffmanNode* l = nullptr;
    HuffmanNode* r = nullptr;

    HuffmanNode(){
        f = 0;
        c = '\0';
        l = nullptr;
        r = nullptr;
    }

    HuffmanNode(const HuffmanNode& other){
        f = other.f;
        c = other.c;
        l = other.l;
        r = other.r;
    }

    HuffmanNode* operator=(const HuffmanNode* other){
        this->f = other->f;
        this->c = other->c;
        this->r = other->r;
        this->l = other->l;

        return this;
    }

};

struct comp{
    bool operator()(const HuffmanNode* l, const HuffmanNode* r) const{
        return l->f > r->f;
    }
};



void buildFrequencyTable(string, unordered_map<char, int>&);

HuffmanNode* buildHuffmanTree(unordered_map<char, int>&);

void buildCodebook(HuffmanNode*, string, unordered_map<char, string>&);

void serializeCodebook(unordered_map<char, string>&, string);

void encodeFile(string, string, unordered_map<char, string>&);

void deserializeCodebook(unordered_map<char, string>&, string);

HuffmanNode* rebuildTreeFromCodebook(unordered_map<char, string>&);

void decodeFile(string, string, HuffmanNode*);



#endif // HUFFMAN_H
