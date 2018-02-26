#include "File.h"

FilePointer::FilePointer( const char * filename, long int offset, int nDupKeys ) {
  this->filename = strdup( filename );
  this->offset = offset;
}

FilePointer::FilePointer( string filename, long int offset, int nDupKeys ) {
  FilePointer::FilePointer( filename.c_str(), offset, nDupKeys );
}

// TEST only 
FilePointer::FilePointer( const char * filename, long int offset, int nDupKeys, string word ) {
  this->filename = strdup( filename );
  this->offset = offset;
  this->word = word;
}

FilePointer::FilePointer( string filename, long int offset, int nDupKeys, string word ) {
  FilePointer::FilePointer( filename.c_str(), offset, nDupKeys, word );
}