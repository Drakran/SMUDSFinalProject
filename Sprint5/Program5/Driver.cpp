#include "Driver.h"
#include "r_ranking.h"
#include <iostream>
#include <IndexInterface.h>
#include <random>
#include <stdexcept>
#include <exception>
#include <porter2_stemmer.h>


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
//    //this will be the word we look for in avl tree
//    wordToFind = wordFind;

}

Driver::~Driver()
{
    delete Tree;
}

void Driver::makingStorage()
{
    std::string extention = ".json";
    Parser parser = Parser();
    std::string delimiter = "/";
    std::string filePath;

    std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
    //3) the vector named files has all of files in the folder.
    //std::cerr << "Total number of files in folder: " << files.size() << std::endl;

    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < 100; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        parser.parse(filePath,files[i], *Tree);
    }
}

void Driver::andQuery(std::stringstream & ss)
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
            makingStorage(); //make Tree
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

void Driver::orQuery(std::stringstream & ss)
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
            makingStorage(); //make Tree
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

void Driver::notQuery(std::stringstream& ss)
{
    int countWord = 0;
    countWord++;
    std::map<std::string, int> document;
    std::cout << "Word is " << wordToFind << '\n';
    Porter2Stemmer::stem(wordToFind); //stem query
    makingStorage(); //make Tree
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

void Driver :: Testing()
{
    std::string query;
    std::cin.ignore();
    std::cout << "Enter your query: ";
    getline(std::cin, query);
    std::string wordToFind = query;
    std::stringstream ss(query);
    ss >> wordToFind;
    if(wordToFind == "AND" || wordToFind == "And" || wordToFind == "and")
    {
        andQuery(ss);
    }

    else if(wordToFind == "OR" || wordToFind == "or" || wordToFind == "Or")
    {
        orQuery(ss);
    }

    else
    {
        notQuery(ss);
    }
}
