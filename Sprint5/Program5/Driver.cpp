#include "Driver.h"
#include <iostream>
#include <IndexInterface.h>
#include <random>

using namespace std;
//to check time:
//cd Desktop/CSE....../Sprint5/build...../
// time ./Program5 /home/student/Desktop/scotus <a single word>
Driver::Driver(std::string fileName, std::string wordFind)
{
    file = fileName;
    word = wordFind;
}

void Driver :: Testing()
{
    string extention = ".json";
    Parser parser;
    std::string delimiter = "/";
    std::string filePath;
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
    vector<string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
 ////comment out this cout otherwise you see the name of each file (77000 files).
    cerr << files.size() << endl;
    for(unsigned i = 0; i < 2; i++)
    {
        filePath = file + delimiter + files[i];
        parser.parse(filePath,files[i], *Tree);
    }
    //std::cout << argv[1];

//    string terryTest = "terry";
//    Word T;
//    T.setWord( terryTest );
//    T.upDateFileAndCount("file1", 1);
//    Tree->insert(T, terryTest);

//    string skylerTest = "skyler";
//    Word S;
//    S.setWord( skylerTest );
//    S.upDateFileAndCount("file1", 1);
//    Tree->insert(S, skylerTest);

    Tree->printInOrder();
    cout << "\nNumber of words in the tree: " << Tree->getSize() <<endl;
    delete Tree;
}
