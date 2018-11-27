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
    int filesToTest = 100;

    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < filesToTest; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        //parser.parse(filePath,files[i], *Tree);
        parser.parse(filePath,files[i], *Table);
    }

    //display the size of the data structure
    std::cout<< "Size of hashtable: "<<Table->getSize() << '\n';

    //display all elements in data structure, use it for 400 files or less
    //Table->printInOrder();

    /*
    This is to test the find function in the hashtable
    */
    int counter = 0;
    int counter2 = 0;
    std::string testAdj = "adjudication";
    std::string testSkyler = "Skyler Tran";

//this word exists on the hashtable
    std::cout << "Number of unique documents with " << testAdj << ": ";
    Porter2Stemmer::stem(testAdj);
    try {
        //this iterator is to traverse the map in inside the word object,
        //and keep count of each file inside of map
        for( auto it : Table->find(testAdj).getFileAndCount() ){
            ++counter;
        }
    } catch (std::exception &e ) {
        //if this outputs the word is not in the hashtable
       std::cerr << "\nThe word does not exist in any of the current files." << "\n";
    }
    std::cout << counter << '\n';

//this word does not exists on table
    std::cout << "Number of unique documents with " << testSkyler << ": ";
    try {
        //this iterator is to traverse the map in inside the word object,
        //and keep count of each file inside of map
        for( auto it : Table->find(testSkyler).getFileAndCount() ){
            ++counter2;
        }
    } catch (std::exception &e ) {
        //if this outputs the word is not in the hashtable
       std::cerr << "\nThe word does not exist in any of the current files." << "\n";
    }

    delete Table;
    //delete Tree;


}
