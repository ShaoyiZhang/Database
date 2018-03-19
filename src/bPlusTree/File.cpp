#include "File.h"

void splitStrToVec_whitespace(std::vector<std::string> &v, const string& str) {
    istringstream iss(str);
    std::copy(istream_iterator<string>(iss),
              istream_iterator<string>(),
              back_inserter(v));
}

string getLine(const string& filename, unsigned int startLine, unsigned int pageSize);

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

vector<string> FilePointer::getDocList( msu & dirPage, const string& filename, unsigned int pageSize ) {
  if ( this->isBuffered == true ) {
    // docList already in memory, return
    return this->docList;
  } else {
    // fetch from binary index file
    bool isFetchSuc = this->fetchFromDisk( dirPage, filename, pageSize );
    if ( isFetchSuc == true ) {
      // fetch success, docList is now in memory
      this->isBuffered = true;
      return this->docList;
    } else {
      // fetch fail, corrupted index file?
      // return empty vector
      cerr << "Fetch Fail!\n"; 
      return vector<string>();
    }
  }
}

// fetch from index file
bool FilePointer::fetchFromDisk( msu & dirPage, const string& filename, unsigned int pageSize ) {
  vector<string> curDocList;
  unsigned int lineNum = dirPage[this->getWord()];
  splitStrToVec_whitespace( curDocList, getLine( filename, lineNum, pageSize ) );
  curDocList.erase( curDocList.begin() );
  // append temp vector to docList
  docList.insert( docList.end(), curDocList.begin(), curDocList.end());
  string word = getWord();
  while ( word == getWord() ) {
    lineNum++;
    splitStrToVec_whitespace( curDocList, getLine( filename, lineNum, pageSize ) );    
    if ( curDocList.empty() == false ) {
      word = curDocList[0];
    } else {
      break;
    }
    curDocList.erase( curDocList.begin() );
  }

  return (docList.size() > 0);
}

void FilePointer::appendDocList( vector<string> newDocList ) {
  if ( isBuffered == true ) {
    this->docList.insert(end(docList), begin(newDocList), end(newDocList));
  } else {
    // insertDisk
    return;
  }
}

string getLine(const string& filename, unsigned int startLine, unsigned int pageSize) {
    unsigned int replacePos = 0; // line number

    // open file
    FILE * pFile;
    pFile = fopen ( filename.c_str() , "r" );

    // go to startLine and read the line
    long int offset = (startLine-1)*pageSize;
    fseek ( pFile , offset , SEEK_SET );
    char * cLine = new char[pageSize];
    fgets (cLine, pageSize, pFile);
    // cout << cLine << endl;

    // if thisLine is NOT for the word passed in, return 0 (not found)
    string thisLine(cLine);
    return thisLine;
}