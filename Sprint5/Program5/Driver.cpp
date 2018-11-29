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
    //making a map containing the
    std::map<std::string, int> andDocument;
    //counter for the number of times this words appears.
    int countWord = 0;
    //counter for
    int notWord = 0;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            notWord++;//count number of 'NOT' string
        else
        {
            countWord++;
            //here
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
    //better ui
    std::cout<<'\n';

    //this vector will contain all the words that are in both the documents based on relevancy ranking.
    std::vector<std::string> andDocumentFinal;
    for(auto it : andDocument)
    {
        if(countWord == countWord + notWord)
        {
            if(it.second == countWord)
            {
                //std::cout << "Document satisfying condition is " << it.first << '\n';
                andDocumentFinal.push_back(it.first);
            }
        }
        else{
            if(it.second == countWord - notWord)
            {
                //std::cout << "Document satisfying condition is " << it.first << '\n';
                andDocumentFinal.push_back(it.first);
            }
        }
    }
    //it will ONLY go to the next menu if there is at least one file in the vector
    if(andDocumentFinal.size() > 0){
        //counter to keep track the number of outputs
        int fifteenBegin = 0;
        int fifteenEnd = 14;
        char choice[20];
        //temp string to display 15 outputs at a time
        std::string display15Files = "yes";
        //creating an iterator to keep track of document map on while loop
        std::vector<std::string>::iterator itForDocuFinal  = andDocumentFinal.begin();
        //this will display the first 15 files and ask the user if they want to see more.
        //it(is an iterator of a vector) and will iterate through the document


        while(itForDocuFinal != andDocumentFinal.end() && fifteenBegin < fifteenEnd ){

            std::cout << "Document satisfying condition is " << *itForDocuFinal << '\n';
            //move to next element in vector
            ++itForDocuFinal;
            //increment counter in outputs
            ++fifteenBegin;
            //If there is more than 15 results we will ask the user if they want to see more.
            if( fifteenBegin == fifteenEnd-1 ){
                //ask user if they want to see more results
                std::cout<< "\nWould you like to see more results? \nEnter (y) for yes or (n) for no: ";
                //flushing cin to have clean input
                std::cin.clear();
                //let user enter option
                std::cin>>choice;
                //if the choise is yes we will display more options
                if(choice[0] == 'y'){
                    //increase the size of end to display more options
                    fifteenEnd += 14;
                }else
                    break;
            }
        }

        //ask the user if they want to see a specific document
        std::string LookUpFile = "\0";
        //iterator that does not point anywhere
        std::vector<std::string>::iterator LookUpIt  = andDocumentFinal.end();
        //we will keep on asking the user to enter a valid document
        while(LookUpIt == andDocumentFinal.end() && LookUpFile != "q"){
            //prompt user to enter
            std::cout<<"\nEnter the document name to see the first 300 words.(ex: 12345.json or q to quit): ";
            //flushing cin to have clean input
            std::cin.clear();
            //let user enter option
            std::cin>>LookUpFile;
            //break upon user request
            if(LookUpFile == "q")
                break;
            //iterator to look up the user input
            LookUpIt = find( andDocumentFinal.begin(), andDocumentFinal.end(),LookUpFile);
            if(LookUpIt != andDocumentFinal.end()){
                //temp file path to get the 300 words from file
                Parser penguinTerry;
                penguinTerry.parseOneFile(file, *LookUpIt);
            }
            //it will keep on asking the user to enter the correct file if it did not find word
        }
    }
    //this is to make the UI more clear.
    std::cout<<"\n===================================================================================\n";
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
    //creating a vector to store all files
    std::vector<std::string> orDocumentFinal;
    for(auto it : orDocument)
    {
        if(countWord == countWord + notWord)
        {
            orDocumentFinal.push_back(it.first);
        }
//        else
//        {
//            if(it.second != countWord)
//                std::cout << "Document satisfying condition is " << it.first << '\n';
//        }
    }
    //we will output the next menu ONLY if there is something in the menu
    if( orDocumentFinal.size() > 0){
        //counter to keep track the number of outputs
        int fifteenBegin = 0;
        int fifteenEnd = 14;
        char choice[20];
        //temp string to display 15 outputs at a time
        std::string display15Files = "yes";
        //creating an iterator to keep track of document map on while loop
        std::vector<std::string>::iterator itForDocuFinal  = orDocumentFinal.begin();
        //this will display the first 15 files and ask the user if they want to see more.
        //it(is an iterator of a vector) and will iterate through the document
        while(itForDocuFinal != orDocumentFinal.end() && fifteenBegin < fifteenEnd ){

            std::cout << "Document satisfying condition is " << *itForDocuFinal << '\n';
            //move to next element in vector
            ++itForDocuFinal;
            //increment counter in outputs
            ++fifteenBegin;
            //If there is more than 15 results we will ask the user if they want to see more.
            if( fifteenBegin == fifteenEnd-1 ){
                //ask user if they want to see more results
                std::cout<< "\nWould you like to see more results? \nEnter (y) for yes or (n) for no: ";
                //flushing cin to have clean input
                std::cin.clear();
                //let user enter option
                std::cin>>choice;
                //if the choise is yes we will display more options
                if(choice[0] == 'y'){
                    //increase the size of end to display more options
                    fifteenEnd += 14;
                }else
                    break;
            }
        }

        //ask the user if they want to see a specific document
        std::string LookUpFile = "\0";
        //iterator that does not point anywhere
        std::vector<std::string>::iterator LookUpIt  = orDocumentFinal.end();
        //we will keep on asking the user to enter a valid document
        while(LookUpIt == orDocumentFinal.end() && LookUpFile != "q"){
            //prompt user to enter
            std::cout<<"\nEnter the document name to see the first 300 words.(ex: 12345.json or q to quit): ";
            //flushing cin to have clean input
            std::cin.clear();
            //let user enter option
            std::cin>>LookUpFile;
            //break upon user request
            if(LookUpFile == "q")
                break;
            //iterator to look up the user input
            LookUpIt = find( orDocumentFinal.begin(), orDocumentFinal.end(),LookUpFile);
            if(LookUpIt != orDocumentFinal.end()){
                //temp file path to get the 300 words from file
                Parser penguinTerry;
                penguinTerry.parseOneFile(file, *LookUpIt);
            }
            //it will keep on asking the user to enter the correct file if it did not find word
        }
    }
    //this is to make the UI more clear.
    std::cout<<"\n===================================================================================\n";
}

void Driver::notQueryAVL(std::stringstream& ss)
{
    int countWord = 0;
    countWord++;
    //this map will contain the document the word appears in with number with an int containing the flag(or)
    std::map<std::string, int> document;
    std::cout << "Word is " << wordToFind << '\n';
    Porter2Stemmer::stem(wordToFind); //stem query
    makingStorageAVLTree(); //make Tree
    int count{0};
    //this map will be used to store the relevancy ranking.
    std::map<int, std::string, std::greater<int>> rranking;
    //we will look for the word in the avl tree, if found we will copy the map inside word object
    //to the rranking map that is sorted by the number of times a word appears and the file it appears in.
    try {
        //this iterator will copy the word class map to rranking map sorted by the highsest number of
        //appreances in the map from word class.
        for( auto it : Tree->find(wordToFind).getFileAndCount() )
        {
            //std::cout<< it.first << "\n";//QA purposes
            //pushing pair to rraking map
            rranking.insert(make_pair(it.second, it.first));
            //std::cout << it.first << '\t'; //-- QA purpose to view files in word class map
            //this map contains the names of the files where this word appears
            ++document[it.first];
            //counter to keep track of number of files.
            count++;
        }
    //if it outputs this message the word was not found.
    } catch (std::exception &e ) {
       std::cerr << "The word does not exist in any of the current files." << "\n";
    }
    //This will output the rraking map, it is sorted with highest number of appareaces
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
                for( auto it : Tree->find(wordToFind).getFileAndCount() ){
                    //std::cout << it.first << '\n'; //-- QA purpose
                    if(document.find(it.first) == document.end()){}
                    else
                        ++document[it.first];
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
        }
    }
    /*
    *SKYLER PLEASE CHECK THIS ITERATOR OUT!!!
    * this iterator will output only the files that appear in the first word and
    * not in the second one!!!
    * if we do itForNot == countWord this will display the files where THEY BOTH APPEAR
    * if we do itForNOt!=  will display the files where onnly the first word appears but not second!!
    */
    std::vector<std::string> notDocumentFinal;
    for(auto itForNot : document)
    {
        if(itForNot.second != countWord){
            //std::cout<< "HEREEEE " << it.first << '\n';//QA
            notDocumentFinal.push_back(itForNot.first);
        }
    }
    //making sure the size of the vector is bigger than 0
    if(notDocumentFinal.size() > 0){
        //counter to keep track the number of outputs
        int fifteenBegin = 0;
        int fifteenEnd = 14;
        char choice[20];
        //temp string to display 15 outputs at a time
        std::string display15Files = "yes";
        //creating an iterator to keep track of document map on while loop
        std::vector<std::string>::iterator itForDocuFinal  = notDocumentFinal.begin();
        //this will display the first 15 files and ask the user if they want to see more.
        //it(is an iterator of map) and will iterate through the document
        while(itForDocuFinal != notDocumentFinal.end() && fifteenBegin < fifteenEnd ){

            std::cout << "Document satisfying condition is " << *itForDocuFinal<< '\n';
            //move to next element in map
            ++itForDocuFinal;
            //increment counter in outputs
            ++fifteenBegin;
            //If there is more than 15 results we will ask the user if they want to see more.
            if( fifteenBegin == fifteenEnd-1 ){
                //ask user if they want to see more results
                std::cout<< "\nWould you like to see more results? \nEnter (y) for yes or (n) for no: ";
                //flushing cin to have clean input
                std::cin.clear();
                //let user enter option
                std::cin>>choice;
                //if the choise is yes we will display more options
                if(choice[0] == 'y'){
                    //increase the size of end to display more options
                    fifteenEnd += 14;
                }else
                    break;
            }
        }
        //ask the user if they want to see a specific document
        std::string LookUpFile = "\0";
        //iterator that does not point anywhere
        std::vector<std::string>::iterator LookUpIt  = notDocumentFinal.end();
        //we will keep on asking the user to enter a valid document
        while(LookUpIt == notDocumentFinal.end() && LookUpFile != "q"){
            //prompt user to enter
            std::cout<<"\nEnter the document name to see the first 300 words.(ex: 12345.json or q to quit): ";
            //flushing cin to have clean input
            std::cin.clear();
            //let user enter option
            std::cin>>LookUpFile;
            //break upon user request
            if(LookUpFile == "q")
                break;
            //iterator to look up the user input
            LookUpIt = find( notDocumentFinal.begin(), notDocumentFinal.end(),LookUpFile);
            //word exists
            if( LookUpIt != notDocumentFinal.end() ){
                //temp file path to get the 300 words from file
                Parser penguinTerry;
                penguinTerry.parseOneFile(file, *LookUpIt);
            }
            //if the word cannot be found it will keep on asking the user to input the right choice.
        }
    }
    //this is to make the UI more clear.
    std::cout<<"\n===================================================================================\n";
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
    //This is the word the user will enter
    std::string query;
    //flushing cin to have clean input
    std::cin.ignore();
    //prompt user to enter word they are looking for
    std::cout << "Enter your query: ";
    //readingin the word(s) the user entered.
    getline(std::cin, query);
    //converting string to string stream
    std::stringstream ss(query);
    ss >> wordToFind;
    //checking and/or/not flags, output will vary depending on these flags.
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



