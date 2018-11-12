#ifndef MY_HASH_NODE
#define MY_HASH_NODE
#include <iostream>

using namespace std;

class HashNode {
  unsigned long key;   // The hash node's key
  unsigned long value; // The key's associated data

  /* extend if necessary */

public:

  // Add constructors, destructor if necessary

  //Default Constructor
  HashNode(){
    this->key =0;
    this->value=0;
  }

  //Constructor with Values
  HashNode(unsigned long key, unsigned long value){
   this -> key=key;
   this -> value=value;
  }

  //Destructor
 ~HashNode(){
    cout << "Destructor Called" << endl;
  }

  unsigned long getKey() { return key; }
  
  unsigned long getValue() { return value; }
  
  void setKey(unsigned long value);

  void setValue(unsigned long input);

  void assign(unsigned long key, unsigned long value);

  // extend if necessary
};

/* 
   Implement the assign method 
   and any methods that you may additionally need for the HashTable to work.
*/

void HashNode::setKey(unsigned long key){
  this->key= key;
}

void HashNode::setValue(unsigned long value){
  this->value= value;
}

void HashNode::assign(unsigned long key, unsigned long value){
    setKey(key);
    setValue(value);
  }



#endif
