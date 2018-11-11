#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Word
{
public:
    Word();
    void setWord(string w);
    string getWord();
    void upDateFileAndCount(string f, int c);
    map<string, int> getFileAndCount();
private:
    string caseWord;
    /*first element in map will be the file identifier
    second element in map will be the apprerances in that file*/
    map<string, int> FileIdAndCount;
};

#endif // WORD_H
