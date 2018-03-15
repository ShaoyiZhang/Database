#ifndef INDEXDENERATOR_H_
#define INDEXDENERATOR_H_
#include <string>
#include <vector>
#include "OuterLayerObj.h"
using namespace std;

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
