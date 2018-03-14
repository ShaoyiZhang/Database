#include "Node.h"
#include "File.h"
#include "BPlusTree.h"
#include <iostream>

int main(int argc,char* argv[]) {
  string word = "happy";
  FilePointer fp = FilePointer( "happy", 10, 1, word );
  // Node * root = new Node( word, fp );
  //cout << root->GetOccupancy();
  BPlusTree bpt = BPlusTree( fp );
  cout << "construction passed\n";
  bpt.Search( word );
  // delete( root );
  // delete bpt;
  return 0;
}
