#include "IndexLineObj.h"
/*
char* word;         // (0）maybe necessary
size_t hashVal;     // (1) hash(word)
unsigned long prevLoc; // (2) previous pair of the same word's location, starting from 1, 0 means no prev/next
unsigned long nextLoc; // (3) next pair of the same word's location
vector<unsigned long> offsets;     // (4) "pointing" to the file which stores a list of doc IDs
// bool isLocked;      // (5) concurrency (0: not locked), implement later
*/

template<typename T>
string ToString(T t) {
        stringstream ss;
        ss << t;
        return ss.str();
}

IndexLineObj::IndexLineObj(char* word, /*unsigned long& prev, unsigned long& next,*/ bool isLocked){
        this->word = word;
        this->hashVal = hash<string>{}(word); // use c++11!!
        // this.prevLoc = prev;
        // this.nextLoc = next;
        // this->isLocked = isLocked;
        offsets.clear(); // just in case
}

void IndexLineObj::addOffset(unsigned long offset) {
    // check for duplicates?
    this->offsets.push_back(offset);
}

void IndexLineObj::print() {
        // cout << "the current IndexLineObj is:"
                // << "\n\tword: " << this.word
             // << "\n\thashVal: " << this->hashVal
             // << "\n\tprev line in index: " << this.prevLoc
             // << "\n\tnext line in index: " << this.nextLoc
             // << "\n\tlist address: " << this.ptr.getFileName() << " at line " << this.ptr.getOffset()
             // << "\n\tisLocked: " << (this->isLocked ? "true": "false") << endl;
}

string IndexLineObj::format(){
    string result(this->word);
    for (std::vector<unsigned long>::iterator it = this->offsets.begin() ; it != this->offsets.end(); ++it){
            result += "/t" + to_string(*it);
    }
    // cout << "[DEBUG] <" << result << "> to index file." << endl;
    result += "\n";
    return result;
}
//
// int main(){
//     char a [] = "abc";
//     IndexLineObj* i = new IndexLineObj(a);
//     i->addOffset(100000);
//     i->addOffset(1234);
//     i->addOffset(2345);
//     i->addOffset(5125332*10000);
//     cout << i->format();
//
// }
