#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "File.h"
using namespace std;

const int M = 5;   // num of max pointers to next level
const int L = 3;   // num of max profiles

// #ifdef USE_EXPORT_KEYWORD
// export
// #endif
// template<class T>
class Node{
private:
  vector< string > keys;
  vector< Node * > children;
  bool isLeaf;
  // int occupancy;
  // int capacity;
  Node * parent;
  
  // the following fields are only useful in leaf node
  vector< FilePointer > filePointers; // only useful in leaf nodes  
  Node * previous; // used in range query
  Node * next; // used in range query

 public:
  Node();
  // constructer for root
  Node( FilePointer fp );  
  //constructor for a leaf
  Node( FilePointer fp, bool isLeaf, Node * parent );
  Node( bool isLeaf, Node * parent );
  // Node( FilePointer fp, bool isLeaf );  
  // Node( string word );

  ~Node(){};
  //constructor for an internal node
  // Node(Node ** arrayOfNodes, int size);
  int size() { return this->keys.size(); }
  bool getIsLeaf() { return isLeaf; }
  void setIsLeaf( bool isLeaf ){ isLeaf = isLeaf; }
  void insertLeaf( string name, int index, int endPos );
  bool isContain( FilePointer record );
  // int GetCapcity() const { return this->capacity; };
  // int GetOccupancy() const { return this->occupancy; };
  void print();
  string getKeyAt( int index ) { return keys[index]; };
  void setKeyAt( int index, string key ) { this->keys[index] = key; };
  // used for split leaf
  void appendKey( string word ) { this->keys.push_back( word ); }
  void appendValue( FilePointer fp ) { this->filePointers.push_back( fp ); };
  
  // used in leaf node 
  void insertKeyValuePair( string word, FilePointer fp );

  int indexOfKey( string key );
  int indexOfFilePointer( string word );
  FilePointer getFPAt( int index ) { return this->filePointers[index]; };
  void setFPAt(int index, FilePointer fp) { this->filePointers[index] = fp; };
  Node* getParent() { return parent; };
  void setParent(Node* parent) { this->parent=parent; };
  // void IncrOccupancy() { occupancy++; };
  vector< Node * > * getNextLevel( string key );
  int indexOfChild( string key );
  // Node* Add( Node* child, Node* root);
  // Node* Add(string key, FilePointer fp, Node* root);
  vector< Node * > * getChildren() { return &children; };
  void setChildAt(int index, Node* child){ this->children[index] = child; };
  Node * getChildAt( int index ) { return this->children[index]; }
  Node* getNext(){ return next; };
  Node* getPrevious(){ return previous; };
  void setNext(Node* next){ this->next = next; };
  void setPrevious(Node* previous){ this->previous = previous; };
};

#endif
