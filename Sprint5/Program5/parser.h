/*
 *
 * Terry Wang
 *
 */

#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <stdexcept>
#include <dirent.h>
#include <fstream>


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
