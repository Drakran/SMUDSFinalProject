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
    Comments:
    Left left rotations work perfectly! Still need to work on copy constructor and destructor.

    3)Test testing rotateRightRight function:
    Comments:
    Testing both rightright and leftleft functions at the same time: both work

    4) RightLeft and Left Right functions both work at the same time.

    5) Rule of three works completely!
    Comments:
    Insert functions work perfectly.
    Rule of three works perfectly.
    Rotations work perfectly.

    -Approved by Terry. (Note signature maybe forged.)

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
    Test.insert(0);
    Test.insert(-5);
    Test.insert(25);
    Test.insert(30);
    AVLTree<int>Test1 = Test;
    Test1.printInOrder();
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

/*
 *1)convert to this
            10
        9       15
    7
 5
 2) do left left
*/



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
