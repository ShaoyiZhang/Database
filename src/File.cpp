#include "File.h"
// FilePointer::FilePointer() {
//   filename = nullptr;
//   pageID = -1;
//   offset = -1;

// }
FilePointer::FilePointer( const char * filename, long int offset, int nDupKeys ) {
  this->filename = strdup( filename );
  this->offset = offset;
}

FilePointer::FilePointer( string filename, long int offset, int nDupKeys ) : FilePointer ( filename.c_str(), offset, nDupKeys ){
  //FilePointer::FilePointer( filename.c_str(), offset, nDupKeys );
}

// TEST only 
FilePointer::FilePointer( const char * filename, long int offset, int nDupKeys, string word ) {
  this->filename = strdup( filename );
  this->offset = offset;
  this->word = word;
}

FilePointer::FilePointer( string filename, long int offset, int nDupKeys, string word ) : FilePointer( filename.c_str(), offset, nDupKeys, word ) {
}

bool FilePointer::operator == ( FilePointer const &other ) {
  return word == other.word;
}

// int getPageID() { };
// long int getOffset();
// int getNDupKeys();

vector<long> FilePointer::getDocList() {
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
      return vector<long>();
    }
  }
}

bool FilePointer::fetchFromDisk() {
  return true;
}