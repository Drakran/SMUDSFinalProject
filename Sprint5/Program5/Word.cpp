#include "Word.h"
#include <iostream>
#include <string>
#include <map>

/*getters and setters for private variables for each word object*/
Word :: Word()
{
    caseWord = "\0";
}

bool Word :: operator<(const Word& rightObj)
{
    return this->caseWord < rightObj.caseWord;
}

bool Word :: operator>(const Word& rightObj)
{
    return this->caseWord > rightObj.caseWord;
}

bool Word :: operator==(const Word& rightObj)
{
    return this->caseWord == rightObj.caseWord;
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

std::ostream & operator<<(std::ostream &out, const Word& w)
{
    out << w.caseWord;
    return out;
}
