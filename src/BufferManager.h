#ifndef BUFFERMANAGER_H_
#define BUFFERMANAGER_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class BufferManager {
private:
    unsigned int maxPageNum;
    string referIndex;
    istringstream is;
    
public:
    BufferManager(unsigned int maxNum, const string& wordLineIndex);
    ~BufferManager();
    void fetch(const string& fileName, unsigned long startingPage);
    void fetch(const string& fileName, unsigned long startingPage, unsigned int size);
    void clear();


};
#endif
