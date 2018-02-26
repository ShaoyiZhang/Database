#include "Node.h"
#include "File.h"
#include <iostream>

int main(int argc,char* argv[]) {
  string word = "happy";
  FilePointer fp = FilePointer( "yelp", 10, 1, word );
  Node * root = new Node( word, fp );
  //cout << root->GetOccupancy();

  delete( root );
  return 0;
}
