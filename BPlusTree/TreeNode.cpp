#include "TreeNode.h"

// constructor for root node
TreeNode::TreeNode( string word ) : isLeaf( false ) {
  // this->isLeaf = false;
  this->labels.push_back( word );
  // init leaf node
  TreeNode * newLeaf = new TreeNode::TreeNode( word, true );
  this->nextLevel.push_back( newLeaf );
}

// constructor for leaf node
// in
TreeNode::TreeNode( string word, File::FilePointer fp, bool isLeaf ) : isLeaf( isLeaf ) {
  this->labels.push_back( word );
  // this->isLeaf = true;
  this->filePointers.push_back( fp );
}