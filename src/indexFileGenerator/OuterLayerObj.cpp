#include "OuterLayerObj.h"


// helper functions
// https://www.experts-exchange.com/questions/24234582/Convert-size-t-to-string.html
template<typename T>
string ToString(T t) {
        stringstream ss;
        ss << t;
        return ss.str();
}
// OuterLayerObj
OuterLayerObj::OuterLayerObj(const char& fileName, size_t pageSize){
        this.fileName = fileName;
        this.hashValues.clear(); // just in case?
        this.nextLineNum = 2; // first line is reserved for metaData
        this.pageSize = pageSize;
}

OuterLayerObj::~OuterLayerObj(){
        this.hashValues.clear();
}

vector<string> OuterLayerObj::findPages(size_t& hashValue){
        // given a hashValue, return a list of pages which store docIDs for such hash value
        vector<string> pageList;
        string hvStr = ToString<size_t>(hashValue);
        size_t offset = 0; // to start with
        string name = hvStr + "." + ToString<size_t>(offset);
        ifstream f(name.c_str());
        while(f.good()) {

        }
}

string OuterLayerObj::addToListPage(size_t& hashValue, size_t& pageSize, size_t docID) {

}

void OuterLayerObj::append(IndexFileObj& thisLine){

}
