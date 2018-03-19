#include "File.h"
FilePointer::FilePointer() {
  filename = nullptr;
  pageID = -1;
  offset = -1;
  nDupKeys = 0;
}
// FilePointer::FilePointer( string filename, int offset, int nDupKeys ) {
//   this->filename = filename;
//   this->offset = offset;
// }

// FilePointer::FilePointer( string filename, int offset, int nDupKeys ) : FilePointer ( filename.c_str(), offset, nDupKeys ){
//   //FilePointer::FilePointer( filename.c_str(), offset, nDupKeys );
// }

// TEST only 
FilePointer::FilePointer( string filename, int offset, string word, int nDupKeys ) {
  this->filename = filename;
  this->offset = offset;
  this->word = word;
  this->nDupKeys = nDupKeys;
}

// FilePointer::FilePointer( string filename, int offset, string word, int nDupKeys ) : FilePointer( filename.c_str(), offset, nDupKeys, word ) {
// }

bool FilePointer::operator == ( FilePointer const &other ) {
  return word == other.word;
}

// int getPageID() { };
// long int getOffset();
// int getNDupKeys();

vector<int> FilePointer::getDocList() {
  if ( this->isBuffered == true ) {
    // docList already in memory, return
    return this->docList;
  } else {
    // fetch from binary index file
    bool isFetchSuc = this->fetchFromDisk();
    if ( isFetchSuc == true ) {
      // fetch success, docList is now in memory
      this->isBuffered = true;
      return this->docList;
    } else {
      // fetch fail, corrupted index file?
      // return empty vector
      cerr << "Fetch Fail!\n"; 
      return vector<int>();
    }
  }
}

// fetch from index file
bool FilePointer::fetchFromDisk() {
  return true;
}