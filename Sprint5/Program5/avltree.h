#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <IndexInterface.h>

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
    Node(T d);
};

//constructor for node
template <typename T>
Node<T>::Node(T d)
{
    data = d;
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename T>
class AVLTree: public IndexInterface<T> {
/*
The AVLTree class will use private and public functions to insert.
The private function(s) are internal function(s) called
the public function(s).
*/
public:
    AVLTree();
    AVLTree(const AVLTree<T>& rightObject);
    virtual ~AVLTree();
    virtual void Testing(); //Remove later
    AVLTree<T>& operator=(const AVLTree<T>& rightObject);
    virtual int getSize();
    virtual void insert( T &d);
    void printInOrder();
    /*find: will traverse the tree and see if a node exits.This function is passed by reference
     because we will modify update existing info inside of the node.*/
    virtual bool contains(T& d);
    T& find( T& data );
private:
    Node<T>* root;
    int treeNodes;
    void copy(Node<T>* rightObjNodePtr);//used for copy constructor
    void clear(Node<T>* &rootPtr);//used for destructor
    void insert( T &d, Node<T>* &r);//passing root by reference
    bool contains(T& d, Node<T>* &r);
    void printInOrder(Node<T>* r);
    int getHeight(Node<T>* n);
    int max(int l, int r);
    void rotateWithLeftChild(Node<T>* &r);//passing root by reference
    void doubleWithLeftChild(Node<T>* &r);//passing root by reference
    void doubleWithRightChild(Node<T>* &r);//passing root by reference
    void rotateWithRightChild(Node<T>* &r);//passing root by reference

};


template<typename T>
void AVLTree<T>::Testing()
{
    std::cout << "Approved by Skyler Wang" << std::endl;
}


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
    this->root = nullptr;
    this->treeNodes = 0;
    //call copy function passing in the object to be copied.
    copy(rightObject.root);
}

//deconstructor
template <typename T>
AVLTree<T> :: ~AVLTree()
{
    //calling clear function to delete everything in tree.
    clear(root);
}

//overloaded assignment operator
template <typename T>
AVLTree<T>& AVLTree<T> :: operator=(const AVLTree<T>& rightObject)
{
    //checking if we are copying the same object
    if(this == &rightObject){
        return *this;
    }

    //calling clear function to delete everything in tree.
    clear(this->root);
    //call copy function passing in the object to be copied.
    copy(rightObject.root);

    return *this;
}

/*
This function will copy values, form the right hand side object.
This object is currently empty however, rightObject may not be empty.
copy function is used in copy constructor and assignment operator.
*/
template <typename T>
void AVLTree<T> :: copy(Node<T>* rightObjNodePtr)
{
    if(rightObjNodePtr){
        //add a new element from the right object to the left object
        insert(rightObjNodePtr->data);
        //copy recursively in order
        copy(rightObjNodePtr->left);
        copy(rightObjNodePtr->right);
    }
}

//function that frees dynamic memory.
template <typename T>
void AVLTree<T> :: clear(Node<T>* &rootPtr)
{
    //checking if tree is empty
    if(rootPtr != nullptr){
        //delete recursively on both left and right
        clear(rootPtr->left);
        clear(rootPtr->right);
        delete rootPtr;
        //make ptr null
        rootPtr = nullptr;
        --treeNodes;
    }
}

//function that gets the size of tree
template <typename T>
int AVLTree<T> :: getSize()
{
    return treeNodes;
}

//public insert function that will call private
template <typename T>
void AVLTree<T> :: insert( T &t)
{
    //passing in both values by reference
    insert(t, root);
}

//private insert function
template <typename T>
void AVLTree<T> :: insert( T &t, Node<T>* &ptrAtThisNode)
{
    //check if the tree is empty
    if(ptrAtThisNode == nullptr){
        //creating the root of the tree
        ptrAtThisNode = new Node<T>(t);
        ++treeNodes;
    }
    //checking if next value of the tree goes to left
    else if(t < ptrAtThisNode->data){
        //recursive call to insert on left side
        insert(t,ptrAtThisNode->left);
        //check for balance factor WHEN INSERTING IN THE LEFT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->left) - getHeight(ptrAtThisNode->right) ==  2){
            //checking for the imabalance factor, checking values inside node to do case 1 or 2
            if( t < ptrAtThisNode->left->data ){
                //case 1 rotation
                rotateWithLeftChild(ptrAtThisNode);
            }else{
                //case 2 rotation
                doubleWithLeftChild(ptrAtThisNode);
            }
        }
    }
    else if(t > ptrAtThisNode->data){
        //recursive call to insert on right side
        insert(t,ptrAtThisNode->right);
        //check for balance factor WHEN INSERTING IN THE RIGHT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->right) - getHeight(ptrAtThisNode->left) == 2){
            //checking for the imabalance factor, checking values inside node to do case 3 or 4
            if(ptrAtThisNode->right->data < t){
                //case 4 rotation
                rotateWithRightChild(ptrAtThisNode);
            }else{
                //case 3 rotation
                doubleWithRightChild(ptrAtThisNode);
            }
        }
    }
    else{}//value already existsin map, SPECIAL CASE

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
        //2nd. Outputting values. //setw(ptrAtThisNode->height *4) to print in tree format
        std::cout << ptrAtThisNode->data << std::endl;
        //3rd. Getting evertyhing to the right.
        printInOrder(ptrAtThisNode->right);
    }
}

/*This function will use to measure the height of each child.*/
template <typename T>
int AVLTree<T> :: getHeight(Node<T>* nPtr)
{
    //if no children return -1
    if(nPtr== nullptr)
        return 0;
    //returing height of the child.
    return nPtr->height;
}

/*This function will use to measure the height of each child.*/
template <typename T>
int AVLTree<T> :: max(int leftChild, int rightChild)
{
    //returing biggest between left and right
    return leftChild > rightChild ? leftChild : rightChild;
}

//case 1 rotation
template <typename T>
void AVLTree<T> :: doubleWithLeftChild(Node<T>* &K2)
{
    //converting case2 to a case1 by rotation
    rotateWithRightChild(K2->left);
    //balancing a tree using case1
    rotateWithLeftChild(K2);
}

/*
This is a case two rotation:
-left child of right substree.
*/
template <typename T>
void AVLTree<T> :: rotateWithLeftChild(Node<T>* &K2)
{
    //1) Create a pointer to the node left of the value passed in the function
    Node<T>* K1 = K2->left;
    //2) Make unbalanced left pointer point to the right of its left
    K2->left = K1->right;
    //3) Make the the right ptr of K1 point to K2
    K1->right = K2;
    //4) Update heights of each node and rotate nodes and switch imbalance node withs its left
    K2->height = 1+ max( getHeight(K2->left), getHeight(K2->right) );
    K1->height = 1+ max( getHeight(K1->left), getHeight(K2) );
    K2 = K1;

}

//case 4 rotation
template <typename T>
void AVLTree<T> :: doubleWithRightChild(Node<T>* &K2)
{
    //converting case3 to a case1 by rotation
    rotateWithLeftChild(K2->right);
    //balancing a tree using case4
    rotateWithRightChild(K2);
}

/*
This is a case three rotation:
-rightt child of left substree.
*/
template <typename T>
void AVLTree<T> :: rotateWithRightChild(Node<T>* &K2)
{
    //1) Create a pointer to the node left of the value passed in the function
    Node<T>* K1 = K2->right;
    //2) Make unbalanced right pointer point to the () of its ()
    K2->right = K1->left;
    //3) Make the the left ptr of K1 point to K2
    K1->left = K2;
    //4)The height of k2 will depend if there was a node added or not from k1.
    K2->height = 1+ max( getHeight(K2->left), getHeight(K2->right) );
    //The height of K1 will be the height of its own right + the height of its left or K2
    K1->height = 1+ max( getHeight(K1->right), getHeight(K2) );
    K2 = K1;

}

template <class T>
T& AVLTree<T> :: find( T& data )
{
    Node<T>* temp = root;
    while (temp != nullptr){
      if (temp->data == data)
          return temp->data;
      if (temp->data < data) temp = temp->right;
      else temp = temp->left;
    }
}

template<class T>
bool AVLTree<T>::contains( T & d )
{
    return contains( d, root );
}

template<class T>
bool AVLTree<T>::contains( T & d, Node<T>* &r )
{
    if( r == nullptr )
        return false;
    else if( d < r->data )
        return contains( d, r->left );
    else if( r->data < d )
        return contains( d, r->right );
    else
        return true;    // Match
}


#endif
