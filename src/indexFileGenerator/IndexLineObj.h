#ifndef INDEXLINEOBJ_H_
#define INDEXLINEOBJ_H_
#include <string>
#include <vector>
using namespace std;

class IndexLineObj {
private:
    // char* word;      // not necessary
    size_t hashVal;     // (1) hash(word)
    // size_t prevPairLoc; // (2) previous pair of the same word's location, starting from 1, 0 means no prev/next
    // size_t nextPairLoc; // (3) next pair of the same word's location
    string pagePtr;     // (4) "pointing" to the file which stores a list of doc IDs
    bool isLocked;      // (5) concurrency (0: not locked), implement later
public:
    IndexLineObj(char& word, string& ptr, bool isLocked = false/*, size_t prev, size_t next*/);
    IndexLineObj(size_t& hashVal, string& ptr, bool isLocked = false/*, size_t prev, size_t next*/);

    ~IndexLineObj();
    // setPrev(size_t prev) {this.prevPairLoc = prev;};
    // setNext(size_t next) {this.nextPairLoc = next;};
    // size_t getPrev() {return this.prevPairLoc};
    // size_t getNext() { return this.nextPairLoc};
    void print();       // output to console for debugging, OuterLayerObj controls writing process
    // char* toBinFile(const IndexLineObj& pair); // return binary format, implement later
};

#endif
