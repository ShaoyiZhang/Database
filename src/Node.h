#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
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
  Node( FilePointer fp, bool isLeaf );
  // Node( FilePointer fp, bool isLeaf );  
  // Node( string word );

  ~Node(){};
  //constructor for an internal node
  // Node(Node ** arrayOfNodes, int size);

  bool GetIsLeaf() const { return isLeaf; }
  void SetIsLeaf( bool isLeaf ){ isLeaf = isLeaf; }
  void InsertLeaf( string name, int index, int endPos );
  bool IsContain( FilePointer record );
  // int GetCapcity() const { return this->capacity; };
  // int GetOccupancy() const { return this->occupancy; };

  string GetKeyAt( int index ) const { return keys[index]; };
  void SetKeyAt( int index, string key ) { this->keys[index] = key; };
  
  int IndexOfKey( string key );
  int IndexOfFilePointer( string word );
  FilePointer GetFPAt( int index ) const { return this->filePointers[index]; };
  void SetFPAt(int index, FilePointer fp) { this->filePointers[index] = fp; };
  Node* GetParent() const { return parent; };
  void SetParent(Node* parent) { this->parent=parent; };
  // void IncrOccupancy() { occupancy++; };
  vector< Node * > * GetNextLevel( string key );
  int IndexOfChild( string key );
  Node* Add( Node* child, Node* root);
  Node* Add(string key, FilePointer fp, Node* root);
  vector< Node * > * GetChildren() { return &children; };
  void SetChildrenAt(int index, Node* child){ this->children[index] = child; };
  Node* GetNext(){ return next; };
  Node* GetPrevious(){ return previous; };
  void SetNext(Node* next){ this->next = next; };
  void SetPrevious(Node* previous){ this->previous = previous; };
  Node * SplitNoneLeaf( Node* root);
  Node * SplitRoot( Node* root);
  Node * SplitLeaf( Node* root);
};

/*
class Node{
private:
  string* keys;
  int* values;
  Node** children;
  Node* parent;
  bool isLeaf;
  int occupancy;
  int capacity;
  Node* previous;
  Node* next;
public:
  Node():keys(NULL),values(NULL),children(NULL),parent(NULL),isLeaf(false),occupancy(0),capacity(0),previous(NULL),next(NULL){};
  Node(bool isLeaf);
  Node(bool isLeaf, Node* parent);
  bool IsLeaf(){ return this->isLeaf; };




  ~Node();

  void Print();

  void PrintAllKeys(){
      for(int i = 0; i < occupancy-1; i++)
          cout << keys[i];
      cout << endl;
  };
};
*/
#endif
