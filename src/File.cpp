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