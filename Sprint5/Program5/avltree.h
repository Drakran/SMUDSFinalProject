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
    int getSizeOfTree();
    void insert(const T &d);
    void printInOrder();
    bool contains(const T &d);//contains will use find to search the avl tree
private:
    Node<T>* root;
    int treeNodes;
    void copy(Node<T>* rightObjNodePtr);//used for copy constructor
    void clear(Node<T>* &rootPtr);//used for destructor
    void insert(const T &d, Node<T>* &r);//passing root by reference
    void printInOrder(Node<T>* r);
    int getHeight(Node<T>* n);
    int max(int l, int r);
    void rotateLeftLeft(Node<T>* &r);//passing root by reference
    void rotateLeftRight(Node<T>* &r);//passing root by reference
    void rotateRightRight(Node<T>* &r);//passing root by reference
    void rotateRightLeft(Node<T>* &r);//passing root by reference
    Node<T>* find(const T &d);//public function contains will call find

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
            //checking for the imabalance factor, checking values inside node to do case 1 or 2
            if( t < ptrAtThisNode->left->data ){
                //case 1 rotation
                rotateLeftLeft(ptrAtThisNode);
            }else{
                //case 2 rotation
                rotateLeftRight(ptrAtThisNode);
            }
        }
    }else
    if(t > ptrAtThisNode->data){
        //recursive call to insert on right side
        insert(t,ptrAtThisNode->right);
        //check for balance factor WHEN INSERTING IN THE RIGHT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->right) - getHeight(ptrAtThisNode->left) == 2){
            //checking for the imabalance factor, checking values inside node to do case 3 or 4
            if( t > ptrAtThisNode->right->data ){
                //case 4 rotation
                rotateRightRight(ptrAtThisNode);
            }else{
                //case 3 rotation
                rotateRightLeft(ptrAtThisNode);
            }
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
        //2nd. Outputting values. //setw(ptrAtThisNode->height *4) to print in tree format
        cout << ptrAtThisNode->data << endl;
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
void AVLTree<T> :: rotateLeftLeft(Node<T>* &K2)
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

/*
This is a case two rotation:
-left child of right substree.
*/
template <typename T>
void AVLTree<T> :: rotateLeftRight(Node<T>* &K2)
{
    //converting case2 to a case1 by rotation
    rotateRightRight(K2);
    //balancing a tree using case1
    rotateLeftLeft(K2);

}

//case 4 rotation
template <typename T>
void AVLTree<T> :: rotateRightRight(Node<T>* &K2)
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

/*
This is a case three rotation:
-rightt child of left substree.
*/
template <typename T>
void AVLTree<T> :: rotateRightLeft(Node<T>* &K2)
{
    //converting case3 to a case1 by rotation
    rotateLeftLeft(K2);
    //balancing a tree using case4
    rotateRightRight(K2);

}

//This function will return a ptr to the element in the AVL tree
template <typename T>
bool AVLTree<T> :: contains(const T& ValueToFind)
{
    //if the return type of find is NOT NULL then the value exists in avl tree
    return ( find(ValueToFind) != nullptr );
}

//This function will return a ptr to the element in the AVL tree
template <typename T>
Node<T>* AVLTree<T> :: find(const T& ValueToFind)
{
    //create a temp node ptr poiting to root
    Node<T>* tempNodePtr = root;
    while (tempNodePtr != nullptr){
        if (tempNodePtr->data == ValueToFind)//ptr found
            return tempNodePtr;
        if (tempNodePtr->data < ValueToFind)//searching right
            tempNodePtr = tempNodePtr->right;
        else                        //searching left
            tempNodePtr= tempNodePtr->left;
    }
    //returning null if not found
    return nullptr;
}

#endif
