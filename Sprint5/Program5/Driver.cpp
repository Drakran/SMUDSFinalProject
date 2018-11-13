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
    for(int i = 0; i < 15; ++i){
        Test.insert(i);
    }
    cout << Test.contains(0) << endl;
    cout << Test.contains(14) << endl;

    //Test.printInOrder();

}
