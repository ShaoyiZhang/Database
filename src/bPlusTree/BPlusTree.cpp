#include "BPlusTree.h"

// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
BPlusTree::BPlusTree( string filename ){
  this->root = nullptr;
  count = 0;
  maxPage = 200;
  this->filename = filename;  
  loadDirPage( filename );
}

BPlusTree::BPlusTree( int maxPage ){
  this->root = nullptr;
  this->count = 0;
  this->maxPage = maxPage;
  // this->filename = filename;  
  // loadDirPage( filename );
}

BPlusTree::BPlusTree( string filename, int maxPage ){
  this->root = nullptr;
  this->count = 0;
  this->maxPage = maxPage;
  this->filename = filename;
  this->dirFilename = "haha"; 
  loadDirPage( this->dirFilename );
}

BPlusTree::BPlusTree( string filename, string dirFilename, int maxPage ){
  this->root = nullptr;
  this->count = 0;
  this->maxPage = maxPage;
  this->filename = filename;
  this->dirFilename = dirFilename; 
  loadDirPage( this->dirFilename );
}

BPlusTree::BPlusTree( string filename, int maxPage, msu & dirPage ){
  this->root = nullptr;
  this->count = 0;
  this->maxPage = maxPage;
  this->filename = filename;  
  // loadDirPage( filename );
  this->dirPage = dirPage;
}

// root
BPlusTree::BPlusTree ( string word, FilePointer record, int maxPage ) {
  Node * root = new Node( word, record );
  this->root = root;
  this->count = 1;
  this->maxPage = maxPage;
}

BPlusTree::~BPlusTree(){
  return;
}

void BPlusTree::insert( string word, FilePointer record ) {
  this->insert( word, record, root );
}

// Return a pointer to a leaf node that might contain the word
Node * BPlusTree::searchHelper( string word, Node * start ) {
  cerr << "inside search helper\n";
  if ( this->root == nullptr ) {
    // all elements in the tree has been deleted
    cerr << "empty tree\n";
    return root;//make_pair( nullptr, -1 );
  }
  Node * cur = start;
  while ( cur != nullptr && cur->getIsLeaf() == false ) {
    // cerr << "try move down\n";
    // Node ** childrenPtr = cur->getChildren();
    // cerr << "address of childrenPtr: " << childrenPtr << endl;
    int index = cur->indexOfChild( word ) ;
    cerr << "index of child: " << index << " childsize: " << cur->childSize() <<endl;
    if ( index == cur->childSize() ) {
      // we scaned all children, but the deseried leaf node is missing
      // we will return a nullptr
      cerr << "child pointer does NOT exist\n";
    }
    // retrieve the leaf node pointer and return to caller
    cur = cur->getChildAt(index); 
    // cerr <<"alive!\n"; 
  }
    // cerr <<" still alive!\n"; 
  
  return cur;
}

// return the leaf node and the index of the filepointer
bool BPlusTree::search( string word ) {
  Node * cur = searchHelper( word, this->root );
  cerr << " search size " << cur->size() << endl;
  
  int index = cur->indexOfFilePointer( word );
  // cerr << index << "\n";
  // cerr << "??????\n";
  if ( index == -1 ) {
    cerr << "not found";
    return false;
  } else {
    // found word
    cerr << "found word \"" << word << "\" at " << cur << ", " << index << endl;
    return true;
  }
}

// helper method
// insert a newly splitted node(child) to its parent(this)
void BPlusTree::insert( Node * parent, Node * child, string key ) {
  cerr << "insert (different signature)\n";
  this->levelOrder( child );
  this->levelOrder( root ); 
  parent->insertChild( child, key );

  cerr << "before checking post-internal-insertion:\n";
  cerr << "keys: ";
  this->levelOrder( root );
  for ( int i = 0; i < parent->size(); i++ ) {
    cerr << parent->getKeyAt(i) << " ";
  }
  cerr << "\n";
  // this->levelOrder( root ); 
  
  // if the none leaf node is FULL
  // need to split
  cerr << " parent child size before invoking splitRoot/non leaf "
       << parent->childSize() << " keySize: " << parent->size() << "\n";
  if ( parent->childSize() == M + 1 ){
    // levelOrder(root);
    cerr << "parent ALSO need to split\n";
    if ( parent == root ) {
      splitRoot( parent );
    } else {
      splitNoneLeaf( parent );
    }
  }
  // return NULL;
}

void BPlusTree::insertEntry( string word, int docNum ) {
  FilePointer fp = FilePointer();
  this->insert( word, fp, root );
}

void BPlusTree::splitRoot( Node * cur ) {
  cerr << "split root!\n";
  this->levelOrder( this->root );
  // create a new root
  Node * newRoot = new Node();
  newRoot->setIsLeaf( false );
  newRoot->setChildAt( 0, cur ); // insert current root to new root
  newRoot->incrChildSize();
  newRoot->setParent( nullptr );
  cur->setParent( newRoot );
  // this->levelOrder( newRoot );
  this->root = newRoot;  
  splitNoneLeaf( cur );
  // create a new internal node to hold second half of current root
}

// move middle key to parent, split current node, insert to parent
void BPlusTree::splitNoneLeaf( Node * cur ) {
  cerr << "split internal!\n";
  Node * newInternal = new Node( false, cur->getParent() );
  newInternal->setChildAt(0, nullptr);
  newInternal->incrChildSize();
  // cerr << "newInternal childsize " << newInternal->childSize() << "\n";

  cerr << "internal node key size: " << cur->size() << "\n";
  assert( cur->childSize() == M + 1 );
  int leftBound = ceil( static_cast<double>(M)/2 );
  int middle = M / 2; // floor
  cerr << "split internal left bound " << leftBound << " middle " << middle << endl;
  // move the child right to middle key to the new Internal node at index 0
  newInternal->setChildAt( 0, cur->getChildAt( leftBound ) );
  // move middle key to parent, child pointers in parent need to be shifed
  // shifting implemented in insertKey()
  // cur->getParent()->insertKey( cur->getKeyAt( middle ) );
  cerr<< "check parent keys:\n";
  for ( int i = 0; i < cur->getParent()->size(); i++ ) {
    cerr << cur->getParent()->getKeyAt(i) << " ";
  }
  cerr << endl;
  
  for ( int i = leftBound; i < M; i++ ) {
    // move latterHalf(index 3,4 ) to new internal
    cerr << " new key idx: " << i - leftBound << " new child idx: " << i - leftBound + 1
         << " old key idx: " << i << " old child idx: " << i + 1 << " key: " << cur->getKeyAt( i )<<"\n";
    newInternal->setChildAt( i - leftBound + 1, cur->getChildAt( i + 1 ) );
    newInternal->setKeyAt( i - leftBound, cur->getKeyAt( i ) );
    newInternal->incrKeySize();
    newInternal->incrChildSize();
    // cerr << "newInternal childsize " << newInternal->childSize() << "\n";
    cur->decrKeySize();
    cur->decrChildSize();
  }
  // delete middle key from current node
  cur->decrKeySize();  
  cur->decrChildSize(); // this is a late decrement for move child to new interal node at index 0
  assert( newInternal->childSize() == leftBound );

  // set the second half of nodes point to newInternal (change parent pointer)
  for ( int i = 0; i < newInternal->childSize(); i++ ) {
    Node * child = newInternal->getChildAt(i);
    if ( child != nullptr ) {
      child->setParent( newInternal );
    }
  }
  this->levelOrder( root );
  this->levelOrder( newInternal );
  cerr << "split internal move phase pass\n";
  cerr << "try insert splitted internal to parent\n";
  // cerr << "new root: " << cur->getParent() << " " << newInternal->getParent()->size() << " " 
  // << " key " << newInternal->getParent()->getKeyAt(0) << endl;
  // cerr << " childSize " << newInternal->getParent()->childSize() << endl;
  cerr << "cur child size: " << cur->childSize() << " key size: " << cur->size() << endl;
  cerr << "new internal child size: " << newInternal->childSize() << " key size: " << newInternal->size() << endl;  
  Node * temp = newInternal;
  while ( temp->getIsLeaf() == false ) {
    if ( temp->getChildAt(0) != nullptr ) {
      temp = temp->getChildAt(0);
    } else {
      cerr << "byebye!\n";
      break;
    }
  }
  string key = temp->getKeyAt(0);
  insert( cur->getParent(), newInternal, key );
}

Node * BPlusTree::splitLeaf( Node * cur, int childIndex ) {
  cerr << "split leaf !\n";
  Node * newLeaf = new Node(true, cur );
  assert( cur->size() == L + 1 );
  int leftBound = ceil(static_cast<double>(L)/2);
  cerr << "split leaf left bound " << leftBound << endl;
  for (int i = leftBound; i <= L; i++){
    // copy latterHalf(index 2,3) to new leaf
    newLeaf->insertKeyValuePair( cur->getKeyAt( i ), *(cur->getFPAt( i ) ) );
    // remove from original node
    cur->decrKeySize();
  }
  cerr << "split leaf move phase pass\n";
  this->levelOrder( this->root );
  
  cerr << "!!!!!!!!!!\n";
  for ( int j = 0; j < cur->getParent()->childSize(); j++ ) {
    if ( cur->getParent()->getChildAt(j) != nullptr ) {
      cerr << cur->getParent()->getChildAt(j)->getFPAt(0)->getWord() << " ";
    }
  }
  cerr << endl;

  cerr << "split leaf linked list reorder pass\n";
  // insert new leaf to parent (which must be none-leaf)
  cerr << "try insert splitted leaf to parent\n";

  string key = newLeaf->getKeyAt(0);
  // cur->getParent()->setChildAt( 0, newLeaf );
  // cerr << "insert LEFT !!!!!!!!!\n";
  this->levelOrder( root );
  // retain the linked list structure of leaf nodes to support range query
  if ( cur->getNext() != nullptr ) { //&&this->next->keys[0]!="")
    cur->getNext()->setPrevious( newLeaf );
  }
  newLeaf->setNext( cur->getNext() );
  newLeaf->setParent( cur->getParent() );
  newLeaf->setPrevious( cur );
  cur->setNext( newLeaf );
  // retainOrder( cur, newLeaf, cur );
  insert( cur->getParent(), newLeaf, key );
  return newLeaf;
}

// Return a pointer to a internal node that might contain the desired leaf node
Node * BPlusTree::insertHelper( string word, Node * start ) {
  cerr << "inside insert helper\n";
  if ( this->root == nullptr ) {
    // all elements in the tree has been deleted
    cerr << "empty tree\n";
    return nullptr;//make_pair( nullptr, -1 );
  }
  Node * cur = this->root;
  assert( cur->childSize() > 1 );
  bool isLeaf;

  isLeaf = false;
  cerr << "printing root\n";
  this->levelOrder( root );
  while ( isLeaf == false ) {
    cerr << "try move down\n";
    // Node ** childrenPtr = cur->getChildren();
    // cerr << "address of childrenPtr: " << childrenPtr << endl;
    int index = cur->indexOfChild( word );
    cerr << "index of child: " << index << " childsize: " << cur->childSize() <<endl;
    // if ( index == cur->childSize() ) {
    //   // we scaned all children, but the deseried leaf node is missing
    //   // we will return a nullptr
    //   cerr << "child pointer does NOT exist\n";

    // retrieve the leaf node pointer and return to caller
    cerr << "helo\n";
    if ( cur->getChildAt(index) != nullptr && 
         cur->getChildAt(index)->getIsLeaf() == false ) {
        cur = cur->getChildAt(index);           
    } else {
      cerr << "move down complete\n";      
      return cur;
    }
  }
  return cur;
}

Node * BPlusTree::insert( string word, FilePointer & record, Node * start ) {
  cerr << "inserting \"" << word << "\"\n";
  cerr << "tree before insert:\n";
  this->levelOrder( this->root );
  // TO DO: Tree empty
  if ( root == nullptr ) {
    cerr << "Empty tree\n";
    this->root = new Node( word, record );
    return root->getChildAt(1);
  }
  // case none-empty tree
  // find leaf node to insert record, potentially split nodes recursively
  // candidate is a leaf node
  
  Node * deepestInternal = insertHelper( word, start ); // deepest internal node
  // if word not already in the tree, insert normally
  cerr << "HERE!!\n";
  Node * leaf = searchHelper( word, deepestInternal );
  // null could mean inserting to left most or right most
  // OR righ
  if ( leaf != nullptr ) {
    cerr << leaf->indexOfKey( word ) << endl;
  }
  if ( leaf == nullptr || ( leaf != nullptr && leaf->isContain( word ) == false ) ) {
    cerr << "insert new\n";
    return insertNew( word, record, deepestInternal );
  } else {
    cerr << "insert existing\n";
    return insertExisting( word, record, leaf );
  }
}

// the key is already in the tree/index file
// update the tree in memory and modify the index file on disk
Node * BPlusTree::insertExisting( string word, FilePointer & record, Node * leaf ) {
  int index = leaf->indexOfFilePointer( word );
  leaf->getFPAt( index )->appendDocList( record.getDocList() );
  return leaf;
}

// candidate = deepest internal node
Node * BPlusTree::insertNew( string word, FilePointer & record, Node * candidate ) {
  // cerr << "tree after insert helper:\n";
  // this->levelOrder( this->root );
  this->levelOrder( candidate );
  cerr << "insert continue after insert helper return\n";
  assert( candidate->getIsLeaf() == false );
  int childIndex = candidate->indexOfChild( word );
  cerr << "deepest internal node child index: " << childIndex << " childSize: " << candidate->childSize() << "\n";  
  Node * cur = candidate->getChildAt(childIndex);
  if ( childIndex == candidate->childSize() || 
      cur == nullptr ) {
    // we scaned all children, but the deseried leaf node is missing
    cerr << "child pointer does NOT exist\n";
  
    // assert( candidate != nullptr && candidate->getIsLeaf() == true );

    // create new leaf and insert 
    Node * newLeaf = new Node( word, record, true, candidate );
    if ( childIndex == 0 ) {
      Node * next = candidate->getChildAt(1);
      newLeaf->setNext(next);
    } 

    candidate->setChildAt( childIndex, newLeaf );
    return newLeaf;
  }

  // set candidate to be leaf node
  candidate = candidate->getChildAt( childIndex );    

  // at leaf node 
  int index = candidate->indexOfKey( word );
  cerr << "insert index in leaf: " << index << endl;
  cerr << "before insert key value\n";

  if ( candidate->size() == 0 || candidate->size() == index ) {
    // just use push_back
    cerr << "append\n";
    candidate->insertKeyValuePair( word, record );
  } else {
    // find the right location to insert
    candidate->insertKeyValuePair( word, record );
    cerr << "!!! size " << candidate->size() << endl;
    for ( int i = 0; i < candidate->size(); i++ ) {
      cerr << candidate->getKeyAt(i) << " ";
    }
    cerr << endl;
  }

  cerr << "tree after insert before split:\n";
  this->levelOrder( this->root );
  cerr << "key vale pair inserted at leaf node(candidate)\n";
  Node * rightLeaf = candidate;
  // check leaf node size to see if we need to split leaf
  if ( candidate->size() == L + 1 ) {
    // need to split leaf
    rightLeaf = splitLeaf( candidate, childIndex );
  }
  cerr << "after insertion: \n";
  this->levelOrder( this->root );
  return rightLeaf;
}

void BPlusTree::levelOrder( Node * cur ) {
  cout << "Current tree:\n";
  if ( cur == nullptr ) {
    cout << "Tree is empty\n";
    return;
  }
  vector<vector<string>> res;
  dfs( cur, res, 0 );
  for ( int i = 0; i < res.size(); i++ ) {
    for ( int j = 0; j < res[i].size(); j++ ) {
      cout << res[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  // return res;
}

void BPlusTree::dfs( Node* cur, vector<vector<string>> &res, int depth) {
  if ( root != NULL ) { 
    if ( depth == res.size() ) {
      // new level
      vector<string> oneLevel;
      for ( int i = 0; i < cur->size(); i++ ) {
        if ( cur->getIsLeaf() == true ) {
          oneLevel.push_back( cur->getFPAt(i)->getFileName() );                  
        } else {
          // if ( cur->getKeyAt(i) )
          oneLevel.push_back( cur->getKeyAt(i) );        
        }
      }
      oneLevel.push_back("#");
      res.push_back(oneLevel);
      // cerr << "new depth " << depth << " val " << root->val << endl;
    } else {
      for ( int i = 0; i < cur->size(); i++ ) {
        if ( cur->getIsLeaf() == true ) {
          res[depth].push_back( cur->getFPAt(i)->getFileName() );        
        } else {
          res[depth].push_back( cur->getKeyAt(i) );        
        }
      }
      res[depth].push_back("#");
        // cerr << "depth " << depth << " val " << root->val << endl;
    }
    // res[depth].push_back("|");
    // traverse all chilren
    if ( cur->getIsLeaf() == false ) {
      for ( int i = 0; i < cur->childSize(); i++ ) {
        if ( cur->getChildAt(i) != nullptr ) {
          dfs( cur->getChildAt(i), res, depth + 1 );
        } else {
          vector<string> newLevel;
          newLevel.push_back("null #");
          res.push_back(newLevel);
        }
      }
    }
  }
}

void BPlusTree::printAll() {
  cout << "printing all keys\n"; 
  Node * cur = root;
  int count = 0;
  while ( cur->getIsLeaf() == false ) {
    if ( cur->getChildAt(0) != nullptr ) {
      cur = cur->getChildAt(0);
    } else {
      cerr << "not left most\n";
      cur = cur->getChildAt(1);
    }
  }
  while ( cur != nullptr ) {
    cur->print();
    cur = cur->getNext();
  }
  cout << endl;
}

void BPlusTree::loadDirPage( string filename ) {
  ifstream input( filename );
  string line;
  // map< string, unsigned int > dirPage;
  while ( getline( input, line )) {
    vector<string> pageInfo = split( line );
    // word lineNum
    dirPage[ pageInfo[0] ] = stoi( pageInfo[1] );
  }
}

vector<string> BPlusTree::split(const std::string& subject) {
    stringstream ss(subject);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    copy(vstrings.begin(), vstrings.end(), vstrings.begin());
    return vstrings;
}



void BPlusTree::bulkLoad() {
  // right most leaf, can be used to get right most deepest internal node
  // this->root = new Node();
  
  // insert first word to b+ tree and obtain a pointer to right most leaf
  // this->insert( it->first, FilePointer( it->first, it->second, it->first, 0 ) );
  Node * right = root;//root->getChildAt(1);
  // it++;
  for ( auto it = dirPage.begin(); it != dirPage.end(); ++it ) {
    // get the parent( internal node ) of right most leaf
    FilePointer record = FilePointer( it->first, it->second, it->first, 0 );
    right = this->insert( it->first, 
                          record,
                          right 
                        )->getParent();    
  }
}

// keyword start and end must be inside the tree
void BPlusTree::printBetween( string start, string end ) {
  Node * startNode =  searchHelper( start, this->root );
  Node * leaf = startNode->getChildAt( startNode->indexOfChild( start) );
  while ( leaf != nullptr ) {
    for ( int i = 0; i < leaf->size(); i++ ) {
      cout << leaf->getKeyAt(i) << " ";
    }
    leaf = leaf->getNext();
  }
}

vector<int> BPlusTree::getDocVec( string word ) {
  Node * leaf = searchHelper( word, this->root );
  if ( leaf != nullptr ) {
    int index = leaf->indexOfKey( word );    
    return leaf->getFPAt( index )->getDocList();
  } else {
    return vector<int> ();
  }
}

vector<int> BPlusTree::searchMultiple( vector<string> wordList ) {
  if ( wordList.size() == 0 ) {
    return vector<int>();
  }
  // sort words to maximize buffer utilization
  sort( wordList.begin(), wordList.end() );
  // wordList[0];
  Node * leaf;
  vector<int> v1 = this->getDocVec( wordList[0] );
  vector<int> intersect = v1;  
  vector<int> v2;
  for ( int i = 1; i < wordList.size(); i++ ) {
    v2 = this->getDocVec( wordList[i] );
    // sort( v2.begin(), v2.end() );
    set_intersection( v1.begin(), v1.end(), v2.begin(), v2.end(),
                      back_inserter( intersect ) );
    v1 = intersect;
    // v2.clear();
  }
  return intersect;
}
/*
bool BPlusTree::remove( string word ) {
  // use insert helper to find the parent of leaf node
  Node * parent = insertHelper( word );
  int index = parent->indexOfChild( word );
  Node * leaf = parent->getChildAt( index );
  if ( leaf == nullptr ) {
    // this word does NOT exist
    return false;
  }
  // delete key-value pair from leaf
  leaf->removeKeyValuePairAt( indexOfKey( word ) ); // size decrement inside this function
  Node * left = leaf->getPrev();
  Node * right = leaf->getNext();

  if ( leaf->size() > L ) {
    // the leaf still have enough key-value pair after deletion
    // update key in parent(internal node) and we are done
    parent->setKeyAt( parent->indexOfKey( leaf->getKeyAt(0) ) );
  } else if ( left != nullptr ) {
      if ( left->size() > L ) {
        // borrow from left if left leaf contain enough key-value pair    
        // copy entry to current node
        leaf->insertKeyValuePair( left->getKeyAt( left->size() - 1 ), 
                                  left->getFPAt( left->size() - 1 ) );
        left->decrKeySize(); // delete entry from left node
        parent->setKeyAt( parent->indexOfKey( leaf->getKeyAt(0) ) );
      } else { 
        merge( leaf, left, true )
      }    
  } else if ( right != nullptr ) { // left == nullptr, first leaf node in last level
      if ( right->size() > L ) {
        // borrow from right
        leaf->insertKeyValuePair( right->getKeyAt( 0 ), 
                                  right->getFPAt( 0 ) );
        right->decrKeySize(); // delete entry from left node
        parent->setKeyAt( parent->indexOfKey( right->getKeyAt(0) ) );
      } else {
        // merge with right
        merge();    
      }
  }

  //   cerr << "case NOT covered in deletion\n";

  return true;
}

// // remove key-val from leaf and check constraint for leaf, borrow/merge if necessary
// void removeLeaf( Node * leaf ) {

// }
// check constraint for internal node, merge borrow if needed


void merge( Node * cur, Node * sibling, Node * parent, bool isLeft ) {
  // left sibling does NOT have enough key-val pair, 
  // then merge left sibling to current node 
  // 1. move key-val pairs to left sibling
  for ( int i = 0; i < leaf->size(); i++ ) {
    sibling->insertKeyValuePair( leaf->getKeyAt( i ), left->getFPAt( i ) );
  }
  // 2. remove pointer for leaf node and shift other child pointers in parent node
  parent->removeChildAt( index ); 
  // 3. update key in parent and grandparent
  parent->removeKeyAt( index );
}

*/