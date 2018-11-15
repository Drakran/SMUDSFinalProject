#include "Word.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;
/*getters and setters for private variables for each word object*/
Word :: Word()
{
    caseWord = "\0";
}

void Word :: setWord(string w)
{
    caseWord = w;
}

string Word :: getWord()
{
    return caseWord;
}

void Word :: upDateFileAndCount(string fileId, int countOfWord)
{
    FileIdAndCount.emplace(fileId, countOfWord);
}

map<string, int> Word :: getFileAndCount()
{
    return FileIdAndCount;
}
