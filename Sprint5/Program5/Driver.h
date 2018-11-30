#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <avltree.h>
#include <hashtable.h>
#include <parser.h>
#include <exception>
#include <IndexInterface.h>
#include <random>
#include <thread>
#include <stdexcept>
#include "hashtable.h"
#include <porter2_stemmer.h>
#include <vector>

class Driver
{
public:
    Driver(std::string);
    ~Driver();
    void userInterface();
    void TestingWithAVLTree();
    void TestingWithHashTable();
    void makingStorage(IndexInterface<Word, std::string>*& dataStructure);
    void andQuery(std::stringstream&, IndexInterface<Word, std::string>*& dataStructure);
    void notQuery(std::stringstream&, IndexInterface<Word, std::string>*& dataStructure);
    void orQuery(std::stringstream&, IndexInterface<Word, std::string>*& dataStructure);
    void basicStat();
    void stat(IndexInterface<Word, std::string>*& dataStructure);

private:
    std::string file;
    int filesToIndex;
    std::string wordToFind;
    unsigned long totalWords;
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
    IndexInterface<Word, std::string>* Table = new HashTable<Word, std::string>();
    std:: vector<std::string> filePathsVec;
};

#endif // DRIVER_H
