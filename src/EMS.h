//
// Created by Zhancheng Qian on 2018/3/10.
//

#ifndef DATABASE_EMS_H
#define DATABASE_EMS_H

static int MAX = 65536;
static int MAX_BUFFER = 8096;

//char metadata[100];
static int numRows;

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct IndexRecord{
    string word;
//    size_t prev;
//    size_t next;
    vector<unsigned long> vec;
};

void pR (struct IndexRecord ir);
void gen_random(char *s, const int len);
void mergeTwoFiles(const char *input_1, const char *input_2, const char *output_file);
void setBufferSize(int size);

#endif //DATABASE_EMS_H
