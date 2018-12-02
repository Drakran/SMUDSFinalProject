/*This class is sent individual files and returns
 * a parsed verison of the file along with
 * any information that the user requests of that
 * file
 *
 * Terry Wang
 *
 * Along with Skyler and Jaime for the other parts
 * but parser is mine
 *
 * Dec 2018
 */

#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include <map>
#include <stdexcept>
#include <fstream>
#include <chrono>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <regex>
#include <porter2_stemmer.h>
#include <set>
#include "Word.h"
#include "dirent.h"
#include "IndexInterface.h"
#include <vector>

/*Code for reading in files adapted
 * from https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c
 */

class Parser
{
public:
    Parser();
    std::vector<std::string> getFiles(std::string,std::string);
    void parse(std::string, std::string,  IndexInterface<Word,std::string>&);
    bool isStopWord(std::string); //check if a word is a stop word, return true if it is
    void incrementOverallWordTotal(int &wordsInThisFile);
    unsigned long getOverallWordTotal();
    void parseOneFile(std::vector<std::string>&, std::string);
    void parseIndex(std::string, IndexInterface<Word,std::string>&);
    std::string returnTextofFile(std::vector<std::string>&, std::string);
    int numberofTerms(std::vector<std::string>&, std::string, std::string, IndexInterface<Word,std::string>& );
private:
    std::set<std::string> stopWords;
    std::vector<std::string> fileNames;
    unsigned long OverallWordTotal;
    std::map<std::string, std::string> keepTrack;
    void parseCase(std::map<std::string,int>&, std::istringstream&);
    std::ifstream readInFiles(std::vector<std::string>&, std::string);
    std::regex reg;
};
#endif // PARSER_H
