//AUTHOR: Jack Fontenot
//Assignment Title: Program 1
//Assignment Description: Huffman Coding
//Due Date: 9/7/2025
//Date Created: 8/29/2025
//Date Last Modified: 9/7/2025
#include "huffman.h"

//Builds a frequency table so Huffman nodes can have a frequency
void buildFrequencyTable(string fName, unordered_map<char, int>& m){
    ifstream file;
    char c;
    string line;
    file.open(fName);

    while(file.get(c)){
        m[c]++;
    }

    file.close();
}

//Creates a huffman tree
HuffmanNode* buildHuffmanTree(unordered_map<char, int>& m){
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, comp> q;
    HuffmanNode* newTree;
    unordered_map<char, string> book;

    for(auto v : m){
        HuffmanNode* node = new HuffmanNode();
        node->c = v.first;
        node->f = v.second;
        node->l = nullptr;
        node->r = nullptr;
        q.push(node);
    }

    while(q.size() > 1){
        HuffmanNode* T1 = q.top();
        q.pop();
        HuffmanNode* T2 = q.top();
        q.pop();
        newTree = new HuffmanNode;
        newTree->l = T1;
        newTree->r = T2;
        newTree->c = '\0';
        newTree->f = T1->f + T2->f;
        q.push(newTree);
    }

    newTree = q.top();
    q.pop();

    return newTree;
}

//Creates a codebook based off a Huffman tree
void buildCodebook(HuffmanNode* root, string s,
                   unordered_map<char, string>& book){

    if(root->c != '\0'){
        book[root->c] = s;
        return;
    }

    buildCodebook(root->l, s + "0", book);
    buildCodebook(root->r, s + "1", book);
}

//Writes out the codebook to a .txt file
void serializeCodebook(unordered_map<char, string>& book, string fName){
    ofstream file;
    file.open(fName);
    int asciiV;

    for(auto& m : book){
        asciiV = m.first;
        file << asciiV << " " << m.second << endl;
        //cout << asciiV << " " << m.second << endl;
    }

    file.close();
}

//reads from a .txt and compresses it into a bin file
void encodeFile(string test, string binary,
                unordered_map<char, string>& book){
    ifstream iFile;
    ofstream oFile;
    iFile.open(test);
    oFile.open(binary, ios::binary | ios::out);
    char c;
    char out;
    string buff;

    while(iFile.get(c)){
        buff = book[c];
        out = 0;

        if(!iFile.eof()){
            for(size_t i = 0; i < buff.size(); ++i){
                if(buff.at(i) == '0'){
                    out *= 2;
                }
                else{
                    out = (out * 2) + 1;
                }
            }
        }
        else{
            int diff = 8 - buff.size();
            for(size_t i = 0; i < buff.size(); ++i){
                if(buff.at(i) == '0'){
                    out *= 2;
                }else{
                    out = (out * 2) + 1;
                }
            }
            for(int i = 0; i < diff; ++i){
                out *= 2;
            }
        }
        oFile.put(out);
    }

    iFile.close();
    oFile.close();
}

//reads a codebook from a file and deserializes it
void deserializeCodebook(unordered_map<char, string>& book, string fName){
    string s;
    int c;
    char bookF;
    ifstream file;
    file.open(fName);

    while(file >> c){
        bookF = c;
        getline(file, s);
        book[bookF] = s;
    }

    file.close();
}

//Uses codeBook to build a Huffman tree
HuffmanNode* rebuildTreeFromCodebook(unordered_map<char, string>& book){
    HuffmanNode* root = new HuffmanNode;
    unordered_map<char, int> newB;
    char c;

    for(auto& v : book){
        c = v.first;
        newB[c] = stoi(v.second);
    }

    root = buildHuffmanTree(newB);

    return root;
}

//Decodes compressed binary file into a .txt file in ASCII
void decodeFile(string bin, string decoded, HuffmanNode* node){

    ifstream binF;
    ofstream outF;
    char in;
    HuffmanNode* curr = node;

    binF.open(bin, ios::binary | ios::in);
    outF.open(decoded);

    while(binF.get(in)){
        for(int i = 0; i < 8; ++i){
            if(in & (1 << (7 - i))){
                curr = curr->r;
            }
            else{
                curr = curr->l;
            }

            if(curr->c != '\0'){
                outF << curr->c;
                //cout << curr->c;
                curr = node;
            }
        }
    }

    curr = node;



    binF.close();
    outF.close();

}
