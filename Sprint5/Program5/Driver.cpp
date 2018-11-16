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

    Tree->printInOrder();
    delete Tree;
}
