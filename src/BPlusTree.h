#ifndef _BPLUSTREEE_H_
#define _BPLUSTREEE_H_

#include <iostream>
#include "Node.h"
#include <map>
// #include <utility> 
#include <math.h> // ceil
using namespace std;

extern const int M; // num of max pointers to next level
extern const int L; // num of max profiles

// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
typedef map< string, unsigned int > msu;
class BPlusTree{
private:
  Node * root;
  int count;
  unsigned int maxPage;
  msu dirPage;
  string filename;
public:
  // BTree():root(new Node(true)),count(0){};
  BPlusTree( string filename );
  BPlusTree( int maxPage );  
  BPlusTree( string filename, int maxPage );
  BPlusTree( string filename, int maxPage, msu & dirPage );

  BPlusTree( string word, FilePointer record, int maxPage );
  ~BPlusTree();
  int getCount(){ return count; };
  bool isRoot( Node * cur ) const { return cur == root; }
  
  // return pointer to leaf node
  void insert( string word, FilePointer record );
  Node * insert( string word, FilePointer record, Node * start );
  void insert( Node * parent, Node * child, string key );
  bool remove( string word );
  Node * insertHelper( string word, Node * start ); // find internal node candidate
    void insertEntry(string word);
  void splitNoneLeaf( Node * cur );
  // return leaf containing right half
  Node * splitLeaf( Node * cur, int childIndex );
  void splitRoot( Node * cur );
  void retainOrder( Node * left, Node * right, Node * cur );
  
  bool search( string word );
  // modify the pointer to the leaf and return the index of key in that leaf
  // int search( string word, Node * leaf );
  vector<int> getDocVec( string word );
  vector<int> searchMultiple( vector<string> wordList );

  Node * searchHelper( string word ); // find leaf node candidate
  Node * getRoot() { return root; };
  void printAll();
  void printAll( Node * root );
  void printAllKeys() { printAllKeys( this->root ); };
  void printAllKeys( Node * cur );
  void printBetween( string start, string end );

  void levelOrder( Node * cur );
  void dfs( Node* cur, vector<vector<string>> &res, int depth);
  // vector<string> Split(const std::string& subject);
  void loadDirPage( string filename );
  vector<string> split( const string& subject );
  void bulkLoad();
  
};

#endif