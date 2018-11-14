#include "Driver.h"
#include <iostream>
#include <avltree.h>
#include <random>
using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{
    AVLTree<int>Test;
    srand(time(0));
    int randNo;
    for(int i = 0; i < 100; ++i)
    {
        randNo = rand()%250 + 1;
        Test.insert(randNo);
    }
    Test.printInOrder();
}
