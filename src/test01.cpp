#include "Node.h"
#include "File.h"
#include "BPlusTree.h"
#include <iostream>

int main(int argc,char* argv[]) {
  // vector<string> words;
  // vector<FilePointer> fps;
  string word1 = "AKey";
  FilePointer fp1 = FilePointer( "A", 10, 1, word1 );
  vector<bool> isTestEnabled;
  isTestEnabled.push_back(true);
  isTestEnabled.push_back(false);
  int count = 0;
  // BPlusTree bpt = BPlusTree( fp1 );
  BPlusTree bpt = BPlusTree( );
  cout << "construction passed\n";
  // bpt.search( word1 );
  bpt.levelOrder( bpt.getRoot() );
  string keyTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  if ( isTestEnabled[count] == true ) {
    cerr << "Test insertion in ascending order...";
    for ( int i = 1; i < 40; i++ ) {
      string word = keyTable.substr(i,1) + "key";
      FilePointer fp = FilePointer( keyTable.substr(i,1), 10, 1, keyTable.substr(i,1) );
      cout << "======================\n";
      bpt.insert( word, fp );
      bpt.levelOrder( bpt.getRoot() );
      bpt.search( word );
      cerr << "ok" << i << endl << endl;
    }
  }
  count++;  
  if ( isTestEnabled[count] == true ) {
    cerr << "-----------------------------\nTest insertion in descending order...";    
    // reverse( keyTable.begin(),keyTable.end() );
    keyTable = "987654321";
    cerr << keyTable << endl;
    for ( int i = 1; i < 8; i++ ) {
      string word = keyTable.substr(i,1) + "key";
      FilePointer fp = FilePointer( keyTable.substr(i,1), 10, 1, keyTable.substr(i,1) );
      cout << "======================\n";
      bpt.insert( word, fp );
      bpt.levelOrder( bpt.getRoot() );
      cerr << "ok" << i << endl << endl;
    }
  }
  count++;
  return 0;
}
