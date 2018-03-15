#ifndef INDEXDENERATOR_H_
#define INDEXDENERATOR_H_
#include <string>
#include <vector>
using namespace std; //

#include "../File.h" // for filePointer


class IndexLineObj {
private:
    // char* word;      // not necessary
    size_t hashVal;     // (1) hash(word)
    size_t prevPairLoc; // (2) previous pair of the same word's location, starting from 1, 0 means no prev/next
    size_t nextPairLoc; // (3) next pair of the same word's location
    FilePointer ptr;    // (4) pointing to the file which stores a list of doc IDs
    bool isLocked;      // (5) concurrency (0: not locked), implement later
public:
    IndexLineObj(char& word, FilePointer& fptr, bool isLocked = false, size_t prev, size_t next);
    ~IndexLineObj();
    setPrev(size_t prev) {this.prevPairLoc = prev;};
    setNext(size_t next) {this.nextPairLoc = next;};
    size_t getPrev() {return this.prevPairLoc};
    size_t getNext() { return this.nextPairLoc};
    void print();       // output to console for debugging, OuterLayerObj controls writing process
    char* toBinFile(const IndexLineObj& pair); // return binary format, implement later
};

class OuterLayerObj {
private:
    char* fileName;
    vector<size_t> hashValues; // hash value after hash value, size = # lines of index file - 1 (metadata)
    size_t nextLineNum;
    size_t pageSize;
public:
    OuterLayerObj(const char& fileName, size_t pageSize);
    ~OuterLayerObj();
    void append(IndexLineObj& thisLine);
    vector<string> findPages(size_t& hashValue); // return a list of file names (pages) of docID lists of the hash value (word)
    string addToListPage(size_t& hashValue, size_t& pageSize, size_t docID);
};

class IndexFileObj{
private:
    char* dataFileName;
    char* indexFileName;
    size_t lineReached;    // failure back up -- can we serialize the program? (recover classes' states)
    vector<size_t> pages;  // 1 means one more page, name: indexFileName + "1"
    char* metaData;        // first line
    OuterLayerObj* indexObj; // rest of the file
public:
    IndexFileObj(char* dataFileName, char* indexFileName, size_t pageSize); // pass pageSize to OuterLayerObj
    ~IndexFileObj();
    getIndexFile() {return indexFileName};
};

#endif
