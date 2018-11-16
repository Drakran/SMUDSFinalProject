#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <string>
#include <map>

class Word
{
public:
    Word();
    bool operator<(const Word& rightObj);
    bool operator>(const Word& rightObj);
    bool operator==(const Word& rightObj);
    friend std::ostream & operator<<(std::ostream &out, const Word& w);
    void setWord(std::string w);
    std::string& getWord();
    void upDateFileAndCount(std::string f, int c);
    std::map<std::string, int> getFileAndCount();
private:
    std::string caseWord;
    /*first element in map will be the file identifier
    second element in map will be the apprerances in that file*/
    std::map<std::string, int> FileIdAndCount;
};

#endif // WORD_H
