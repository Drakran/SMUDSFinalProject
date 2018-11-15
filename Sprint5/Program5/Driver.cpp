#include "Driver.h"
#include <iostream>
#include <IndexInterface.h>
#include <random>

using namespace std;

Driver::Driver()
{

}

void Driver :: Testing()
{

    Word *twoThings = new Word;
    twoThings->setWord("Terry");
    Word *threeThings = new Word;
    threeThings->setWord("Skyler");
    Word *fourThings = new Word;
    fourThings->setWord("Sophie");
    Word *scope = new Word;
    scope->setWord("Scope");
    Word *sabado = new Word;
    sabado->setWord("Sabado");

    //IndexInterface *Peng = new Penguin<int>();
    IndexInterface<Word*>* Tree = new AVLTree<Word*>();
    //Peng->Testing();
    Tree->Testing();
    //cout << Tree->getSize();
    Tree->insert(fourThings);
    Tree->insert(threeThings);
    Tree->insert(twoThings);
    Tree->insert(scope);
    Tree->insert(sabado);
    //Tree->printInOrder();

    Word *sabado1 = new Word;
    sabado1->setWord("Sabado");

     if( Tree->contains(sabado1) )
         cout << "found" <<endl;
     else
         cout << "notfound"<< endl;



//    srand(time(0));
//    int randNo;
//    for(int i = 0; i < 20; ++i)
//    {
//        randNo = rand()%250 + 1;
//        Tree->insert(randNo);
//    }
    //Tree->printInOrder();
}
