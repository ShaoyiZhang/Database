#include "Node.h"
#include "File.h"
#include "BPlusTree.h"
#include <iostream>

int main(int argc,char* argv[]) {
  string word = "happy";
  string word2 = "happy2";
  string word3 = "happy3";
  string word4 = "happy4";
  string word5 = "happy5";
  string word6 = "happy6";
  string word7 = "happy7";
  string word8 = "happy8";
  string word9 = "happy9";
  string word10 = "happy10";
  
  
  FilePointer fp = FilePointer( "happy", 10, 1, word );
  // Node * root = new Node( word, fp );
  //cout << root->GetOccupancy();
  BPlusTree bpt = BPlusTree( fp );
  cout << "construction passed\n";
  bpt.search( word );
  cout << "search1 completed\n";
  bpt.insert( word2, fp );
  cout << "ok2\n\n";
  bpt.insert( word3, fp );
  cout << "ok3\n\n";  
  bpt.insert( word4, fp );
  cout << "ok4\n\n";  
  bpt.insert( word5, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  bpt.insert( word6, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  bpt.insert( word7, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  bpt.insert( word8, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  bpt.insert( word9, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  bpt.insert( word10, fp );
  cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  
  
  
  // delete( root );
  // delete bpt;
  return 0;
}
