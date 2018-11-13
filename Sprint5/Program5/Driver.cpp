#include "Driver.h"
#include <iostream>
#include <avltree.h>

using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{
    AVLTree<int>Test;
    for(int i = 0; i < 65; ++i){
        Test.insert(i);
    }
    Test.printInOrder();

}
