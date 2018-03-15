#ifndef OUTERLAYEROBJ_H_
#define OUTERLAYEROBJ_H_
#include <string>
#include <vector>
#include "IndexLineObj.h"
using namespace std;



class OuterLayerObj {
private:
    char* fileName;
    vector<size_t> hashValues; // hash value after hash value, size = # lines of index file - 1 (metadata)
    size_t nextLineNum;
    size_t pageSize;
public:
    OuterLayerObj(const char& fileName, size_t pageSize);
    ~OuterLayerObj();
    vector<string> findPages(size_t& hashValue); // return a list of file names (pages) of docID lists of the hash value (word)
    void append(size_t& hashValue, size_t& docID);
};

#endif
