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
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <stdexcept>
#include <dirent.h>
#include <fstream>
#include <regex>
#include <porter2_stemmer.h>
#include <set>
#include <map>
#include <unordered_map>
#include <Word.h>
#include <IndexInterface.h>

class Parser
{
public:
    Parser();
    std::vector<std::string> getFiles(std::string,std::string);
    void parse(std::string, std::string,  IndexInterface<Word,std::string>&);
    bool isStopWord(std::string);
    void incrementOverallWordTotal(int &wordsInThisFile);
    int getOverallWordTotal();
private:
    std::set<std::string> stopWords;
    std::vector<std::string> fileNames;
    int OverallWordTotal;
};

#endif // PARSER_H
