#include "IndexLineObj.h"

IndexLineObj::IndexLineObj(char& word, string& pagePtr, bool isLocked = false/*, size_t prev, size_t next*/){
        // this.word = word;
        this.hashVal = hash<string>{} (word); // use c++11!!
        // this.prevPairLoc = prev;
        // this.nextPairLoc = next;
        this.isLocked = isLocked;
        this.pagePtr = pagePtr;
        // create file pagePtr
}

IndexLineObj::IndexLineObj(size_t& hashVal, string& pagePtr, bool isLocked = false/*, size_t prev, size_t next*/){
        // this.word = word;
        this.hashVal = hashVal;
        // this.prevPairLoc = prev;
        // this.nextPairLoc = next;
        this.isLocked = isLocked;
        this.pagePtr = pagePtr;
        // create file pagePtr
}

void IndexLineObj::print() {
        cout << "the current IndexLineObj is:"
                // << "\n\tword: " << this.word
             << "\n\thashVal: " << this.hashVal
             << "\n\tprev line in index: " << this.prevPairLoc
             << "\n\tnext line in index: " << this.nextPairLoc
             << "\n\tlist address: " << this.ptr.getFileName() << " at line " << this.ptr.getOffset()
             << "\n\tisLocked: " << (isLocked ? "true"; "false") << endl;
}
