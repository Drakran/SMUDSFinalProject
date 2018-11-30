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

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

Driver::Driver(std::string fileName)
{
    //this is the name of the directory where all of the files are found.
    file = fileName;
    //number of files to index
    filesToIndex = 20;
    totalWords = 0;
}

Driver::~Driver()
{
    delete Tree;
    delete Table;
}

void Driver::makingStorage(IndexInterface<Word, std::string>*& dataStructure)
{
    std::string extention = ".json";
    Parser parser = Parser();
    std::string delimiter = "/";
    std::string filePath;

    std::vector<std::string> files = parser.getFiles(file, extention);    //this will output all of files in format of: numberOfFile.json
    //3) the vector named files has all of files in the folder.
    //std::cerr << "Total number of files in folder: " << files.size() << std::endl;
    filesToIndex = 20;
    //start at 0 to filesToTest = (custom # of files) or filesToTest = files.size() all files in folder.
    for(unsigned i = 0; i < filesToIndex; ++i)
    {
        //filepath contains the name of each file (77000 files).
        filePath = file + delimiter + files[i];
        if(filesToIndex <= 100)
        {
            if(i % 51 == 0)
                std::cout << "Be patient please...\n";
        }
        else if(filesToIndex <= 1001 && filesToIndex > 101)
        {
            if(i % 450 == 0)
                std::cout << "Be patient please...\n";
        }
        else if(filesToIndex <= 10001 && filesToIndex > 1001)
        {
            if(i % 1001 == 0)
                std::cout << "Be patient please...\n";
        }
        else if(filesToIndex <= 40001 && filesToIndex > 10001)
        {
            if(i % 10001 == 0)
                std::cout << "Be patient please...\n";
        }
        else if(filesToIndex <= files.size() && filesToIndex > 40001)
        {
            if(i % 15001 == 0)
                std::cout << "Be patient please...\n";
        }
        parser.parse(filePath,files[i], *dataStructure);
    }
    totalWords = parser.getOverallWordTotal();
}

void Driver::andQuery(std::stringstream& ss, IndexInterface<Word, std::string>*& dataStructure)
{
    //making a map containing the
    std::map<std::string, int> andDocument;
    //counter for the number of times this words appears.
    int countWord = 0;
    int flag = 100; //use for "NOT"
    //counter for
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
        {
            ss >> wordToFind;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            try {
                for( auto it : dataStructure->find(wordToFind).getFileAndCount() )
                {
                    //std::cout << it.first << '\n'; //-- QA purpose
                   andDocument.find(it.first)->second = flag;
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
        }
        else
        {
            countWord++;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : dataStructure->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; -- QA purpose
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
        if(it.second != flag)
        {
            if(it.second == countWord)
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

void Driver::orQuery(std::stringstream& ss, IndexInterface<Word, std::string>*& dataStructure)
{
    std::map<std::string, int> orDocument;
    int flag = 100;
    while(ss >> wordToFind)
    {
        if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
        {
            ss >> wordToFind;
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            try {
                for( auto it : dataStructure->find(wordToFind).getFileAndCount() )
                {
                    //std::cout << it.first << '\n'; //-- QA purpose
                    orDocument.find(it.first)->second = flag;
                }
            } catch (std::exception &e ) {
               std::cerr << "The word does not exist in any of the current files." << "\n";
            }
        }
        else
        {
            std::cout << "Word is " << wordToFind << '\n';
            Porter2Stemmer::stem(wordToFind); //stem query
            int count{0};
            std::map<int, std::string, std::greater<int>> rranking;
            try {
                for( auto it : dataStructure->find(wordToFind).getFileAndCount() )
                {
                    rranking.insert(make_pair(it.second, it.first));
                    //std::cout << it.first << '\n'; //-- QA purpose
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
        if(it.second != flag)
        {
            orDocumentFinal.push_back(it.first);
        }
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

void Driver::notQuery(std::stringstream& ss, IndexInterface<Word, std::string>*& dataStructure)
{
    std::string test_ = wordToFind;
    int flag = 100;
    //this map will contain the document the word appears in with number with an int containing the flag(or)
    std::map<std::string, int> document;
    std::cout << "Word is " << wordToFind << '\n';
    Porter2Stemmer::stem(wordToFind); //stem query
    int count{0};
    //this map will be used to store the relevancy ranking.
    std::map<int, std::string, std::greater<int>> rranking;
    //we will look for the word in the avl tree, if found we will copy the map inside word object
    //to the rranking map that is sorted by the number of times a word appears and the file it appears in.
    try {
        //this iterator will copy the word class map to rranking map sorted by the highsest number of
        //appreances in the map from word class.
        for( auto it : dataStructure->find(wordToFind).getFileAndCount() )
        {
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
    if(ss.str() != test_)
    {
        while(ss >> wordToFind)
        {
            if(wordToFind == "NOT" || wordToFind == "not" || wordToFind == "Not")
            {
                ss >> wordToFind;
                std::cout << "Word is " << wordToFind << '\n';
                Porter2Stemmer::stem(wordToFind); //stem query
                try {
                    for( auto it : dataStructure->find(wordToFind).getFileAndCount() ){
                        //std::cout << it.first << '\n'; //-- QA purpose
                        //if(document.find(it.first) == document.end()){}
                        document.find(it.first)->second = flag;
                    }
                } catch (std::exception &e ) {
                   std::cerr << "The word does not exist in any of the current files." << "\n";
                }
            }
        }
    }
    /*
     * Skyler has fixed this!!! Ignore the rest of the comment.
    *SKYLER PLEASE CHECK THIS ITERATOR OUT!!!
    * this iterator will output only the files that appear in the first word and
    * not in the second one!!!
    * if we do itForNot == countWord this will display the files where THEY BOTH APPEAR
    * if we do itForNOt!=  will display the files where onnly the first word appears but not second!!
    */
    std::vector<std::string> notDocumentFinal;
    for(auto itForNot : document)
    {
        if(itForNot.second != flag){
            //std::cout<< "HEREEEE " << itForNot.first << '\n';//QA
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

void Driver::basicStat()
{
    if(Table->getSize() > 1)
        stat(Table);
    else if(Tree->getSize() > 1)
        stat(Tree);
    else
        std::cout << "No data structure has been initialized!!!\n";
}

void Driver::stat(IndexInterface<Word, std::string>*& dataStructure)
{
    double avgWord;
    int counter = 0;
    std::cout << "Total opinions indexed: " << filesToIndex << '\n';
    avgWord = totalWords / filesToIndex;
    std::cout << "Average words per opinion: " << avgWord << '\n';
    std::cout << "Top 50 Common Words: \n";
    /*
     * These stats don't match
     * AVL >><< HashTable
     * NO GOOD!!
     *
     */
    for(auto it : dataStructure->top50Common())
    {
        counter++;
        if(counter == 50)
            break;
        std::cout << it.second << " ";
        std::cout << it.first << '\n';
    }
    std::cout << "Total Words by case number: \n";
    for(auto it : dataStructure->getTotalWordsEachCase())
    {
        std::cout << it.first << " ";
        std::cout << it.second << '\n';
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
        andQuery(ss, Tree);
    else if(wordToFind == "OR" || wordToFind == "or" || wordToFind == "Or")
        orQuery(ss, Tree);
    else
        notQuery(ss, Tree);
}

void Driver :: TestingWithHashTable()
{
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
            andQuery(ss, Table);
        else if(wordToFind == "OR" || wordToFind == "or" || wordToFind == "Or")
            orQuery(ss, Table);
        else
            notQuery(ss, Table);
}

void Driver::userInterface()
{
    bool condition = true;
    char choice[20];
    int counter_Tree = 0;
    int counter_Hash = 0;
    while(condition)
    {
        std::cout << "Choose an option: \n1. Maintenance mode\n2. Interactive mode\n3. Beast mode\n0. Quit\n";
        std::cin >> choice;
        if(choice[0] == '1')
        {
            char choiceMaintenance[20];
            bool conditionMaintenance = true;
            std::cout<<"Entering maintenance mode....\n";
            while(conditionMaintenance)
            {
                std::cout<<"╔╦╗┌─┐┬┌┐┌┌┬┐┌─┐┌┐┌┌─┐┌┐┌┌─┐┌─┐\n";
                std::cout<<"║║║├─┤││││ │ ├┤ │││├─┤││││  ├┤ \n";
                std::cout<<"╩ ╩┴ ┴┴┘└┘ ┴ └─┘┘└┘┴ ┴┘└┘└─┘└─┘\n";
                std::cout << "Choose an option: \n1. Add opinions \n2. Clear index\n0. Back\n";
                std::cin >> choiceMaintenance;
                std::string path;
                if(choiceMaintenance[0] == '1')
                {
                    std::cin.ignore(); //path currently = /home/student/Desktop/scotus
                    std::cout<<"Enter path: " ;
                    std::cin>>path;
                    //Update index from new opinions goes here




                }
                if(choiceMaintenance[0] == '2')
                {
                    //Clear index goes here
                    //Delete .txt file
                }
                if(choiceMaintenance[0] == '0')
                {
                    std::cout<<"Exiting maintenance mode...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    conditionMaintenance = false;
                }
            }
        }
        if(choice[0] == '2')
        {
            std::cout<<"Entering interactive mode...\n";
            char choiceMaintenance[20];
            bool conditionInteractive = true;
            while(conditionInteractive)
            {
                std::cout<<"╦┌┐┌┌┬┐┌─┐┬─┐┌─┐┌─┐┌┬┐┬┬  ┬┌─┐\n";
                std::cout<<"║│││ │ ├┤ ├┬┘├─┤│   │ │└┐┌┘├┤\n";
                std::cout<<"╩┘└┘ ┴ └─┘┴└─┴ ┴└─┘ ┴ ┴ └┘ └─┘\n";

                std::cout << "Choose an option: \n1. AVLTree \n2. HashTable\n3. Basic Statistics\n0. Back\n";
                std::cin >> choiceMaintenance;
                if(choiceMaintenance[0] == '1')
                {
                    std::cout<<" ╔═╗╦  ╦╦  \n";
                    std::cout<<" ╠═╣╚╗╔╝║  \n";
                    std::cout<<" ╩ ╩ ╚╝ ╩═╝\n";
                    if(counter_Tree == 0)
                    {
                        if(is_file_exist("output.txt"))
                        {
                            std::cout << "Building Tree from Index" << '\n';
                            Parser parse;
                            parse.parseIndex("output.txt", *Tree);
                            totalWords = parse.getOverallWordTotal();
                        }
                        else
                        makingStorage(Tree);
                        counter_Tree++;
                    }
                    TestingWithAVLTree();
                }
                if(choiceMaintenance[0] == '2')
                {
                    std::cout<<"╦ ╦┌─┐┌─┐┬ ┬╔╦╗┌─┐┌┐ ┬  ┌─┐\n";
                    std::cout<<"╠═╣├─┤└─┐├─┤ ║ ├─┤├┴┐│  ├┤ \n";
                    std::cout<<"╩ ╩┴ ┴└─┘┴ ┴ ╩ ┴ ┴└─┘┴─┘└─┘\n";
                    if(counter_Hash == 0)
                    {
                        if(is_file_exist("outputhash.txt"))
                        {
                            std::cout << "Building Hash Table from Index" << '\n';
                            Parser parse;
                            parse.parseIndex("outputhash.txt", *Table);
                            totalWords = parse.getOverallWordTotal();
                        }
                        else
                            makingStorage(Table);
                        counter_Hash++;
                    }
                    TestingWithHashTable();
                }
                if(choiceMaintenance[0] == '3')
                {
                    basicStat();
                }
                if(choiceMaintenance[0] == '0')
                {
                    std::cout<<"Exiting interactive mode...\n";
                    conditionInteractive = false;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            }
        }
        if(choice[0] == '3')
        {
            std::cout<<"Entering beast mode....\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout<<".----. .----.  .--.   .----..-----.    .-.  .-. .---. .----. .----. \n";
            std::cout<<"| {_} }} |__} / {} \\ { {__-``-' '-'    }  \\/  {/ {-. \\} {-. \\} |__} \n";
            std::cout<<"| {_} }} '__}/  /\\  \\.-._} }  } {      | {  } |\\ '-} /} '-} /} '__} \n";
            std::cout<<"`----' `----'`-'  `-'`----'   `-'      `-'  `-' `---' `----' `----' \n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout<<"Oops.... Nothing to do, exiting...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if(choice[0] == '0')
        {
            std::cout << "Saving your Data Structures to Index" << '\n';
            if(Tree->getSize() > 1){Tree->printIndex();}
            if(Table->getSize() > 1){Table->printIndex();}
            condition = false;
            std::cout << "Stopping program.....\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

