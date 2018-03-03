#ifndef _BTREEE_H_
#define _BTREEE_H_

#include <iostream>
using namespace std;

extern int M;
extern int L;



// BTree has a root node which is of type InternalNode
// The children ptrs of root might be LeafNode AND InternalNode
class BTree{
private:
  Node* root;
  int count;
public:
BTree():root(new Node(true)),count(0){};
  int GetCount(){ return count; };
  void Insert(string key,int value);
  Node* SearchHelper(string key, Node* current) const;
  Node* GetRoot(){ return root; };
  bool Search(string key) const;
  Node* InsertHelper(string key, Node* current);
  void PrintAll(){ PrintAll(root); };
  void PrintAll(Node* root);
  void PrintAllKeys(Node* root);
  void PrintBetween(string start, string end);
};

#endif