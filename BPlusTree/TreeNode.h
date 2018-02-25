#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include <iostream>
#include <vector>
#include "File.h"
using namespace std;

const int M = 5;
const int L = 3;

class TreeNode{
 private:
  // string* nameIndex;
  // TreeNode** nextNodes;
  // pair<string, int>** leaves;
  vector< string > labels;
  vector< TreeNode > nextLevel;
  vector< File::FilePointer > filePointers; // only useful in leaf nodes
  bool isLeaf;
  // int index;
 public:
  TreeNode();
  // constructer for root
  TreeNode( string word, File::FilePointer );  
  //constructor for a leaf
  TreeNode( string word, bool isLeaf );   
  // TreeNode( string word );

  //constructor for an internal node
  // TreeNode(TreeNode ** arrayOfNodes, int size);

  const bool IsLeaf() { return isLeaf; }
  void SetLeaf( bool value ){ isLeaf = value; }
  void InsertLeaf( string name, int index, int endPos );
  // string* getNameIndex() { return nameIndex; }
  // TreeNode** getNextNodes() { return nextNodes; }
  pair<string, int>** getLeaves() { return leaves; }
};

#endif