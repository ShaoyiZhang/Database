#include "Node.h"

// constructor for root node
Node::Node( string word, FilePointer::FilePointer ) : isLeaf( false ), previous( nullptr ),
                                                      occupancy( 1 ), capacity( M ) {
  this->keys.push_back( word );
  Node * newLeaf = new Node::Node( word, true );
  this->nextLevel.push_back( newLeaf );
}

// // constructor for leaf node
// // in
// Node::Node( string word, File::FilePointer fp, bool isLeaf ) : isLeaf( isLeaf ) {
//   this->keys.push_back( word );
//   // this->isLeaf = true;
//   this->filePointers.push_back( fp );
// }

// Node::~Node()