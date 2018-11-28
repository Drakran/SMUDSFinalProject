#include "Driver.h"
#include "r_ranking.h"
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
Driver::Driver(std::string fileName)
{
    //this is the name of the directory where all of the files are found.
    file = fileName;
    //number of files to index
    filesToIndex = 400;
}

Driver::~Driver()
{
    delete Tree;
    delete Table;
}

void Driver::makingStorageAVLTree()
{

    std::string extention = ".json";
    Parser parser = Parser();
    std::string delimiter = "/";
    std::string filePath;

    std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
    //3) the vector named files has all of files in the folder.
    //std::cerr << "Total number of files in folder: " << files.size() << std::endl;

    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < filesToIndex; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        parser.parse(filePath,files[i], *Tree);
    }
}

void Driver::makingStorageHashTable()
{
    std::string extention = ".json";
    Parser parser = Parser();
    std::string delimiter = "/";
    std::string filePath;

    std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
    //3) the vector named files has all of files in the folder.
    //std::cerr << "Total number of files in folder: " << files.size() << std::endl;

    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < filesToIndex; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        parser.parse(filePath,files[i], *Table);
    }
}

void Driver::andQueryAVL(std::stringstream & ss)
{
    std::map<std::string, int> andDocument;
    int countWord = 0;
    int notWord = 0;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            notWord++;//count number of 'NOT' string
        else
        {
            countWord++;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            makingStorageAVLTree(); //make Tree
            int count = 0;
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : Tree->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; -- QA purpose
                    count++;
                    ++andDocument[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : rranking)
            {
                if(it == *rranking.begin())
                    std::cout << "Most appear in ";
                std::cout << (it).second << "(" << (it).first << " instances)/";
            }
            std::cout << '\n';
        }
    }
    for(auto it : andDocument)
    {
        if(countWord == countWord + notWord)
        {
            if(it.second == countWord)
                std::cout << "Document satisfying condition is " << it.first << '\n';
        }
        else
            if(it.second == countWord - notWord)
                std::cout << "Document satisfying condition is " << it.first << '\n';
    }
}

void Driver::orQueryAVL(std::stringstream & ss)
{
    std::map<std::string, int> orDocument;
    int countWord = 0;
    int notWord = 0;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            notWord++;
        else
        {
            countWord++;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            makingStorageAVLTree(); //make Tree
            int count{0};
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : Tree->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; -- QA purpose
                    count++;
                    ++orDocument[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : rranking)
            {
                if(it == *rranking.begin())
                    std::cout << "Most appear in ";
                std::cout << (it).second << "(" << (it).first << " instances)/";
            }
            std::cout << '\n';
        }
    }
    for(auto it : orDocument)
    {
        if(countWord == countWord + notWord)
            std::cout << "Document satisfying condition is " << it.first << '\n';
//        else
//        {
//            if(it.second != countWord)
//                std::cout << "Document satisfying condition is " << it.first << '\n';
//        }
    }
}

void Driver::notQueryAVL(std::stringstream& ss)
{
    int countWord = 0;
    countWord++;
    std::map<std::string, int> document;
    std::cout << "Word is " << wordToFind << '\n';
    Porter2Stemmer::stem(wordToFind); //stem query
    makingStorageAVLTree(); //make Tree
    int count{0};
    std::map<int, std::string, std::greater<int>> rranking;
    try {
        for( auto it : Tree->find(wordToFind).getFileAndCount() )
        {
            rranking.insert(make_pair(it.second, it.first));
            std::cout << it.first << '\n'; //-- QA purpose
            ++document[it.first];
            count++;
        }
    } catch (std::exception &e ) {
       std::cerr << "The word does not exist in any of the current files." << "\n";
    }
    for(auto it : rranking)
    {
        if(it == *rranking.begin())
            std::cout << "Most appear in ";
        std::cout << (it).second << "(" << (it).first << " instances)/";
    }
    std::cout << '\n';
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
        {
            countWord++;
            ss >> wordToFind;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            try {
                for( auto it : Tree->find(wordToFind).getFileAndCount() )
                {
                    //std::cout << it.first << '\n'; //-- QA purpose
                    if(document.find(it.first) == document.end()){}
                    else
                        ++document[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : document)
                if(it.second == countWord - 1)
                    std::cout << "Document satisfying condition is " << it.first << '\n';
        }
    }
}

void Driver::andQueryHT(std::stringstream & ss)
{
    std::map<std::string, int> andDocument;
    int countWord = 0;
    int notWord = 0;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            notWord++;
        else
        {
            countWord++;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            makingStorageHashTable(); //make Tree
            int count = 0;
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : Table->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; -- QA purpose
                    count++;
                    ++andDocument[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : rranking)
            {
                if(it == *rranking.begin())
                    std::cout << "Most appear in ";
                std::cout << (it).second << "(" << (it).first << " instances)/";
            }
            std::cout << '\n';
        }
    }
    for(auto it : andDocument)
    {
        if(countWord == countWord + notWord)
        {
            if(it.second == countWord)
                std::cout << "Document satisfying condition is " << it.first << '\n';
        }
        else
            if(it.second == countWord - notWord)
                std::cout << "Document satisfying condition is " << it.first << '\n';
    }
}

void Driver::orQueryHT(std::stringstream & ss)
{
    std::map<std::string, int> orDocument;
    int countWord = 0;
    int notWord = 0;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            notWord++;
        else
        {
            countWord++;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            makingStorageHashTable(); //make Tree
            int count{0};
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : Table->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; -- QA purpose
                    count++;
                    ++orDocument[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : rranking)
            {
                if(it == *rranking.begin())
                    std::cout << "Most appear in ";
                std::cout << (it).second << "(" << (it).first << " instances)/";
            }
            std::cout << '\n';
        }
    }
    for(auto it : orDocument)
    {
        if(countWord == countWord + notWord)
            std::cout << "Document satisfying condition is " << it.first << '\n';
//        else
//        {
//            if(it.second != countWord)
//                std::cout << "Document satisfying condition is " << it.first << '\n';
//        }
    }
}

void Driver::notQueryHT(std::stringstream& ss)
{
    int countWord = 0;
    countWord++;
    std::map<std::string, int> document;
    std::cout << "Word is " << wordToFind << '\n';
    Porter2Stemmer::stem(wordToFind); //stem query
    makingStorageHashTable(); //make HashTable
    int count{0};
    std::map<int, std::string, std::greater<int>> rranking;
    try {
        for( auto it : Table->find(wordToFind).getFileAndCount() )
        {
            rranking.insert(make_pair(it.second, it.first));
            std::cout << it.first << '\n'; //-- QA purpose
            ++document[it.first];
            count++;
        }
    } catch (std::exception &e ) {
       std::cerr << "The word does not exist in any of the current files." << "\n";
    }
    for(auto it : rranking)
    {
        if(it == *rranking.begin())
            std::cout << "Most appear in ";
        std::cout << (it).second << "(" << (it).first << " instances)/";
    }
    std::cout << '\n';
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
        {
            countWord++;
            ss >> wordToFind;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            try {
                for( auto it : Table->find(wordToFind).getFileAndCount() )
                {
                    //std::cout << it.first << '\n'; //-- QA purpose
                    if(document.find(it.first) == document.end()){}
                    else
                        ++document[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : document)
                if(it.second == countWord - 1)
                    std::cout << "Document satisfying condition is " << it.first << '\n';
        }
    }
}

void Driver :: TestingWithAVLTree()
{
    std::string query;
    std::cin.ignore();
    std::cout << "Enter your query: ";
    getline(std::cin, query);
    std::stringstream ss(query);
    ss >> wordToFind;
    if(wordToFind == "AND" || wordToFind == "And" || wordToFind == "and")
        andQueryAVL(ss);
    else if(wordToFind == "OR" || wordToFind == "or" || wordToFind == "Or")
        orQueryAVL(ss);
    else
        notQueryAVL(ss);
}

void Driver :: TestingWithHashTable()
{
//        makingStorageHashTable();
//        //display the size of the data structure
//        std::cout<< "Size of hashtable: "<<Table->getSize() << '\n';

//        //display all elements in data structure, use it for 400 files or less
//        //Table->printInOrder();

//        /*
//        This is to test the find function in the hashtable
//        */
//        int counter = 0;
//        int counter2 = 0;
//        std::string testAdj = "adjudication";
//        std::string testSkyler = "Skyler Tran";

//        //this word exists on the hashtable
//        std::cout << "Number of unique documents with " << testAdj << ": ";
//        Porter2Stemmer::stem(testAdj);
//        try {
//            //this iterator is to traverse the map in inside the word object,
//            //and keep count of each file inside of map
//            for( auto it : Table->find(testAdj).getFileAndCount() ){
//                ++counter;
//            }
//        } catch (std::exception &e ) {
//            //if this outputs the word is not in the hashtable
//           std::cerr << "\nThe word does not exist in any of the current files." << "\n";
//        }
//        std::cout << counter << '\n';

//    //this word does not exists on table
//        std::cout << "Number of unique documents with " << testSkyler << ": ";
//        try {
//            //this iterator is to traverse the map in inside the word object,
//            //and keep count of each file inside of map
//            for( auto it : Table->find(testSkyler).getFileAndCount() ){
//                ++counter2;
//            }
//        } catch (std::exception &e ) {
//            //if this outputs the word is not in the hashtable
//           std::cerr << "\nThe word does not exist in any of the current files." << "\n";
//        }

        std::string query;
        std::cin.ignore();
        std::cout << "Enter your query: ";
        getline(std::cin, query);
        std::stringstream ss(query);
        ss >> wordToFind;
        if(wordToFind == "AND" || wordToFind == "And" || wordToFind == "and")
            andQueryHT(ss);
        else if(wordToFind == "OR" || wordToFind == "or" || wordToFind == "Or")
            orQueryHT(ss);
        else
            notQueryHT(ss);
}

void Driver::basicStat()
{
    double avgWord;
    int counter = 0;
    if(Table->getSize() > 1)
    {
        std::cout << "Total opinions indexed: " << filesToIndex << '\n';
        avgWord = Table->getSize() / filesToIndex;
        std::cout << "Average words per opinion: " << avgWord << '\n';
        for(auto it : Table->top50Common())
        {
            counter++;
            if(counter == 50)
                break;
            std::cout << it.second << " ";
            std::cout << it.first << '\n';
        }
    }
    else if(Tree->getSize() > 1)
    {
        std::cout << "Total opinions indexed: " << filesToIndex << '\n';
        avgWord = Tree->getSize() / filesToIndex;
        std::cout << "Average words per opinion: " << avgWord << '\n';
        for(auto it : Tree->top50Common())
        {
            counter++;
            if(counter == 50)
                break;
            std::cout << it.second << " ";
            std::cout << it.first << '\n';
        }
    }
    else
        std::cout << "No data structure has been initialized!!!\n";

}



