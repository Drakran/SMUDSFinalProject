#include "Driver.h"
#include <iostream>
#include <IndexInterface.h>
#include <random>

using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();

    string terryTest = "Terry";
    Word T;
    T.setWord( terryTest );
    T.upDateFileAndCount("file1", 1);
    Tree->insert(T, terryTest);

    string teTest = "Te";
    Word te;
    te.setWord( teTest );
    te.upDateFileAndCount("file111", 10);
    Tree->insert(te, teTest);


    string erryTest = "erry";
    Word e;
    e.setWord( erryTest );
    e.upDateFileAndCount("file1121", 90);
    Tree->insert(e, erryTest);

    cout << Tree->find(terryTest) << endl;



//    srand(time(0));
//    int randNo;
//    for(int i = 0; i < 20; ++i)
//    {
//        randNo = rand()%250 + 1;
//        Tree->insert(randNo);
//    }
    //Tree->printInOrder();
}
