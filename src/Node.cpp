#include "Node.h"
// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
Node::Node() {
  cerr << "default constructor size will be 0\n";
  for ( int i = 0; i < M; i++ ) {
    keys[i] = nullptr;
  }
  for ( int i = 0; i < M+1; i++ ) {
    children[i] = nullptr;
  }
  for ( int i = 0; i < L; i++ ) {
    filePointers[i] = nullptr;
  } 
  nKeys = 0;
  nChild = 0;
}
// constructor for root node with fp
Node::Node( string word, FilePointer fp ) : isLeaf( false ), previous( nullptr ), 
                              next( nullptr ), parent( nullptr ) {
  cerr << "root cons, size 1\n";
  for ( int i = 0; i < M; i++ ) {
    keys[i] = nullptr;
  }
  for ( int i = 0; i < M+1; i++ ) {
    children[i] = nullptr;
  }
  for ( int i = 0; i < L; i++ ) {
    filePointers[i] = nullptr;
  }
  this->keys[0] = new string( word );
  nKeys = 1;
  // insert newLeaf to 2nd slot since < goes to left child and >= goes to right
  Node * newLeaf = new Node( word, fp, true, this );
  this->children[0] = nullptr;
  this->children[1] = newLeaf;
  nChild = 2;
}

// constructor for new empty node
Node::Node( bool isLeaf, 
            Node * parent ) : isLeaf( isLeaf ), previous( nullptr ),
                              next( nullptr ), parent( parent ) {
  for ( int i = 0; i < M; i++ ) {
    keys[i] = nullptr;
  }
  for ( int i = 0; i < M+1; i++ ) {
    children[i] = nullptr;
  }
  for ( int i = 0; i < L; i++ ) {
    filePointers[i] = nullptr;
  } 
  cerr << "new empty\n";
  // this->keys[0] = new string( fp.getWord() );
  // this->filePointers[0] = new FilePointer( fp ); // copy constructor
  nKeys = 0;
  nChild = 0; // leaf node 
}

// constructor for leaf node
Node::Node( string word, FilePointer fp, bool isLeaf, 
            Node * parent ) : isLeaf( isLeaf ), previous( nullptr ),
                              next( nullptr ), parent( parent ) {
  for ( int i = 0; i < M; i++ ) {
    keys[i] = nullptr;
  }
  for ( int i = 0; i < M+1; i++ ) {
    children[i] = nullptr;
  }
  for ( int i = 0; i < L; i++ ) {
    filePointers[i] = nullptr;
  } 
  cerr << "new leaf\n";
  this->keys[0] = new string( word );
  this->filePointers[0] = new FilePointer( fp ); // copy constructor
  nKeys = 1;
  nChild = 0; // leaf node 
}

// return the index of a given key in the keys array
// if name is NOT present in the array, return -1
int Node::indexOfKey(string key) {
  int index = 0;
  // cerr << this->size() << endl;
  for (int i = 0; i < this->size(); i++){
    // cerr << " index of key " << i << endl;
    if ( key >= *keys[i]) {
      index++;
    }
    // cerr << " index of key " << i << "pass" << endl;    
  }
  return index;
}

void Node::insertKey( string word ) { 
  int index = this->indexOfKey( word ); 
  cerr << "inserKey: size " << this->nKeys << " index " << index << endl;  
  if ( index == this->nKeys ) { // insert at the end
    cerr << "insert at end\n";
    keys[index] = new string( word );
    // filePointers[index] = new FilePointer( fp );
  } else { // insert in the middle
    cerr << "insert in middle\n";
    for ( int i = this->size(); i > index; i-- ) {
      keys[i] = keys[i-1];
      // also need to move pointers
      children[i+1] = children[i];
    }
    keys[index] = new string( word );
  }
  nKeys++;  
}

void Node::insertChild( Node * child ) {
  int index = this->indexOfChild( child->getKeyAt(0) ); 
  cerr << "insert Child: size " << this->nChild << " index " << index << endl;  
  nChild++;    
  if ( index == this->nChild - 1 ) { // insert at the end
    cerr << "insert at end\n";
    children[index] = child;
    // filePointers[index] = new FilePointer( fp );
    return;
  } 
  // insert in the middle
  cerr << "insert in middle\n";
  if ( child->getIsLeaf() ) {
    cerr << " child is leaf\n";
  } else {
    cerr << " child is internal\n";    
  }
  for ( int i = 0; i < child->size(); i++ ) {
    cerr << " " << child->getKeyAt(i) << " ";
  } 

  cerr << "\n===========\n" << " index " << index  
       << " nchild " << nChild << endl;  
  for ( int i = nChild-1; i > index; i-- ) {
    // keys[i] = keys[i-1];
    // also need to move pointers
    cerr << "===========\n" << i << " index " << index << endl;
    children[i-1] = children[i];
  }
  children[index] = child;


}

// in leaf node, nKeys = nFPs, nChild = 0
void Node::insertKeyValuePair( string word, FilePointer fp ) {
  int index = this->indexOfKey( word );
  cerr << "inserKeyValue: size " << this->size() << " index " << index << endl;  
  if ( index == this->nKeys ) { // insert at the end
    cerr << "insert at end\n";
    keys[index] = new string( word );
    filePointers[index] = new FilePointer( fp );
  } else { // insert in the middle
    cerr << "insert in middle\n";
    for ( int i = this->size(); i > index; i-- ) {
      keys[i] = keys[i-1];
      filePointers[i] = filePointers[i-1];
    }
    keys[index] = new string( word );
    filePointers[index] = new FilePointer( fp );
  }
  nKeys++;  
  // need to check final size in caller
}

// bool Node::isContain( FilePointer record ) {
//   // if ( std::binary_search ( children.cbegin(), 
//   //                           children.cend(), 
//   //                           record, 
//   //                           TComparator) ) {
//   for ( int i = 0; i < this->children.size(); i++ ) {
//     if ( *( this->filePointers[i] ) == record ) {
//       return true;
//     }
//   }
//   cerr << "not contain " << record.getWord() << endl;
//   return false;

// }

int Node::indexOfFilePointer( string word ) {
  cerr << "IndexOfFilePointer: key size is " << this->nKeys << "\n ";
  for ( int i = 0; i < nKeys; i++ ) {
    cerr << "index fp: " << i << " ";
    if ( *( keys[i] ) == word ) {
      cerr << "pass" << endl;
      return i;
    }
  }
  cerr << "not contain " << word << endl;
  return -1;
}

void Node::print() {
  if ( this->isLeaf == true ) {
    for (int i = 0; i < this->size(); i++) {
      cerr << "Key: "<< this->getKeyAt( i )
           << " Value: " << this->getFPAt( i )
           << endl;
    }
  }
}

ostream& operator <<( ostream& out, const FilePointer& fp ) {
  out << "fp: " << fp.getFileName() << " " << fp.getWord() << endl;
  return out;
}

// A function for InternalNode (Road map)
// return the index of the pointer which lead us to next level
// if pointer not already exist, return -1
int Node::indexOfChild( string key ) {
    int index = 0;
    while ( index < nKeys && key >= *( keys[index] ) ) {
        //cerr << "capacity"<<this->GetCapcity()<<endl;
        index++;
    }
    //cerr<<"index"<< index << endl;
    return index;
}

void Node::removeKeyValuePairAt( int index ) {
  // TO DO: free current pointer before shifting
  for ( int i = index; i < nKeys - 1; i++ ) {
    keys[i] = keys[i+1];
  }
  nKeys--;
}

void Node::removeChildAt( int index ) {
  // TO DO: free current pointer before shifting  
  for ( int i = index; i < nChild - 1; i++ ) {
    children[i] = children[i+1];
  }
  nChild--;
}

void Node::removeKeyAt( int index ) {
  for ( int i = index; i < nKeys - 1; i++ ) {
    keys[i] = keys[i+1];
  }
  nKeys--;
}