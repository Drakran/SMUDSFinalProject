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




class Parser
{
public:
    Parser();
    std::vector<std::string> getFiles(std::string,std::string);
    void parse();
private:
    std::vector<std::string> fileNames;
};

#endif // PARSER_H
