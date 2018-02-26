#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include <iostream>
#include <vector>
#include "File.h"
using namespace std;

const int M = 5;
const int L = 3;

class Node{
 private:
  vector< string > keys;
  vector< Node * > nextLevel;
  bool isLeaf;
  int occupancy;
  int capacity;
  vector< Node * > parent;
  
  // the following fields are only useful in leaf node
  vector< FilePointer > filePointers; // only useful in leaf nodes  
  Node * previous; // used in range query
  Node * next; // used in range query

 public:
  Node();
  // constructer for root
  Node( string word, FilePointer fp );  
  //constructor for a leaf
  Node( string word, bool isLeaf );
  Node( string word, FilePointer fp, bool isLeaf );  
  // Node( string word );

  ~Node(){};
  //constructor for an internal node
  // Node(Node ** arrayOfNodes, int size);

  bool GetIsLeaf() const { return isLeaf; }
  void SetIsLeaf( bool value ){ isLeaf = value; }
  void InsertLeaf( string name, int index, int endPos );

  int GetCapcity() const { return this->capacity; };
  int GetOccupancy() const { return this->occupancy; };

  string GetKeyAt( int index ) const { return keys[index]; };
  void SetKeyAt( int index, string key ) { this->keys[index] = key; };

  // Node SplitNoneLeaf( Node* root);
  // Node SplitRoot( Node* root);
  // Node SplitLeaf( Node* root);
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

  int IndexOfKey(string key) const;

  void SetValueAt(int index, int value){ this->values[index]=value; };
  int GetValueAt(int index){return this->values[index];};
  Node* GetParent(){ return parent; };
  void SetParent(Node* parent){ this->parent=parent; };
  void IncrOccupancy(){ occupancy++; };
  Node* GetNextLevel(string key) const;
  int IndexOfChild(string key) const;
  Node* Add(Node* child,Node* root);
  Node* Add(string key, int value, Node* root);
  ~Node();

  void Print();
  Node** GetChildren(){ return children; };
  void SetChildrenAt(int index, Node* child){ this->children[index] = child; };
  Node* GetNext(){ return next; };
  Node* GetPrevious(){ return previous; };
  void SetNext(Node* next){ this->next = next; };
  void SetPrevious(Node* previous){ this->previous = previous; };
  void PrintAllKeys(){
      for(int i = 0; i < occupancy-1; i++)
          cout << keys[i];
      cout << endl;
  };
};
*/
#endif
