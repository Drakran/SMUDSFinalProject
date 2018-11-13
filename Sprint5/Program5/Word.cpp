#include "Word.h"
#include <iostream>
#include <string>
#include <map>

/*getters and setters for private variables for each word object*/
Word :: Word()
{
    caseWord = "\0";
}

void Word :: setWord(std::string w)
{
    caseWord = w;
}

std::string Word :: getWord()
{
    return caseWord;
}

void Word :: upDateFileAndCount(std::string fileId, int countOfWord)
{
    FileIdAndCount.emplace(fileId, countOfWord);
}

std::map<std::string, int> Word :: getFileAndCount()
{
    return FileIdAndCount;
}
