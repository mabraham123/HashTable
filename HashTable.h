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


/*
 Find the value for a key
 Parameter:
 key-  The key for the hashnode
*/
ulint HashTable::getValue(ulint key){

  //Find the key hash
  ulint index= hash_function(key);

  //Create a new node to save the Hashlist
  list<HashNode> *HListCopy=nullptr;
 
  //Index the bucket
  HListCopy= &(table->at(index));

  //Loop through the List and see if a node exists
  for(HashNode &hashNode: *HListCopy){
    //If the key exists
    if(key==hashNode.getKey()){
    //return the value
      return hashNode.getValue();
    }
  }

  //Return error message if the key is not found
  throw KEY_NOT_FOUND;
}

/*
  Method to insert a hashnode to the Hash table
  Parameters:
  key-  Key value to be hashed
  value-  Data that is held in the node
*/
void HashTable::insert(ulint key, ulint value){
 
  //Check how full the HashTable
  if((num/size())>=0.9){
    //Make the table bigger if it's too full
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
  cout <<"Inserted Successfull" <<endl;
}

/*
  Method to erase a HashNode from the table
  Parameter:
  key-  key for the hashnode
*/
void HashTable::erase(ulint key){


  //Hash the key
  ulint index =hash_function(key);
  
  //Check if the key exists
    //Index the bucket
    list<HashNode>* HListCopy= &(table->at(index));

    //Loop though the list
    for(list<HashNode>::iterator it=(*HListCopy).begin(); it !=(*HListCopy).end(); ++it){
      //If the key is found
      if (it->getKey()==key){
        //Remove the node
          it = (*HListCopy).erase(it);

          cout << "Erase Successfull" <<endl;
        //Stop the search
          break;
        }
      }
}



/*
  Method to rehash the table when the contents of a table gets too full
  Parameter:
  newSize-  the size of the new table
*/
void HashTable::rehash(size_t newSize){
  Table *oldTable=table;
  try{
  table = new Table(newSize);

  for (int index = 0; index < (int)(*oldTable).size(); index++)
  {
    if (!(oldTable->at(index).empty())){
      for (HashNode &hashNode: (*oldTable).at(index))
      {
        ulint key=hashNode.getKey();
        ulint value=hashNode.getValue();
        insert(key,value);
      }
    }
  }
}catch(...){
  //return OUT_OF_MEMORY;
  cout<< "You have ran out of memory" << endl;
 // cout<< "You have ran out of memeory" <<endl;
}
  delete oldTable;
}



#endif
