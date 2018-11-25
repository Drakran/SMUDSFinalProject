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
    virtual ~IndexInterface() = 0;
    virtual int getSize() = 0;
    virtual void insert( T &d,K &k ) = 0;
    virtual T& find( K& data ) = 0;
    virtual void printInOrder();

private:

};
template<typename T,typename K>
inline IndexInterface<T,K>::IndexInterface(){}
template<typename T,typename K>
inline IndexInterface<T,K>::~IndexInterface(){}
template<typename T,typename K>
inline void IndexInterface<T,K> :: printInOrder(){}

#endif // INDEXINTERFACE_H
