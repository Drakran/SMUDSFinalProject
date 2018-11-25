#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <avltree.h>
#include <hashtable.h>
#include <parser.h>
#include <exception>
#include <IndexInterface.h>
#include <random>
#include <stdexcept>
#include <porter2_stemmer.h>
class Driver
{
public:
    Driver(std::string,std::string);
    void Testing();
private:
    std::string file;
    std::string wordToFind;

};

#endif // DRIVER_H
