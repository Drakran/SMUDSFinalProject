#ifndef R_RANKING_H
#define R_RANKING_H
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <sstream>
#include <istream>
#include <vector>
#include <map>
template <typename T>
class R_Ranking
{
public:
    R_Ranking();
    void calculateRR();
    void print();

private:
    std::vector<int> numOfInstance;

};

#endif // R_RANKING_H
