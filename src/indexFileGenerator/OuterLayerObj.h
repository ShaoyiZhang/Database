#ifndef OUTERLAYEROBJ_H_
#define OUTERLAYEROBJ_H_
#include <string>
#include <vector>
#include "IndexLineObj.h"
using namespace std;

class OuterLayerObj {
private:
    vector<size_t> hashValues; // add each hash value to a vector at first occurences
    // then the index of each element + 2 = line number
    // http://www.dreamincode.net/forums/topic/36630-find-index-of-vector-element/
    unsigned long pageSize;
public:
    OuterLayerObj(unsigned long pageSize);
    vector<unsigned long> findOffsets(size_t& hashValue); // return a list of offsets where lists of doc ids are
    void append(size_t& hashValue, unsigned long& docID); // many things happen here
};

#endif
