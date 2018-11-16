#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <Word.h>

template<typename T,typename K>
class IndexInterface
{
public:
    //functions for super class
    IndexInterface();
    void setTotalNumberOfFiles(int &totalNumberOfFiles);
    int getTotalNumberOfFiles();
    //pure virtual functions: MUST BE OVERWRITTEN IN SUBCLASSES.
    virtual ~IndexInterface() = 0;
    virtual int getSize() = 0;
    virtual void insert( T &d,K &k ) = 0;
    virtual T& find( K& data ) = 0;
    //virtual functions that can be overwritten but do not have to
    virtual void printInOrder();

private:
    int totalNumberOfFiles;
};
template<typename T,typename K>
inline IndexInterface<T,K>::IndexInterface(){totalNumberOfFiles=0;}

template<typename T,typename K>
inline IndexInterface<T,K>::~IndexInterface(){}

template<typename T,typename K>
inline void IndexInterface<T,K>::setTotalNumberOfFiles(int &tNumFiles){ totalNumberOfFiles = tNumFiles; };

template<typename T,typename K>
inline int IndexInterface<T,K>::getTotalNumberOfFiles(){ return totalNumberOfFiles; };

/*Virtual Function*/
template<typename T,typename K>
inline void IndexInterface<T,K> :: printInOrder(){}


#endif // INDEXINTERFACE_H
