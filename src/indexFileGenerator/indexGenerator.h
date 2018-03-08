#ifndef INDEXDENERATOR_H_
#define INDEXDENERATOR_H_

#include "string.h"
#include <string>
#include <vector>
using namespace std;

#include "../File.h" // for filePointer

class WordFPtrPair {
public:
    char* word;
    size_t hashVal;
    FilePointer ptr;
    WordFPtrPair(char* word, FilePointer fptr);
    char* toBinFile(const WordFPtrPair & pair); // return binary format
};

class OuterLayer {
public:
    char* fileName;
    vector<size_t> words_hashed;
    size_t pageNum;
    OuterLayer(char* fileName);
    void add(WordFPtrPair wordFPtrPair);
    void delete(size_t key);
};

class SecondaryLayer {
public:
    char* fileName;
    size_t pageNum;
    SecondaryLayer(char* fileName);


};

class indexFileObj {
public:
    OuterLayer outter;
    SecondaryLayer inner;
    indexFileObj(char* outFileName, char* inFileName);

};

#endif
