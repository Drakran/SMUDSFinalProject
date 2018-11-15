#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <Word.h>

template<typename T>
class IndexInterface
{
public:
    //functions for super class
    IndexInterface();
    virtual ~IndexInterface() = 0;
    virtual void Testing() = 0;
    virtual int getSize() = 0;
    virtual void insert( T &d ) = 0;
    virtual T& find( T& data ) = 0;
    virtual void printInOrder();
    virtual bool contains(T& d) = 0;

private:

};
template<typename T>
inline IndexInterface<T>::IndexInterface(){}
template<typename T>
inline IndexInterface<T>::~IndexInterface(){}
template<typename T>
inline void IndexInterface<T> :: printInOrder(){
   std::cout << "Jaime FULL APPROVAL";
}


#endif // INDEXINTERFACE_H
