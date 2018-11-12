#include "Driver.h"
#include <iostream>
#include <avltree.h>

/*
 * Sunday November 11
 * 1) Test testing get height function:
    The test will focus on makin sure once the avl reaches imbalance factor
    the flags will be set.
    Ex: When the difference between left subtree of a node and the right is 2
    this will set the flag.
    Comments:
    getHeight, calculates the differences between each subtree without any problem.
    Still working on desctructor/copy constructor.

    2)Test testing rotateLeftLeft function:
    The test will focus on making a left left rotation (CASE 1) on the imbalance tree.
    Ex:                     to

                  10                        10
              5       15                -10       15
         -10                        -20     5
      -20
            Not Balanced                Balanced tree.
    Comments:
    Left left rotations work perfectly!
*/
using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{
    AVLTree<int>Test;
    Test.insert(10);
    Test.insert(5);
    Test.insert(15);
    Test.insert(-10);
    Test.printInOrder();
    cout << "\n";
    Test.insert(-20);
    Test.printInOrder();
    cout << "\n";
    Test.insert(-30);
    Test.printInOrder();
    cout << "\n";
    Test.insert(-40);
    Test.printInOrder();
    cout << "\n";
    Test.insert(-50);
    Test.printInOrder();
    cout << "\n";
    Test.insert(-60);
    Test.printInOrder();
    cout << "\n";


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
