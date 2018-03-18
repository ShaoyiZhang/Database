#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class BulkLoader {
private:
    BPlusTree bPtree;
    BufferManager bm;
public:
    BulkLoader();
    ~BulkLoader();
    string load(const string& indexFile); // return bplusTree index file name

};
#endif
