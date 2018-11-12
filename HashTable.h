#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode>> Table;
  Table *table; // size of table is stored in the Table data structure
  size_t num;   // number of entries in the HashTable;

public:
  HashTable();       // constructor, initializes table of size 1;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)
  size_t hash_function(ulint);  // the table's hash function
  ulint getValue(ulint);    // find and return data associated with key

  void insert(ulint,ulint); // insert data associated with key into table
  void erase(ulint);        // remove key and associated data from table

  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table 

  // extend if necessary
};

/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/

/*
  Default Constructor
*/
HashTable::HashTable(){
  this->table= new Table(11, list<HashNode>());
  this->num=0;
}

/*
  Assigned Values Contructor 
*/
HashTable::HashTable(size_t sizeOfTable){
  this->table=new Table(sizeOfTable, list<HashNode>());
  this->num=0;
}

/*
  Destructor
*/
HashTable::~HashTable(){
 delete this->table;
}

/*
  Get the number of buckets
*/
size_t HashTable::size(){
  return (*table).size();
}

/*
  Hash function
*/
size_t HashTable::hash_function(ulint key){
  return key%size();
}


// find and return data associated with key
ulint HashTable::getValue(ulint key){

  //Find the key hash
  ulint index= hash_function(key);

  //Index the bucket
  list<HashNode> *HashListCopy=nullptr;
  HashListCopy= &(table->at(index));

  //Find if the value exits
  for (HashNode &hashNode: *HashListCopy){
    if (hashNode.getKey()==key){
    //return the value
      return hashNode.getValue();
    }
  }

  //Return error message
  throw KEY_NOT_FOUND;
}

void HashTable::insert(ulint key, ulint value){
 
  //Check size for rehash
  if((num/size())>=0.9){
    rehash(2*size());
  }



  //Create new node
  HashNode nodeToAdd;
  nodeToAdd.assign(key,value);

  //Find the hash
  size_t index=hash_function(key);

  //Move to the index
  (*table).at(index).push_back(nodeToAdd);

  num+=1;
}


void HashTable::erase(ulint key){


  //Hash the key
  ulint index =hash_function(key);
  
  //Check if the key exists
    //Index the bucket
    list<HashNode>* HashListCopy= &(table->at(index));

    //Find if the value exits
    for(list<HashNode>::iterator it=(*HashListCopy).begin(); it !=(*HashListCopy).end(); ++it){
      if (it->getKey()==key){
          it = (*HashListCopy).erase(it);
          break;
        }
      }
}

void HashTable::rehash(size_t newSize){
  Table *originalTable=table;

  table = new Table(newSize);

  for (int index = 0; index < (int)(*originalTable).size(); index++)
  {
    if (!(originalTable->at(index).empty())){
      for (HashNode &hashNode: (*originalTable).at(index))
      {
        ulint key=hashNode.getKey();
        ulint value=hashNode.getValue();
        insert(key,value);
      }
    }
  }

  delete originalTable;
}


#endif
