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
#include <porter2_stemmer.h>
class Driver
{
public:
    Driver(std::string);
    ~Driver();
    void Testing();
    void makingStorage();
private:
    std::string file;
    std::string wordToFind;
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
//  IndexInterface<Word, std::string>* HashTable = new HashTable<Word, std::string>();

};

#endif // DRIVER_H
