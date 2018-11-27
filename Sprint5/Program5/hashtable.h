#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "IndexInterface.h"
#include "list"

template <typename T,typename K> class HashTable;
/*
 *The Hash table will contain a key and value.
 * The KEY IS MADE BY A HASH FUNCTION GO GET THE INDEX IN THE ARRAY
 * WHERE THE VALUE WILL BE INSERTED.
 * This will provide constant look up and insertion.
 */
template <typename T,typename K>
class HashTable : public IndexInterface<T,K>
{

public:
    HashTable();
    HashTable(const HashTable<T,K> &rightObj);
    ~HashTable();
    HashTable<T,K>& operator=(const HashTable<T,K> &rightObj);
<<<<<<< HEAD
    virtual T& operator[](K& lookUpKey);
=======
    T& operator[](K& lookUpKey);
>>>>>>> origin
    virtual int getSize();
    virtual void insert( T &d, K &k);//value first then key
    /*find: will traverse the table and see if a key exists at that index.
     *The index is computed by getting the hash of a key(string).*/
    virtual T& find( K& k );
    virtual void printInOrder();
private:
    /*This function will return an index of where to store a certain element
    * based on the hash calculated by this function.*/
    unsigned int getHashKeyIndex(K &k);

    //private variables
    int elementsInTable;
    const int sizeOfTable = 100000;
    //std::list<std::pair<K,T>> TableList[100000];
    std::list<std::pair<K,T>> *TableList;
};
//default constructor
template <typename T,typename K>
HashTable<T,K> :: HashTable()
{
    //initializing private variables
    elementsInTable = 0;
    TableList = new std::list<std::pair<K,T>>[sizeOfTable];
}

//copy constructor
template <typename T,typename K>
HashTable<T,K> :: HashTable(const HashTable<T,K> &rightObj)
{
    //copy private variables
    this->elementsInTable = rightObj.elementsInTable;
    //This first for loop is to acces each individual list in list array.
    for(int index = 0; index < sizeOfTable; ++index){
        //copy every single pair from right to left
        for(auto it = rightObj.TableList[index].begin(); it != rightObj.TableList[index].end(); ++it ){
            std::pair<K,T> tempPair;
            //first will contain the identifer of the object
            tempPair.first = it->first;
            //second will contain the object itself
            tempPair.second = it->second;
            //we insert pair into hashtable
            TableList[index].push_back(tempPair);
        }
    }
}

//destructor
template <typename T,typename K>
HashTable<T,K> :: ~HashTable()
{
    //delete dynamic memory
    delete [] TableList;
}

//overloaded assignment operator
template <typename T,typename K>
HashTable<T,K>& HashTable<T,K> :: operator=(const HashTable<T,K> &rightObj)
{
    //first we delete evertyhing on left hand side
    delete [] TableList;
    //allocate a new table
    TableList = new std::list<std::pair<K,T>>[sizeOfTable];
    //copy private variables
    this->elementsInTable = rightObj.elementsInTable;
    //This first for loop is to acces each individual list in list array.
    for(int index = 0; index < sizeOfTable; ++index){
        //copy every single pair from right to left
        for(auto it = rightObj.TableList[index].begin(); it != rightObj.TableList[index].end(); ++it ){
            std::pair<K,T> tempPair;
            //first will contain the identifer of the object
            tempPair.first = it->first;
            //second will contain the object itself
            tempPair.second = it->second;
            //we insert pair into hashtable
            TableList[index].push_back(tempPair);
        }
    }
    //return rhs obj
    return *this;
}

/* WARNING MUST USE A TRY AND CATCH FOR THIS FUNCTION!!!!!
 * We can use this to return the object by using its key to look for it.
 * Example to use this function:
 * Hashtable["law"].getFileAndCount();
*/
template <typename T,typename K>
T& HashTable<T,K> ::  operator[](K& lookUpKey)
{
    //we pass in the key to get hash function, which index will store the index where this key should be stored
    unsigned int index = getHashKeyIndex(lookUpKey);
    //if the list at this current index is empty it means we didn't find the object
    if(TableList[index].empty())
        throw std::out_of_range("Error object not found in HashTable. Inside [] operator.");

    for(auto it = TableList[index].begin(); it != TableList[index].end(); ++it ){
        //look for the object by comparing keys in the list
        if(it->first == lookUpKey)
            return it->second;
    }
    //if the object was not found with the iterator we will throw an exception.
    throw std::out_of_range("Error object not found in HashTable. Inside [] operator.");
}

//getting the number of elements in the hashtable
template <typename T,typename K>
int HashTable<T,K> ::  getSize()
{
    return elementsInTable;
}

template <typename T,typename K>
void HashTable<T,K> ::  insert( T &data, K &key)
{
    //get index of key
    unsigned int index = getHashKeyIndex(key);
    //adding first key and value in list
    std::pair<K,T> KeyValPair;
    //first will contain the identifer of the object
    KeyValPair.first = key;
    //second will contain the object itself
    KeyValPair.second = data;
    //we insert pair into hashtable
    TableList[index].push_back(KeyValPair);
    //increment counter
    ++elementsInTable;
}


/* find function
 *WARNING MUST USE A TRY AND CATCH FOR THIS FUNCTION!!!!!
*/
template <typename T,typename K>
T&  HashTable<T,K> :: find( K& lookUpKey )
<<<<<<< HEAD
{
=======
{    
>>>>>>> origin
    //getting index of key
    unsigned int index = getHashKeyIndex(lookUpKey);

    //if the list at that index is empty throw an exception
    if( TableList[index].empty() )
        throw std::out_of_range("Error, object does not exist on hashtable.");

    //iterative through list to find the key value pair.
    for(auto pairIterator = TableList[index].begin(); pairIterator != TableList[index].end(); ++pairIterator ){
        //key to the object is found
        if(pairIterator->first == lookUpKey){
            //return the word object
            return pairIterator->second;
        }
    }
    //throw excepetion if object not found after iterating a non-empty list
    throw std::out_of_range("Error, object does not exist on hashtable.");
}

template <typename T,typename K>
void  HashTable<T,K> :: printInOrder()
{
    //This first for loop is to acces each individual list in list array.
    for(int i = 0; i < sizeOfTable; ++i){
        //SKYLER SEE THIS PLEASE!!! UNCOMMENT THE NEXT LINE,YOU CAN SEE ITS AN ARRAY OF LISTS
        //std::cout<< "Size of index "<< i << " is: " << TableList->size() <<"\n";
        //this second for loop is to iterate through each list that contains a pair
        for(auto it = TableList[i].begin(); it != TableList[i].end(); ++it ){
            //we only output the key (first), second is the word object itself.
            std::cout<<it->first << ' ';
        }
    }
}

template <typename T,typename K>
unsigned int HashTable<T,K> ::  getHashKeyIndex( K& key)
{
    //std hash function,definition
    std::hash<std::string> computeHash;
    /*this temp variable will hold the index
    *where this string belongs too in the array of
    * containers. */
<<<<<<< HEAD
    unsigned int hashedKeyIndex = computeHash(key);
=======
    unsigned hashedKeyIndex = computeHash(key);
>>>>>>> origin
    /*this is used to compute boundries which will
     *  go from 0 - 100,000 */
    hashedKeyIndex = hashedKeyIndex % sizeOfTable;
    //return index
    return hashedKeyIndex;
}

/*Citations:
 * The hash function was used from an example in StackOverflow:
*https://stackoverflow.com/questions/33809770/hash-function-that-can-return-a-integer-range-based-on-string
*/
#endif // HASHTABLE_H
