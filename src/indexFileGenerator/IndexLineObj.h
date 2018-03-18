#ifndef INDEXLINEOBJ_H_
#define INDEXLINEOBJ_H_
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class IndexLineObj {
private:
    char* word;         // (0）maybe necessary
    size_t hashVal;     // (1) hash(word)
    // unsigned long prevLoc; // (2) previous pair of the same word's location, starting from 1, 0 means no prev/next
    // unsigned long nextLoc; // (3) next pair of the same word's location
    vector<unsigned long> offsets;     // (4) bit-offsets
    // bool isLocked;      // (5) concurrency (0: not locked), implement later
public:
    IndexLineObj(char* word, /*unsigned long& prev, unsigned long& next,*/ bool isLocked = false);
    ~IndexLineObj();
    void addOffset(unsigned long offset);
    // void setPrev(unsigned long prev) {this.prevLoc = prev;};
    // void setNext(unsigned long next) {this.nextLoc = next;};
    // unsigned long getPrev() {return this.prevLoc};
    // unsigned long getNext() { return this.nextLoc};
    void print();       // output to console for debugging, OuterLayerObj controls writing process
    string format();
    // char* toBinFile(const IndexLineObj& pair); // return binary format, implement later
};

#endif
