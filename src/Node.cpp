#include "Node.h"

// constructor for root node
Node::Node( string word, FilePointer fp ) : isLeaf( false ), previous( nullptr ),
                                                      occupancy( 1 ), capacity( M ) {
  this->keys.push_back( word );
  Node * newLeaf = new Node( word, fp, true );
  this->nextLevel.push_back( newLeaf );
}

// // constructor for leaf node
// // in
Node::Node( string word,FilePointer fp, bool isLeaf ) : isLeaf( isLeaf ) {
   this->keys.push_back( word );
   // this->isLeaf = true;
   this->filePointers.push_back( fp );
}

// return the index of a given key in the keys array
// if name is NOT present in the array, return -1
int Node::IndexOfKey(string key) const{
    int index = 0;
    for (int i = 0; i < occupancy; i++){
        if (key>=keys[i])
            index++;
    }
    return index;
}

// Node::~Node()

// OLD STUFF below this line 
// Node::Node(bool isLeaf):keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(isLeaf),occupancy(0),capacity(0){
//     if ( isLeaf == true ) { 
//         keys = new string[L+1];
//         values = new int[L+1];
//         for(int i = 0; i < L; i++){
//             values[i] = INT_MIN;
//             keys[i] = "";
//         }
//         capacity = L;
//     } 
//     else{
//         keys = new string[M];
//         children = new Node*[M+1];
//         for (int i = 0; i < M; i++){
//             children[i]=NULL;
//             keys[i] = "";
//         }
//         children[M] = NULL;
//         capacity = M;
//     }
// }

// Node::Node(bool isLeaf, Node* parent):keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(isLeaf),occupancy(0),capacity(0){
//     this->parent = parent;    
//     if (isLeaf==true){
//         keys = new string[L+1];
//         values = new int[L+1];
//         for(int i = 0; i < L; i++){
//             values[i] = INT_MIN;
//             keys[i] = "";
//         }
        
//         capacity = L;
//     } 
//     else{
//         keys = new string[M];
//         children = new Node*[M+1];
//         for (int i = 0; i < M; i++){
//             children[i]=NULL;
//             keys[i] = "";
//         }
//         children[M] = NULL;
//         capacity = M;   
//     }
// }



// Node::~Node(){
//     delete keys;
//     delete [] children;    
//     delete [] filePointers;
//     // delete parent;
// }



// returns a pointer to next level
// the pointer may point to either InternalNode or LeafNode
vector< Node * > * Node::GetNextLevel( string key ) const {
  if ( this->isLeaf ) {
    return NULL;
  }
  return this->children[IndexOfChild( key )];
}

// A function for InternalNode (Road map)
// return the index of the pointer which lead us to next level
int Node::IndexOfChild( string key ) const {
    int index = 0;
    while ( index < children.size() && key >= keys[index] ) {
        //cout << "capacity"<<this->GetCapcity()<<endl;
        index++;
    }
    //cout<<"index"<< index << endl;
    return index;
}

// add node to noneleaf
Node* Node::Add( Node* child, Node* root ){
  // NoneLeafNode case
  int index = this->IndexOfChild(child->keys[0]);
  // index++;
  child->SetParent( this );  
  this->keys.push_back( child.GetKeyAt( 0 ) );
  this->children.push_back( child );
  int occupancy = this->keys.size();
  for ( int i = index; i < size; i++ ) {
    // NOTE: need to verify correctness
    swap( this->keys[i], this->keys[size - 1] );
    swap( this->children[i + 1], this->children[size] );
  }
  // for ( int i = this->GetChildren().size() - 1; i >= index; i-- ) {
  //     keys[i]=keys[i-1];
  //     children[i+1] = children[i];
  // }
  // this->children[index]=child;
  // child->SetParent(this);
  // keys[index-1] = children[index]->GetKeyAt(0);
  // occupancy++;

  // if the none leaf node is FULL
  // need to split
  if ( occupancy > M ){
      if (parent == NULL){
          return SplitRoot(root);
      }
      else
          return SplitNoneLeaf(root);
  }
  return NULL;
}

// Add key-value ( word to rid ) pair to Leaf
Node* Node::Add( string key, FilePointer fp, Node* root){
  int index = this->IndexOfKey(key);
  this->filePointers.push_back( fp );
  int occupancy = this->filePointers.size();
  for ( int i = index; i < size; i++ ) {
    // NOTE: need to verify correctness
    swap( this->filePointers[i], this->filePointers[size - 1] );
    // swap( this->children[i + 1], this->children[size] );
  }
    // for (int i = this->occupancy-1; i >= index; i--){
    //     //SetKeyAt(i+1, GetKeyAt(i));
    //     keys[i+1]=keys[i];
    //     values[i+1] = values[i];
    // }
    // this->SetKeyAt(index, key);
    // values[index]=value;
    // occupancy ++;
  if ( occupancy > M ){
    Node * temp = SplitLeaf(root);
    if (temp) {
      return temp;
    }
  }
  return NULL;
}

/* 
  If this function is called, children.size() must be equal to constant M.
  To split a root called N1 ( parent == NULL ), we'll do the following:
  1. move the second half of the root node to a new node called N2
  2. create a new root node called R1
  3. insert N1 and N2 to R1
  4. return R1 to update the pointer address in B+ tree
*/
Node * Node::SplitRoot(Node* root){
  Node * latterHalf = new Node( false );
  int middle = ceil(static_cast<double>(M)/2);
  // for now, occupancy = 6 = capacity = M
  // copy half of keys to new node
  // key index 3,4 go to new node
  int curNumKeys = this->keys.size();
  vector<string>::const_iterator first = this->keys.begin() + middle ;
  vector<string>::const_iterator last = this->keys.back();
  
  vector<T> newVec(first, last);
  for ( int i = middle; i < curNumKeys; i++ ) {
    latterHalf->push_back( this->keys[i] );
      // latterHalf->keys[index]=this->keys[i];
      // keys[i] = "";
      //latterHalf->SetKeyAt(index, this->GetKeyAt(i));
  }
  index = 0;
  // copy half of children to new node
  // child index 3,4,5 go to new node
  // int origOccupancy = occupancy;
  for (int i = middle; i<origOccupancy; i++){
    latterHalf->children[index]=this->children[i];
    latterHalf->children[index]->SetParent(latterHalf);
    index++;
    children[i]=NULL;
    latterHalf->occupancy++;
    this->occupancy--;
  }
  Node* newRoot = new Node(false);
  Node* temp = latterHalf;
  while (!temp->IsLeaf()){
    temp = latterHalf->GetChildren()[0];
  }
  // temp is leaf now
  newRoot->SetKeyAt(0,temp->GetKeyAt(0));
  newRoot->SetChildrenAt(0, this);
  this->SetParent(newRoot);
  newRoot->SetChildrenAt(1, latterHalf);
  latterHalf->SetParent(newRoot);
  newRoot->IncrOccupancy();
  newRoot->IncrOccupancy();
  return newRoot;
}

Node* Node::SplitNoneLeaf(Node* root){
  Node* latterHalf = new Node(false);
  int middle = ceil(static_cast<double>(M)/2);
  int index = 0;
  // for now, occupancy = 6 = capacity = M
  // copy half of keys to new node
  // key index 3,4 go to new node
  for (int i = middle; i<occupancy-1; i++){
    latterHalf->keys[index]=this->keys[i];
    keys[i] = "";
    index++;
  }
  index = 0;
  // copy half of children to new node
  // child index 3,4,5 go to new node
  int origOccupancy = occupancy;
  for (int i = middle; i<origOccupancy; i++){
      latterHalf->children[index]=this->children[i];
      latterHalf->children[index]->SetParent(latterHalf);
      index++;
      children[i]=NULL;
      latterHalf->occupancy++;
      this->occupancy--;
  }
  Node* temp = this->GetParent()->Add(latterHalf,root);
  if (temp!=NULL)
      root = temp;
  return root;
}

Node* Node::SplitLeaf(Node* root){
  Node* newLeaf = new Node(true);
  for (int i = L; i >= ceil(static_cast<double>(L)/2); i--){
      // copy latterHalf(index 2,3) to new leaf
      newLeaf->Add(keys[i], values[i],root);
      keys[i] = "";
      values[i]=INT_MIN;
      this->occupancy--;
  }
  // this->next might be 0x646576697265442f
  // this->previous might be 0x65646f63582f0009
  // should not happen since we initialize all nodes' next and previous to NULL at the first place
  if (this->next!=NULL/*&&this->next->keys[0]!=""*/)
      this->next->SetPrevious(newLeaf);
  newLeaf->next = this->next;
  newLeaf->parent = this->parent;
  newLeaf->previous = this;
  this->next = newLeaf;
  // insert new leaf to parent (which must be none-leaf)
  // if this is not root
  if(this->parent != NULL){
      Node* temp = this->parent->Add(newLeaf,root);
      if (temp!=NULL)
          root = temp;
  }
  // current node is root
  else{
      Node* newRoot = new Node(false);
      Node* temp = root;
      root = newRoot;
      newRoot->SetChildrenAt(0, temp);
      temp->SetParent(root);
      newRoot->IncrOccupancy();
      root->Add(newLeaf, this);
  }
  return root;
  // Add function automatically split parent if necessary
}

void Node::Print(){
  if (IsLeaf()){
      for (int i = 0; i < this->occupancy; i++){
          cout << "Key: "<< this->keys[i] << " Value: " << this->values[i] << endl;
      }
  }
}
