#include "IndexFileObj.h"

/*
   notes to myself: upper/lower case -- already dealt
                  non-alphabetic    http://www.cplusplus.com/reference/cstring/strtok/ <--- xxx, yyy
                                    http://www.cplusplus.com/reference/cctype/isalpha/ <--- ! !
                                    // special cases: gluten-free, it 's, i 'm, : )
                                    // how??
                                    // generally, how do we deal with symbols? ignore it?
        to Qian: add a feature to change the file name (make it sequential) although cannot see the point of doing so (block I/O)
        ignore words longer than 256
        secondary page name: hash value + 0,1,2,...
        convert to binary file?

        root of all generated files?
 */

using namespace std;

// IndexFileObj
IndexFileObj::IndexFileObj(char* dataFileName, char* indexFileName, size_t pageSize) {
        // read in parameters
        this.dataFileName = dataFileName;
        this.indexFileName = indexFileName;
        this.pageSize = pageSize;

        this.lineReached = 0;
        this.pages.clear(); // just in case
        this.metaData = ""; // in the format of [prevFileName]/t[nextFileName]

        this.indexObjPtr = new OuterLayerObj(fileName, pageSize);

        // create new index file
        fstream indexFileStream;
        indexFileStream.open(indexFileName, fstream::out);

        // create read stream
        istream dataFile(dataFileName);
        string thisLine; // in data file (one document)

        // process data file line by line
        while (getline(dataFile, thisLine)) {
                cout << "[TEST] current doc in process is: " << thisLine << endl;

                // 1. convert from string to char* (cannot simply use c_str since it's non-static)
                // [discarded] https://stackoverflow.com/questions/7352099/stdstring-to-char
                // not exception safe, discarded
                // char * cThisLine = new char[thisLine.length() + 1];
                // strcpy(cThisLine, thisLine.c_str());

                // https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char/4152881#4152881
                vector<char> thisLineVec(thisLine.begin(), thisLine.end());
                thisLineVec.push_back('\0');
                char* cThisLine = &thisLineVec[0];

                // 2. get doc ID by tokenize it
                char * word = strtok (cThisLine," ,.-!()"); // first word must be DOC ID
                cout << word << endl;
                string wordStr = string(word);
                size_t docID = (size_t) stoi(wordStr.substr(3));
                cout << docID << endl;

                // 3. deal with the rest words of the same line
                word = strtok (NULL, " ,.-!()");
                while (word != NULL) {
                        // ignore all words with length >= 256
                        if (strlen(word) >= 256) {
                                continue;
                        }
                        // deal with normal words
                        size_t hashedVal = hash<string>{} (word);
                        cout << hashedVal << " " << word << endl;

                        // call OuterLayerObj function to add doc ID to word's doc-list-page
                        indexObjPtr->append(hashVal, docID);
                        
                        // iteration
                        word = strtok (NULL, " ,.-!()");
                }
                // delete [] cThisLine; [discarded method]
                this.lineReached++;
        }
}
