#include "Node.h"
#include "File.h"
#include "BPlusTree.h"
#include <iostream>
#include <fstream>

int main(int argc,char* argv[]) {
  // vector<string> words;
  // vector<FilePointer> fps;
  string word1 = "AKey";
  FilePointer fp1 = FilePointer( "A", 10, 1, word1 );
  vector<bool> isTestEnabled;
  isTestEnabled.push_back(false);
  isTestEnabled.push_back(false);
  isTestEnabled.push_back(true);
  int count = 0;
  // BPlusTree bpt = BPlusTree( fp1 );
  BPlusTree bpt = BPlusTree( 200 );
  cerr << "construction passed\n";
  // bpt.search( word1 );
  bpt.levelOrder( bpt.getRoot() );
  // string keyTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzA";
  string keyTable = "SQRT6UVWX5YZaFG9HIJKL0MNOP8ghi3jkcdefABCDE1qrlmn4o2pbstuvw7xyz";

  if ( isTestEnabled[count] == true ) {
    cerr << "Test insertion in ascending order...";
    for ( int i = 0; i < keyTable.size(); i++ ) {
      string word = keyTable.substr(i,1) + "key";
      FilePointer fp = FilePointer( keyTable.substr(i,1), 10, 1, keyTable.substr(i,1) );
      cerr << "======================\n";
      bpt.insert( word, fp );
      bpt.levelOrder( bpt.getRoot() );
      bpt.printAll();
      assert( bpt.search( word ) == true );
      cerr << "ok" << i << endl << endl;
    }
    bpt.printAll();        
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
      cerr << "======================\n";
      bpt.insert( word, fp );
      bpt.levelOrder( bpt.getRoot() );
      cerr << "ok" << i << endl << endl;
    }
    bpt.printAll();    
  }
  count++;

// std::ifstream input(filepath);

  if ( isTestEnabled[count] == true ) {
    BPlusTree bpt2 = BPlusTree(200);
    vector<string> wordList;
    string line;
    const char * filename = "../data/google-10000-english-no-swears.txt";
    ifstream input( filename );
    while (getline(input, line)){
      cerr << "~~\n";
      wordList.push_back( line );
    }
    // sort(wordList.begin(), wordList.end() );
    cerr << wordList.size();
    cerr << "Test insertion in long word list...";
    for ( int i = 0; i < wordList.size(); i++ ) {
      // string word = keyTable.substr(i,1) + "key";
      string word = wordList[i] + "Key";
      FilePointer fp = FilePointer( wordList[i], 10, 1, wordList[i] );
      cerr << "======================\n";
      bpt2.insert( word, fp );
      bpt2.levelOrder( bpt2.getRoot() );
      cerr << "searching " << word << endl;
      assert( bpt2.search( word ) == true );
      cerr << "ok" << i << endl << endl;
    }
    bpt2.printAll();
  }
  count++;

  return 0;
}
