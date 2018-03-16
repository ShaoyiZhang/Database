#include "IndexLineObj.h"

IndexLineObj::IndexLineObj(char& word, string& pagePtr, bool isLocked = false, unsigned long& prev, unsigned long& next){
        this.word = word;
        this.hashVal = hash<string>{} (word); // use c++11!!
        this.prevLoc = prev;
        this.nextLoc = next;
        this.isLocked = isLocked;
        this.pagePtr = pagePtr;
        // create file pagePtr
}

void IndexLineObj::print() {
        cout << "the current IndexLineObj is:"
                // << "\n\tword: " << this.word
             << "\n\thashVal: " << this.hashVal
             << "\n\tprev line in index: " << this.prevLoc
             << "\n\tnext line in index: " << this.nextLoc
             << "\n\tlist address: " << this.ptr.getFileName() << " at line " << this.ptr.getOffset()
             << "\n\tisLocked: " << (isLocked ? "true"; "false") << endl;
}
