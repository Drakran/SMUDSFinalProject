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

    string terryTest = "terry";
    Word T;
    T.setWord( terryTest );
    T.upDateFileAndCount("file1", 1);
    Tree->insert(T, terryTest);

    string skylerTest = "skyler";
    Word S;
    S.setWord( skylerTest );
    S.upDateFileAndCount("file1", 1);
    Tree->insert(S, skylerTest);

    int two = 2;
    Tree->setTotalNumberOfFiles(two);
    cout << Tree->getTotalNumberOfFiles() << endl;

    Tree->printInOrder();
    delete Tree;
}
