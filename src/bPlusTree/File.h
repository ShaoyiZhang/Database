#ifndef FILE_H_
#define FILE_H_

#include "string.h"
#include <string>
using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

/* A class for Record ID
  An instance of this class will include:
  1. index file name ( index directory name in our project )
  2. index page id
  3. offset in the index page
  4. In debugging phase, we will also store the keyword string in the object

  This class also contain some class methods to help retrieve actual records from
  the file given a target word. These method will take 
*/

typedef map< string, unsigned int > msu;

class FilePointer {
public:
  FilePointer();
  // FilePointer( string filename, int offset, int nDupKeys );
  // FilePointer( string filename, int offset, int nDupKeys );
  // Test only
  FilePointer( string filename, int offset, string word, int nDupKeys = 0 );
  // FilePointer( string filename, int offset, int nDupKeys, string word );
  string getFileName() { return this->filename; }
  string getFileName() const { return this->filename; }
  
  int getPageID();
  int getOffset();
  int getNDupKeys();
  string getWord() { return this->word; };
  string getWord() const { return this->word; };
  bool getIsBuffered() { return this->isBuffered; }

  bool operator == ( FilePointer const &other );
  vector<string> getDocList( msu & dirPage, const string& filename, unsigned int pageSize );
  void appendDocList( vector<string> newDocList );
  friend ostream& operator <<( ostream& out, const FilePointer& fp );
  // friend ostream& operator<<(ostream& out, const Vector2D& vec) // output
  bool fetchFromDisk( msu & dirPage, const string& filename, unsigned int pageSize );
private:
  string filename; // index file name a.k.a. directory name for the index files
  int pageID; // index page id
  int offset; // offset of the RID for the keyword

  /* a keyword might appear multiple times in different documents. Our database will 
  keep the RIDs of duplicated keywords in the same index page. Overflow pages will
  be created automatically and will be transparent to the B Plus Tree. */
  int nDupKeys;

  bool isBuffered;
  vector<string> docList;
  // NOTE: For debugging and test, we will add an extra filed: 
  // the keyword associated with the RIDs.
  // Remove in release to improve performance.
  string word;
};

/* 
  A wrapper class for file operations
  might be unnecessary
*/
// class FileOperation {

// };


#endif
