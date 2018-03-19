#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "File.h"
using namespace std;

// M as an odd number makes life easier
const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles

// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
class Node{
private:
  string * keys[M];
  Node* children[M+1];
  FilePointer * filePointers[L+1]; // only useful in leaf nodes 
  bool * isDeleted[L+1]; 
  int nKeys;
  int nChild;  
  bool isLeaf;
  // int occupancy;
  // int capacity;
  Node * parent;
  
  // the following fields are only useful in leaf node
  Node * previous; // used in range query
  Node * next; // used in range query

 public:
  Node();
  // constructer for root
  Node( string word, FilePointer fp );  
  //constructor for a leaf
  Node( string word, FilePointer fp, bool isLeaf, Node * parent );
  Node( bool isLeaf, Node * parent );
  // Node( FilePointer fp, bool isLeaf );  
  // Node( string word );

  ~Node(){};
  //constructor for an internal node
  // Node(Node ** arrayOfNodes, int size);
  int size() { return this->nKeys; }
  int childSize() { return this->nChild; }
  void incrKeySize() { this->nKeys++; }
  void decrKeySize() { this->nKeys--; }
  void incrChildSize() { this->nChild++; }
  void decrChildSize() { this->nChild--; }

  bool getIsDeletedAt( int idx ) { return isDeleted[idx]; }
  bool getIsLeaf() { return isLeaf; }
  void setIsLeaf( bool isLeaf ){ isLeaf = isLeaf; }
  void insertLeaf( string name, int index, int endPos );
  bool isContain( FilePointer record );
  // int GetCapcity() const { return this->capacity; };
  // int GetOccupancy() const { return this->occupancy; };
  void print();
  string getKeyAt( int index ) { return *( keys[index] ); }
  // string * getKeyAt( int index ) { return keys[index]; }
  void setKeyAt( int index, string key ) { this->keys[index] = new string( key ); };
  void clearKeyAt( int index ) { this->keys[index] = nullptr; }
  // used for split leaf
  // void appendKey( string word ) { this->keys[nKeys] = new string( word ); nKeys++; }
  // void appendValue( FilePointer fp ) { this->filePointers[nKeys] = new FilePointer( fp );}
  
  // used in leaf node 
  void insertKeyValIsDeleted( string word, FilePointer fp, bool isD );
  void removeKeyValuePairAt( int index );

  // used in internal node
  void removeChildAt( int index );
  void removeKeyAt( int index );
  void insertKey( string word );
  void insertChild( Node * child, string key );
  int indexOfKey( string key );
  int indexOfFilePointer( string word );
  FilePointer * getFPAt( int index ) { return filePointers[index]; };
  void setFPAt(int index, FilePointer fp) { this->filePointers[index] = new FilePointer( fp ); }
  void clearFPAt(int index ) { this->filePointers[index] = nullptr;  }
  Node* getParent() { return parent; }
  void setParent(Node* parent) { this->parent=parent; }
  // void IncrOccupancy() { occupancy++; };
  // Node ** getNextLevel( string key );
  int indexOfChild( string key );
  // Node* Add( Node* child, Node* root);
  // Node* Add(string key, FilePointer fp, Node* root);
  Node ** getChildren() { return children; }
  void setChildAt(int index, Node* child){ this->children[index] = child; };
  Node* getChildAt( int index ) { return this->children[index]; }
  Node* getNext(){ return next; };
  Node* getPrev(){ return previous; };
  void setNext(Node* next){ this->next = next; };
  void setPrevious(Node* previous){ this->previous = previous; }
};

#endif
