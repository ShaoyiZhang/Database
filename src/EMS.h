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
#include <vector>

using namespace std;

class EMS {

};

struct IndexRecord{
    string word;
//    size_t prev;
//    size_t next;
    vector<unsigned long> vec;
};

void pR (struct IndexRecord ir);
void gen_random(char *s, const int len);

#endif //DATABASE_EMS_H
