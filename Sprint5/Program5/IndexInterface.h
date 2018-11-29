#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include "Word.h"
#include "vector"

template<typename T,typename K>
class IndexInterface
{
public:
    //functions for super class
    IndexInterface();
    //pure virtual functions, MUST BE OVERWRITTEN
    virtual ~IndexInterface() = 0;
    virtual int getSize() = 0;
    virtual void insert( T &d,K &k ) = 0;
    virtual T& find( K& data ) = 0;
    //virtual functions, CAN BE OVERWRITEN BUT DO NOT HAVE TO.
    virtual void printInOrder();
    virtual T& operator[](K& lookUpKey);
    virtual std::map<int, std::string, std::greater<int>>& top50Common() = 0;
    virtual std::map<std::string, int>& getTotalWordsEachCase() = 0;
private:

};
template<typename T,typename K>
inline IndexInterface<T,K>::IndexInterface(){}
template<typename T,typename K>
inline IndexInterface<T,K>::~IndexInterface(){}
template<typename T,typename K>
//virtual functions
inline void IndexInterface<T,K> :: printInOrder(){}
template<typename T,typename K>
inline T& IndexInterface<T,K> :: operator[](K& lookUpKey){}
template<typename T,typename K>
std::map<int, std::string, std::greater<int>>& top50Common(){}
template<typename T,typename K>
std::map<std::string, int>& getTotalWordsEachCase(){}
#endif // INDEXINTERFACE_H
