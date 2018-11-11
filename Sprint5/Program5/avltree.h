#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

template <typename T> class Node;
template <typename T> class AVLTree;

template <typename T>
class Node{

friend class AVLTree<T>;

private:
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
public:
    //default parameters for each child pointers
    Node(T d, Node<T>* l = nullptr, Node<T>* r = nullptr);
};

//constructor for node
template <typename T>
Node<T>::Node(T d, Node<T>* l, Node<T>* r)
{
    data = d;
    left = l;
    right = r;
    height = 0;
}

template <typename T>
class AVLTree {
/*
The AVLTree class will use private and public functions to insert.
The private function(s) are internal function(s) called
the public function(s).
*/
public:
    AVLTree();
    AVLTree(const AVLTree<T>& rightObject);
    ~AVLTree();
    AVLTree<T>& operator=(const AVLTree<T>& rightObject);
    void copy(const AVLTree<T>& rightObject);
    void clear();
    int getSizeOfTree();
    void insert(const T &d);
    void printInOrder();
private:
    Node<T>* root;
    int treeNodes;
    void insert(const T &d, Node<T>* &r);//passing root by reference
    void printInOrder(Node<T>* r);
    int getHeight(Node<T>* n);
    int max(int l, int r);
};

//default constructor
template <typename T>
AVLTree<T> :: AVLTree()
{
    //initializing private variables
    root = nullptr;
    treeNodes = 0;
}

//copy constructor
template <typename T>
AVLTree<T> :: AVLTree(const AVLTree<T>& rightObject)
{
    //initializing private variables.
    this->treeNodes = rightObject.treeNodes;
    //call copy function passing in the object to be copied.
    copy(rightObject);
}

//deconstructor
template <typename T>
AVLTree<T> :: ~AVLTree()
{
    //calling clear function to delete everything in tree.
    clear();
}

//overloaded assignment operator
template <typename T>
AVLTree<T>& AVLTree<T>:: operator=(const AVLTree<T>& rightObject)
{
    //checking if we are copying the same object
    if(this == &rightObject){
        return *this;
    }

    //calling clear function to delete everything in tree.
    clear();
    //call copy function passing in the object to be copied.
    copy(rightObject);

    return *this;
}

//copy function
template <typename T>
void AVLTree<T> :: copy(const AVLTree<T>& rightObject)
{
    //checking if the right object is empty
    if(rightObject.root == nullptr){
        //don't do anything
        return;
    }else{
        //right object is not empty, so we copy rightObject to this object

    }
}

//function that frees dynamic memory.
template <typename T>
void AVLTree<T> :: clear()
{
    //checking if tree is empty
    if(root == nullptr){
        //don't do anything
        return;
    }else{
        //the tree is not empty so we delete everything
    }
}

//function that gets the size of tree
template <typename T>
int AVLTree<T> :: getSizeOfTree()
{
    return treeNodes;
}

//public insert function that will call private
template <typename T>
void AVLTree<T> :: insert(const T &t)
{
    //passing in both values by reference
    insert(t, root);
}

//private insert function
template <typename T>
void AVLTree<T> :: insert(const T &t, Node<T>* &ptrAtThisNode)
{
    //check if the tree is empty
    if(ptrAtThisNode == nullptr){
        //creating the root of the tree
        ptrAtThisNode = new Node<T>(t, nullptr, nullptr);

        //update height
        ptrAtThisNode->height++;

        //update counter
        ++treeNodes;
        return;
    }

    //checking if next value of the tree goes to left
    if(t < ptrAtThisNode->data){
        //recursive call to insert on left side
        insert(t,ptrAtThisNode->left);
        //check for balance factor WHEN INSERTING IN THE LEFT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->left) - getHeight(ptrAtThisNode->right) ==  2){
        //////////////////////////////////////////////////////////////////////
        cout << "here " << ptrAtThisNode->data << endl;
        cout << "left height "<< getHeight(ptrAtThisNode->left) << "\n"
             << "right heieght " << getHeight(ptrAtThisNode->right) << "\n";
        //////////////////////////////////////////////////////////////////////
        }
    }else
    if(t > ptrAtThisNode->data){
        //recursive call to insert on right side
        insert(t,ptrAtThisNode->right);
        //check for balance factor WHEN INSERTING IN THE RIGHT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->right) - getHeight(ptrAtThisNode->left) == 2){
        //////////////////////////////////////////////////////////////////////
            cout << "here " << ptrAtThisNode->data << endl;
            cout << "right height "<< getHeight(ptrAtThisNode->right) << "\n"
                 << "left heieght " << getHeight(ptrAtThisNode->left) << "\n";
        //////////////////////////////////////////////////////////////////////
        }
    }else{//value already existsin map, SPECIAL CASE
    }

    //update height
    ptrAtThisNode->height = 1 + max( getHeight(ptrAtThisNode->left), getHeight(ptrAtThisNode->right) );
}

//displaying values inside of the avl tree
template <typename T>
void AVLTree<T> :: printInOrder()
{
    //checking if tree is empty
    if(root == nullptr)
        throw std::out_of_range("Error trying to print empty AVL tree. Inside printInOrder.");
    //calling private printInOrder method
    printInOrder(root);
}

//displaying values inside of the avl tree
template <typename T>
void AVLTree<T> :: printInOrder(Node<T>* ptrAtThisNode)
{
    //recursive call until null
    if(ptrAtThisNode != nullptr){
        //1st. Getting everything to left
        printInOrder(ptrAtThisNode->left);
        //2nd. Outputting values.
        cout << ptrAtThisNode->data << endl;
        //3rd. Getting evertyhing to the right.
        printInOrder(ptrAtThisNode->right);
    }
}

/*This function will use to measure the height of each child.*/
template <class T>
int AVLTree<T>::getHeight(Node<T>* nPtr)
{
    //if no children return -1
    if(nPtr== nullptr)
        return 0;
    //returing height of the child.
    return nPtr->height;
}

/*This function will use to measure the height of each child.*/
template <class T>
int AVLTree<T>::max(int l, int r)
{
    //returing biggest between left and right
    return l > r ? l : r;
}

#endif
