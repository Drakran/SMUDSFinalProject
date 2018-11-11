#include "Driver.h"
#include <iostream>
#include <avltree.h>

using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{
    /*1) Test testing getHeight function:
        The test will focus on makin sure once the avl reaches imbalance factor
        the flags will be set.
        Ex: When the difference between left subtree of a node and the right is 2
        this will set the flag.
    */
    AVLTree<int>Test;
    Test.insert(10);
    Test.insert(5);
    Test.insert(15);
/*********************
 * case 1: LL
//    Test.insert(-10);
//    Test.insert(-20);
//    Test.printInOrder();
//                10
//            5       15
//      -10
//  -20
*********************/

///*********************
// * case 2: LR
//     Test.insert(7);
//    Test.insert(9);
//    Test.printInOrder();
//                10
//            5       15
//              7
//                 9
//*********************/

///*********************
// * case 3: RL
//    Test.insert(14);
//    Test.insert(13);
//    Test.printInOrder();
//                10
//            5       15
//                  14
//                13
//*********************/

///*********************
// * case 4: RR
//    Test.insert(17);
//    Test.insert(19);
//    Test.printInOrder();
//                10
//            5       15
//                      17
//                         19
//*********************/

}
