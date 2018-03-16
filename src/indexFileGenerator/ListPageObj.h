#ifndef LISTPAGEOBJ_H_
#define LISTPAGEOBJ_H_
#include <iostream>
#include <vector>
using namespace std;

class ListPageObj {
private:
    char* pageName;
    size_t corresHashVal;
    vector<size_t> idList;
public:
    ListPageObj(char* pageName, size_t hashVal);
    ~ListPageObj();
    size_t getHashVal();
    vector<size_t> dedup();
};

#endif
