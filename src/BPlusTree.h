#ifndef _BPLUSTREEE_H_
#define _BPLUSTREEE_H_

#include <iostream>
#include "Node.h"
#include <utility>
using namespace std;

extern const int M;
extern const int L;

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
  BPlusTree( FilePointer record );
  ~BPlusTree();
  int GetCount(){ return count; };
  bool IsRoot( Node * cur ) const { return cur == root; }
  void Insert( FilePointer record );
  Node * SearchHelper( string word );
  pair< Node *, int > Search( string word );  
  Node * GetRoot() const { return root; };
  Node * InsertHelper( FilePointer record, Node * cur );
  void PrintAll(){ PrintAll(root); };
  void PrintAll( Node * root );
  void PrintAllKeys( Node * root );
  void PrintBetween( FilePointer start, FilePointer end );
};

#endif