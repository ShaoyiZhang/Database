#ifndef OUTERLAYEROBJ_H_
#define OUTERLAYEROBJ_H_
#include <string>
#include <vector>
#include <unordered_map>
#include "IndexLineObj.h"
using namespace std;

class OuterLayerObj {
private:
    // vector<size_t> hashValues; // add each hash value to a vector at first occurences
    // vector<unsigned long long> bitPos; // and note down their bit position (used for fseek)
    unordered_map<size_t, unsigned long long> hash_bitPos; // hash_bitPos[hashVal] = bit location in the outer index
    // then the index of each element + 2 = line number
    // http://www.dreamincode.net/forums/topic/36630-find-index-of-vector-element/
    unsigned long pageSize;
public:
    OuterLayerObj(unsigned long pageSize);
    ~OuterLayerObj();
    vector<unsigned long> findOffsets(size_t& hashValue); // return a list of offsets where lists of doc ids are
    void append(size_t hashValue, unsigned long docID); // many things happen here
};

#endif
