#include "Driver.h"
#include <iostream>
#include <avltree.h>
#include <hashtable.h>
#include <IndexInterface.h>
#include <random>
#include <stdexcept>
#include <exception>
#include <porter2_stemmer.h>
#include <set>
#include<functional>


//1) Number of Words Parsed.                        (  counter of each instance of an object )
//2) Number of Unique words (Tree Nodes).           ( Tree->getSize() )
//3) Number of documents parsed.                    ( counter of documents parsed.)
//4) Number of unique documents with adjudication.  ( map.size() )


//to check time:
//cd Desktop/CSE....../Sprint5/build...../
// time ./Program5 /home/student/Desktop/scotus <wordToFind>
Driver::Driver(std::string fileName, std::string wordFind)
{
    //this is the name of the directory where all of the files are found.
    file = fileName;
    //this will be the word we look for in avl tree
    wordToFind = wordFind;
}

void Driver :: Testing()
{
    std::string extention = ".json";
    Parser parser;
    std::string delimiter = "/";
    std::string filePath;

    //IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
    IndexInterface<Word, std::string>* Table = new HashTable<Word, std::string>();

    std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
    //3) the vector named files has all of files in the folder.
    std::cerr << "Total number of files in folder: " << files.size() << std::endl;

    //To test different number of files
    int filesToTest = 5;

    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < filesToTest; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        //parser.parse(filePath,files[i], *Tree);
        parser.parse(filePath,files[i], *Table);
    }

/*
    std::cout<< "----------------------------------------\nTests:\n";
    // TESTS FOR FIND FUNCTION
    std::string tempS = "expand";
    std::string tempS2 = "Sklyer Tran";
    //This tests with something that exists in hashtable
    std::cout<<"Inside test, this word exists: \t"<< Table->find(tempS).getWord()<< '\n';
    //This tests with something that does not exists in hashtable
    try {
       Table->find(tempS2).getWord();
    } catch (std::exception& e) {
        std::cout<<"This key does not have an object in the hashtable: \n" << e.what() << '\n';
    }

    //TESTS FOR COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR
    IndexInterface<Word, std::string>* TableTest = new HashTable<Word, std::string>();
    TableTest = Table;
    TableTest->printInOrder();

    IndexInterface<Word, std::string>* TableTest2(Table); //= new HashTable<Word, std::string>();
    TableTest2->printInOrder();
    std::cout<< "\n----------------------------------------\n";
*/

    //tests for subscript operator
    std::cout<< "----------------------------------------\nTests:\n";
    std::string tempS = "expand";
    //trying to get the size of the map where the word is stored.
    //this function returns an object by using a key.
    std::cout<< "Number of appreances of expand: " <<Table->operator[](tempS).getFileAndCount().size() <<'\n';

    //testing for something not on the table
    std::string tempS2 = "skyler tran";
    try {
        //trying to get the size of the map where the word is stored.
        int i = Table->operator[](tempS2).getFileAndCount().size() <<'\n';
    }catch(std::exception &e){
        std::cout<< "Skyler Tran does not exist on hashtable.\n";
    }
    std::cout<< "----------------------------------------";


    //display the size of the data structure
    std::cout<< "\nSize of hashtable: "<<Table->getSize() << '\n';
    //display all elements in data structure
    Table->printInOrder();
    delete Table;
    //delete Tree;


}
