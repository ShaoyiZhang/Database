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

  // string word1 = "a";
  // string word2 = "b";
  // string word3 = "c";
  // string word4 = "d";
  // string word5 = "e";
  // string word6 = "f";
  // string word7 = "g";
  // string word8 = "h";
  // string word9 = "i";
  // string word10 = "j";
  // string word11 = "k";
  // string word12 = "l";
  // string word13 = "m";
  // string word14 = "n";
  // string word15 = "o";
  
  
  
  // FilePointer fp1 = FilePointer( "a", 10, 1, word1 );
  // FilePointer fp2 = FilePointer( "b", 10, 1, word2 );
  // FilePointer fp3 = FilePointer( "c", 10, 1, word3 );
  // FilePointer fp4 = FilePointer( "d", 10, 1, word4 );
  // FilePointer fp5 = FilePointer( "e", 10, 1, word5 );
  // FilePointer fp6 = FilePointer( "f", 10, 1, word6 );
  // FilePointer fp7 = FilePointer( "g", 10, 1, word7 );
  // FilePointer fp8 = FilePointer( "h", 10, 1, word8 );
  // FilePointer fp9 = FilePointer( "i", 10, 1, word9 );
  // FilePointer fp10 = FilePointer( "j", 10, 1, word10 );
  // FilePointer fp11 = FilePointer( "k", 10, 1, word11 );
  // FilePointer fp12 = FilePointer( "l", 10, 1, word12 );
  // FilePointer fp13 = FilePointer( "m", 10, 1, word13 );
  // FilePointer fp14 = FilePointer( "n", 10, 1, word14 );
  // FilePointer fp15 = FilePointer( "o", 10, 1, word15 );
  // // FilePointer fp = FilePointer( "happy", 10, 1, word );
  
  // // Node * root = new Node( word, fp );
  // //cout << root->GetOccupancy();
  // BPlusTree bpt = BPlusTree( fp1 );
  // bpt.levelOrder();
  // cout << "cur root child size: " << bpt.getRoot()->childSize() << endl;
  
  // cout << "construction passed\n";
  // bpt.search( word1 );
  // bpt.levelOrder();
  
  // cout << "======================\n";
  // bpt.insert( word2, fp2 );
  // bpt.levelOrder();
  // cout << "ok2\n\n";
  
  // // cout << "cur root child size: " << bpt.getRoot()->childSize() << endl;  
  // cout << "======================\n";
  // bpt.insert( word3, fp3 );
  // bpt.levelOrder(); 
  
  // // cout << "cur root child size: " << bpt.getRoot()->childSize() << endl;  
  // cout << "ok3\n\n";  

  // cout << "======================\n";
  
  // bpt.insert( word4, fp4 );
  // // cout << "cur root child size: " << bpt.getRoot()->childSize() << endl;  
  // cout << "ok4\n\n";

  // cout << "======================\n";

  // bpt.insert( word5, fp5 );
  // // // cout << "cur root child size: " << bpt.getRoot()->childSize() << endl;
  // cout << "ok5\n\n";
  // bpt.levelOrder(); 
  
  // bpt.insert( word6, fp6 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  // bpt.levelOrder(); 
  // cout << "ok6\n\n";
  
  // bpt.insert( word7, fp7 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  // bpt.levelOrder(); 
  
  // // cout << "ok7\n\n";
  
  // bpt.insert( word8, fp8 );
  // // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  // bpt.levelOrder();
  // cout << "ok8\n\n";
  
  // bpt.insert( word9, fp9 );
  // // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;  
  // bpt.levelOrder();  
  // cout << "ok9\n\n";
  
  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";
  
  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";
  
  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";

  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";

  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";

  // bpt.insert( word10, fp10 );
  // // cout << "cur root key size: " << bpt.getRoot()->size() << endl;
  // bpt.levelOrder();  
  // cout << "ok10\n\n";
  
  // // delete( root );
  // delete bpt;
  return 0;
}
