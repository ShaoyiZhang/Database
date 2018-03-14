#include "BPlusTree.h"

// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
BPlusTree::BPlusTree(){
  this->root = nullptr;
  count = 0;
}
BPlusTree::BPlusTree ( FilePointer record ) {
  Node * root = new Node( record );
  this->root = root;
  count = 1;
}

BPlusTree::~BPlusTree(){
  return;
}

// Return a pointer to a leaf node that might contain the word
Node * BPlusTree::searchHelper( string word ) {
  if ( this->root == nullptr ) {
    // all elements in the tree has been deleted
    cout << "empty tree\n";
    return nullptr;//make_pair( nullptr, -1 );
  }
  Node * cur = this->root;
  while ( cur->getIsLeaf() == false ) {
    // cout << "try move down\n";
    vector<Node*> * childrenPtr = cur->getChildren();
    // cout << "address of childrenPtr: " << childrenPtr << endl;
    int index = cur->indexOfChild( word ) ;
    // cout << "index of child: " << index << endl;
    if ( index == cur->getChildren()->size() ) {
      // we scaned all children, but the deseried leaf node is missing
      // we will init a new leaf, insert to cur->children
      cout << "child pointer does NOT exist\n";
      Node * newLeaf = new Node( true, cur );
      cur->getChildren()->push_back( newLeaf );
    }
    // retrieve the leaf node pointer and return to caller
    cur = ( *childrenPtr )[ cur->indexOfChild( word ) ];   
    // cout << "move down complete\n";
    // cur = *( cur->GetChildren() )[ cur->IndexOfChild( word ) ];
  }
  return cur;
}

// return the leaf node and the index of the filepointer
bool BPlusTree::search( string word ) {
  Node * cur = searchHelper( word );
  // size == 0, new leaf, delete this leaf
  cout << " search size " << cur->size() << endl;
  if ( cur == nullptr || ( cur != nullptr && cur->size() == 0 ) ) {
    cur->getParent()->getChildren()->pop_back(); // delete empty leaf created in searchhelper
    return false; // empty tree
  }
  // check whether record is in the leaf node -> O(L)
  int index = cur->indexOfFilePointer( word );
  cout << "??????\n";
  if ( index == -1 ) {
    return false;
  } else {
    // found word
    // cout << "found word \"" << word << "\" at " << cur << ", " << index << endl;
    return true;
  }
}

// insert a newly splitted node(child) to its parent(this)
void BPlusTree::insertHelper( Node * parent, Node * child ) {
  int index = parent->indexOfChild( child->getKeyAt(0) );
  // NoneLeafNode case
  index++;
  int occupancy = parent->size() + 1; // size of children
  // shift latter half of the node to the right to make room for the new node
  for (int i = occupancy - 1; i >= index;i--){
      // keys[i] = keys[i-1];
      parent->setKeyAt( i, parent->getKeyAt( i - 1 ) );
      // children[i+1] = children[i];
      parent->setChildAt( i + 1, parent->getChildAt( i ) );
  }
  parent->setChildAt( index, child );
  child->setParent( parent );
  parent->setKeyAt( index-1, child->getKeyAt(0) );
  // occupancy++;
  // if the none leaf node is FULL
  // need to split
  if ( occupancy == M + 1 ){
    if ( parent == root ){
      splitRoot( );
    } else {
      splitNoneLeaf( );
    }
  }
  // return NULL;
}
void BPlusTree::splitRoot() {

}
void BPlusTree::splitNoneLeaf() {

}

void BPlusTree::splitLeaf( Node * cur ) {
  cout << "split leaf !\n";
  Node * newLeaf = new Node(true, cur );
  assert( cur->size() == L + 1 );
  int leftBound = ceil(static_cast<double>(L)/2);

  for (int i = leftBound; i <= L; i++){
    // copy latterHalf(index 2,3) to new leaf
    newLeaf->appendKey( cur->getKeyAt( i ) );
    newLeaf->appendValue( cur->getFPAt( i ) );
  }
  // retain the linked list structure of leaf nodes to support range query
  if ( cur->getNext() != nullptr ) { //&&this->next->keys[0]!="")
    cur->getNext()->setPrevious( newLeaf );
  }
  newLeaf->setNext( cur->getNext() );
  newLeaf->setParent( cur->getParent() );
  newLeaf->setPrevious( cur );
  cur->setNext( newLeaf );
  // insert new leaf to parent (which must be none-leaf)
  // if this is not root
  if( cur != root ) {
    insertHelper( cur->getParent(), newLeaf );
    // if ( temp != NULL ) {
    //   root = temp;
    // }
  } else { // current node is root
    // Node* newRoot = new Node(false);
    // Node* temp = root;
    // root = newRoot;
    // newRoot->SetChildrenAt(0, temp);
    // temp->SetParent(root);
    // // newRoot->IncrOccupancy();
    // root->Add(newLeaf, this);
  }
  // return root;
}

void BPlusTree::insert( string word, FilePointer record ){
  // TO DO: Tree empty
  if ( root == nullptr ) {
    cout << "Empty tree, do nothing\n";
    return;
  }
  // case none-empty tree
  // find leaf node to insert record, potentially split nodes recursively
  // candidate is a leaf node
  Node * candidate = searchHelper( word ); // leaf node
  cout << "insert continue after search helper return\n";
  assert( candidate != nullptr && candidate->getIsLeaf() == true );
  // if ( candidate != nullptr ) { 
  //   Node * parent = candidate->getParent(); // internal node (could be root)
  // }
  // insert in leaf
  // candidate->insert( word, record );
  int index = candidate->indexOfKey( word );
  cout << "before insert key value\n";
  if ( candidate->size() == 0 || candidate->size() == index ) {
    // just use push_back
    candidate->appendKey( word );
    candidate->appendValue( record );    
  } else {
    // find the right location to insert
    candidate->insertKeyValuePair( word, record );
    cout << "!!! size " << candidate->size() << endl;
    for ( int i = 0; i < candidate->size(); i++ ) {
      cout << candidate->getKeyAt(i) << " ";
    }
    cout << endl;
  }
  cout << "key vale pair inserted at leaf node(candidate)\n";
  // check leaf node size to see if we need to split leaf
  if ( candidate->size() == L + 1 ) {
    // need to split leaf
    splitLeaf( candidate );
  }
}

void BPlusTree::printAllKeys( Node * cur ){
  if ( cur == NULL ) {
    return;
  }
  // root->PrintAllKeys();
  if( cur->getIsLeaf() == false ) {
    for(int i = 0; i < M; i++) {
      vector<Node*> * childrenPtr = cur->getChildren();
      printAllKeys( (*childrenPtr)[i] );
    }
  }
}

void BPlusTree::printAll( Node* cur ){
  if(cur == NULL) {
    return;
  }
  if( cur->getIsLeaf() ) {
    while( cur->getNext() != NULL) {
      cur->print();
      cur = cur->getNext();
    }
    cur->print();
  }
  else {
    vector<Node*> * childrenPtr = cur->getChildren();    
    printAll( (*childrenPtr)[0] );
  }
}
  /*
    Node* parent = InsertHelper(key,root);
    Node* leaf = parent->GetNextLevel(key);
    int indexOfChild = parent->IndexOfChild(key);
    if (parent->GetIsLeaf()){
        count ++;
        Node* tempRoot = parent->Add(key,value, root);
        if (tempRoot!= NULL)
            root = tempRoot;
    }
    else if (leaf == NULL){
        count ++;
        Node* newLeaf = new Node(true,parent);
        newLeaf->SetKeyAt(0, key);
        newLeaf->SetValueAt(0,value);
        parent->GetChildren()[indexOfChild] = newLeaf;
        // if newLeaf is the first leaf in that level
        // its previous should be NULL
        if (indexOfChild==0){
            newLeaf->SetPrevious(NULL);
        }
        else{
            newLeaf->SetPrevious(parent->GetChildren()[indexOfChild-1]);
            newLeaf->GetPrevious()->SetNext(newLeaf);
        }
        newLeaf->SetNext(NULL);
        newLeaf->IncrOccupancy();
        parent->IncrOccupancy();
    }
    // leaf already exist, insert to leaf
    // check if need to split leaf
    else{
        count ++;
        Node* temp = leaf->Add(key,value,this->GetRoot());
        if (temp)
            this->root = temp;
    }
    */
