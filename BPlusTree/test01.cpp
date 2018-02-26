#include "Node.h"
#include "File.h"

int main(int argc,char* argv[]) {
  string word = "happy";
  FilePointer fp = FilePointer( "yelp", 10, 1, word );
  Node * root = new Node( word, fp );
  return 0;
}