#ifndef INDEXDENERATOR_H_
#define INDEXDENERATOR_H_

#include "string.h"
#include <string>
#include <vector>
using namespace std; //

#include "../File.h" // for filePointer


class IndexLineObj {
private:
    char* word;
    size_t hashVal;     // (1) hash(word)
    size_t prevPairLoc; // (2) previous pair of the same word's location
    size_t nextPairLoc; // (3) next pair of the same word's location
    FilePointer ptr;    // (4) pointing to the file which stores a list of doc IDs
    char isLocked;      // (5) concurrency and implement later
    char* toBinFile(const IndexLineObj& pair); // return binary format, implement later
public:
    IndexLineObj(const char* word, const FilePointer& fptr, char isLocked = 0 /*, size_t prev, size_t next */);
    ~IndexLineObj();
    void print();       // output to console for debugging, OuterLayerObj controls writing process
};

class OuterLayerObj {
private:
    char* fileName;
    vector<size_t> hashValues; // hash value after hash value, size = # lines of index file - 1 (metadata)
    size_t nextLineNum;
public:
    OuterLayerObj(char* fileName);
    ~OuterLayerObj();
    void append(IndexLineObj& thisLine);
};

/*
std::hash<char*>{}() does not return same value
class HashTable {
}
*/
class IndexFileObj{
private:
    char* dataFileName;
    char* indexFileName;
    char* pageSize;
    size_t pageNum;
    vector<size_t> pages; // 1 means one more page, name: indexFileName + "1"
    char* metaData; // first line
    OuterLayerObj index; // rest of the file
public:
    IndexFileObj(char* dataFileName, char* indexFileName, size_t pageSize);
    ~IndexFileObj();
    getIndexFile(); // return indexFileName
};

#endif
