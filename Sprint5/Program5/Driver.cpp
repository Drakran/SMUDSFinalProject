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
Driver::Driver(std::string fileName, std::string wordFind)
{
    //this is the name of the directory where all of the files are found.
    file = fileName;
    //this will be the word we look for in avl tree
    wordToFind = wordFind;
}

void Driver :: Testing()
{
    std::string wordDisplayed = wordToFind;
    IndexInterface<Word, std::string>* Tree = new AVLTree<Word, std::string>();
    std::stringstream ss(wordDisplayed);
    std::map<std::string, int> andDocument;
    ss >> wordToFind;
    if(wordToFind == "AND")
    {
        while(ss >> wordToFind)
        {
            Porter2Stemmer::stem(wordToFind); //stem query
            std::string extention = ".json";
            Parser parser = Parser();
            std::string delimiter = "/";
            std::string filePath;

            std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
            //3) the vector named files has all of files in the folder.
            std::cerr << "Total number of files in folder: " << files.size() << std::endl;

            //To test different number of files
            //int filesToTest = file.size();

            //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
            for(unsigned i = 0; i < 100; ++i)
            {
                //filepath contains the name of each file (77000 files).
                filePath = file + delimiter + files[i];
                parser.parse(filePath,files[i], *Tree);
            }


            //4) Number of unique documents with adjudication. ( map.size() )
            int count{0};
            std::map<int, std::string, std::greater<int>> rranking;
            std::map<int, std::string, std::greater<int>>::iterator it;

            try {
                for( auto it : Tree->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    std::cout << it.first << '\n';
                    count++;
                    ++andDocument[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
            for(auto it : rranking)
            {
                std::cout << "Most appear in " << (it).second << " with " <<
                             (it).first << " instances." << std::endl;
            }
        }
        for(auto it : andDocument)
        {
            if(it.second == 2)
                std::cout << "Document satisfying condition is " <<
                             it.first << '\n';
        }
    }

    else if(wordToFind == "OR")
    {
        Porter2Stemmer::stem(wordToFind); //stem query
        std::string extention = ".json";
        Parser parser = Parser();
        std::string delimiter = "/";
        std::string filePath;

        std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
        //3) the vector named files has all of files in the folder.
        std::cerr << "Total number of files in folder: " << files.size() << std::endl;

        //To test different number of files
        //int filesToTest = file.size();

        //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
        for(unsigned i = 0; i < 100; ++i)
        {
            //filepath contains the name of each file (77000 files).
            filePath = file + delimiter + files[i];
            parser.parse(filePath,files[i], *Tree);
        }


        //4) Number of unique documents with adjudication. ( map.size() )
        int count{0};
        std::map<int, std::string, std::greater<int>> rranking;
        std::map<int, std::string, std::greater<int>>::iterator it;

        try {
            for( auto it : Tree->find(wordToFind).getFileAndCount() ){
                rranking.insert(make_pair(it.second, it.first));
                //std::cout << "Word is " << it.first << " Number of appearance: ";
                //std::cout << it.second << std::endl;
                count++;
            }
        } catch (std::exception &e ) {
           std::cerr << "The word does not exist in any of the current files." << "\n";
        }
        it = rranking.begin();
        for(int i = 0; i < rranking.size(); i++)
        {
            std::cout << "Most appear in " << (*it).second << " with " <<
                         (*it).first << " instances." << std::endl;
            it++;
        }
        //1) Number of Words Parsed.(  counter of each instance of an object )
        std::cout << "Number of Words Parsed: " << parser.getOverallWordTotal() << std::endl;
        //2) Number of Unique words (Tree Nodes).( Tree->getSize() ) check
        std::cout << "Number of Unique words (Tree Nodes): " << Tree->getSize() << "\n";
        std::cout << "Total number of documents parsed: " << files.size() << '\n';
        std::cout << "Number of unique documents with " << wordDisplayed << " is: " << count << '\n';
    }
    delete Tree;
}
