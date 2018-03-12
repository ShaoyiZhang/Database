//
// Created by Zhancheng Qian on 2018/3/10.
//

#ifndef DATABASE_EMS_H
#define DATABASE_EMS_H

int MAX = 65536;
int MAX_BUFFER = 8096;

//char metadata[100];
int numRows;

#include <cstdlib>
#include <string>

using namespace std;

class EMS {

};

struct IndexRecord{
    size_t hash;
    size_t prev;
    size_t next;
    string filePointer;
};

void pR (struct IndexRecord ir);


#endif //DATABASE_EMS_H
