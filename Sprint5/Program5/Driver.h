#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <avltree.h>
#include <parser.h>
#include <exception>
#include <IndexInterface.h>
#include <random>
#include <thread>
#include <stdexcept>
#include "hashtable.h"
#include <porter2_stemmer.h>
class Driver
{
public:
    Driver(std::string);
    ~Driver();
    void TestingWithAVLTree();
    void TestingWithHashTable();
    void makingStorageAVLTree();
    void makingStorageHashTable();
    void andQueryAVL(std::stringstream&);
    void orQueryAVL(std::stringstream&);
    void notQueryAVL(std::stringstream&);
    void andQueryHT(std::stringstream&);
    void orQueryHT(std::stringstream&);
    void notQueryHT(std::stringstream&);
private:
    std::string file;
    std::string wordToFind;
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
    IndexInterface<Word, std::string>* Table = new HashTable<Word, std::string>();
};

#endif // DRIVER_H
