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
Node * BPlusTree::SearchHelper( string word ) {
  if ( this->root == nullptr ) {
    // all elements in the tree has been deleted
    return make_pair( nullptr, -1 );
  }
  Node * cur = this->root;
  while ( cur->GetIsLeaf() == false ) {
    cout << "try move down\n";
    vector<Node*> * childrenPtr = cur->GetChildren();
    cout << "address of childrenPtr: " << childrenPtr << endl;
    cout << "index of child: " << cur->IndexOfChild( word ) << endl;
    cur = ( *childrenPtr )[ cur->IndexOfChild( word ) ];   
    cout << "move down complete\n";
    // cur = *( cur->GetChildren() )[ cur->IndexOfChild( word ) ];
  }
  return cur;
}

// return the leaf node and the index of the filepointer
pair< Node *, int > BPlusTree::Search( string word ) {
  Node * cur = SearchHelper( word )
  // check whether record is in the leaf node
  int index = cur->IndexOfFilePointer( word );
  if ( index == -1 ) {
    return make_pair( nullptr, -1 );
  } else {
    // found word
    cout << "found word \"" << word << "\" at " << cur << ", " << index << endl;
    return make_pair( cur, index );
  }
}

void BPlusTree::Insert( FilePointer record ){
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
}