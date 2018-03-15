#include "Node.h"
#include "File.h"
#include "BPlusTree.h"
#include <iostream>

int main(int argc,char* argv[]) {
  // vector<string> words;
  // vector<FilePointer> fps;
  string word1 = "a";
  FilePointer fp1 = FilePointer( "a", 10, 1, word1 );

  BPlusTree bpt = BPlusTree( fp1 );
  cout << "construction passed\n";
  bpt.search( word1 );
  bpt.levelOrder( bpt.getRoot() );
  string keyTable = "abcdefghijklmno";
  for ( int i = 1; i < 11; i++ ) {
    string word = keyTable.substr(i,1);
    FilePointer fp = FilePointer( keyTable.substr(i,1), 10, 1, keyTable.substr(i,1) );
    cout << "======================\n";
    bpt.insert( word, fp );
    bpt.levelOrder( bpt.getRoot() );
    cerr << "ok" << i << endl << endl;
  }

  return 0;
}
