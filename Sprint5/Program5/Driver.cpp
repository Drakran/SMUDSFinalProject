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
    string terryTest = "Terry";
    string terryTest2 = "terry";


    Word T;
    T.setWord("Terry");
    T.upDateFileAndCount("file1", 1);


    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();

    Tree->insert(T, terryTest);


    try {
        Tree->find(terryTest2);
    } catch (exception &e) {
        //insert object here
        cout << e.what() << endl;
    }

    cout << Tree->find(terryTest).getWord() << endl;

//    srand(time(0));
//    int randNo;
//    for(int i = 0; i < 20; ++i)
//    {
//        randNo = rand()%250 + 1;
//        Tree->insert(randNo);
//    }
    //Tree->printInOrder();
}
