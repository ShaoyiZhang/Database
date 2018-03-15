#include "OuterLayerObj.h"


// helper functions
// https://www.experts-exchange.com/questions/24234582/Convert-size-t-to-string.html
template<typename T>
string ToString(T t) {
        stringstream ss;
        ss << t;
        return ss.str();
}

bool fileExist (const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void addDocID(const string& name, size_t& docID){
    // TODO

}

// https://www.codeproject.com/Articles/9016/Quick-and-Dirty-Series-C-FileSize-function
// https://stackoverflow.com/questions/41714291/can-stdstreampos-be-converted-to-size-t-implicitly/41714540#41714540
size_t fileSize(const char* sFileName)
{
  ifstream f;
  f.open(sFileName, ios_base::binary | ios_base::in);
  if (!f.good() || f.eof() || !f.is_open()) { return 0; }
  f.seekg(0, ios_base::beg);
  ifstream::pos_type begin_pos = f.tellg();
  f.seekg(0, ios_base::end);
  return static_cast<size_t>(f.tellg() - begin_pos);
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
    string name = hvStr + ".0";
    while(fileExist(name)) {
        pageList.push_back(name);
        offset++;
        name = hvStr + "." + ToString<size_t>(offset);
    }
    return pageList;
}


void OuterLayerObj::append(size_t& hashValue, size_t& docID){
    vector<string> pages = findPages(hashValue);
    size_t lastPageSize = fileSize(pages.back();
    if (!pages.empty() && lastPageSize <= this.pageSize && lastPageSize >= 0) {
        // if pages found and the last page is not full, just append docID to it
        addDocID(pages.back(),docID);

    } else {
        // otherwise, create new line in OuterLayer and new file page
        string pageAddress = ToString<size_t>(hashValue) + "." + ToString<size_t>(pages.size());
        IndexLineObj newLine = new IndexLineObj(hashValue, pageAddress);
        addDocID(pageAddress, docID);
    }

}
