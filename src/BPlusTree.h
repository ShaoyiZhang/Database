#ifndef _BPLUSTREEE_H_
#define _BPLUSTREEE_H_

#include <iostream>
#include "Node.h"
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
class BPlusTree{
private:
  Node * root;
  int count;
public:
  // BTree():root(new Node(true)),count(0){};
  BPlusTree();
  BPlusTree( string word, FilePointer record );
  ~BPlusTree();
  int getCount(){ return count; };
  bool isRoot( Node * cur ) const { return cur == root; }

  void insert( string word, FilePointer record );
  void insert( Node * parent, Node * child );
  bool remove( string word );
  Node * insertHelper( string word ); // find internal node candidate
  void splitNoneLeaf( Node * cur );
  void splitLeaf( Node * cur );
  void splitRoot( Node * cur );

  bool search( string word );  
  Node * searchHelper( string word ); // find leaf node candidate
  
  Node * getRoot() { return root; };
  void printAll(){ printAll(root); };
  void printAll( Node * root );
  void printAllKeys() { printAllKeys( this->root ); };
  void printAllKeys( Node * cur );
  void printBetween( FilePointer start, FilePointer end );

  void levelOrder( Node * );
  void bfs( Node* cur, vector<vector<string>> &res, int depth);
};

#endif