/*
 *
 * Terry Wang
 *
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

class Parser
{
public:
    Parser();
    Parser(std::string);
    std::vector<std::string> getFiles(std::string,std::string);
    void parse(std::string, std::string,  IndexInterface<Word,std::string>&);
    bool isStopWord(std::string); //check if a word is a stop word, return true if it is
    void incrementOverallWordTotal(int &wordsInThisFile);
    int getOverallWordTotal();
private:
    std::set<std::string> stopWords;
    std::vector<std::string> fileNames;
    int OverallWordTotal;
    std::map<std::string, std::string> keepTrack;
    void parseCase(std::multimap<int, <std::string,int>>&, std::istringstream&);
    std::regex reg;
    std::string wordToFind;
};

#endif // PARSER_H
