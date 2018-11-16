#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <avltree.h>
#include <parser.h>
#include <exception>

class Driver
{
public:
    Driver(std::string,std::string);
    void Testing();
private:
    std::string file;
    std::string word;

};

#endif // DRIVER_H
