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
    void rotateLeftLeft(Node<T>* &r);//passing root by reference
    void rotateRightRight(Node<T>* &r);//passing root by reference
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
            //checking for the imabalance factor, checking values inside node to do case 1 or 2
            if( t < ptrAtThisNode->left->data ){
                //case 1 rotation
                rotateLeftLeft(ptrAtThisNode);
            }else{

            }
        //////////////////////////////////////////////////////////////////////
        }
    }else
    if(t > ptrAtThisNode->data){
        //recursive call to insert on right side
        insert(t,ptrAtThisNode->right);
        //check for balance factor WHEN INSERTING IN THE RIGHT, if true then its not balanced.
        if(getHeight(ptrAtThisNode->right) - getHeight(ptrAtThisNode->left) == 2){
        //////////////////////////////////////////////////////////////////////
            //checking for the imabalance factor, checking values inside node to do case 3 or 4
            if( t > ptrAtThisNode->right->data ){
                //case 4 rotation
                rotateRightRight(ptrAtThisNode);
            }else{

            }
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
        cout << setw(ptrAtThisNode->height *4) << ptrAtThisNode->data << endl;
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
int AVLTree<T>::max(int leftChild, int rightChild)
{
    //returing biggest between left and right
    return leftChild > rightChild ? leftChild : rightChild;
}


template <class T>
void AVLTree<T> :: rotateLeftLeft(Node<T>* &K2)
{
    /*K2 is node passed on, this is the imbalanced node.
     * This function will do a left left rotation (Case 1)
                     5
            K2 =  3       7
K1 = K2->left  2
K1 left    1
    */
    //1) Create a pointer to the node left of the value passed in the function
    Node<T>* K1 = K2->left;
    /*K2 is node passed on/imbalanced node.
     * This function will do a left left rotation (Case 1)
                     5
            K2 =  3       7
          K1 = 2 (IN THIS CASE K1->right = null, however it can be another node).
K1 left    1
    */
    //2) Make unbalanced left pointer point to the right of its left
    K2->left = K1->right;
    /*K2 is node passed on/imbalanced node.
     * This function will do a left left rotation (Case 1)
                      (5)
              K2  (3)       (7)
            K1 (2)  k1->right points to K2
            (1)
    */
    //3) Make the the right ptr of K1 point to K2
    K1->right = K2;
    /*K2 is node passed on/imbalanced node.
     * This function will do a left left rotation (Case 1)
                     5
        K2 = K1  2       7
              1     3
    */
    //4) Update heights of each node and rotate nodes and switch imbalance node withs its left
    K2->height = 1+ max( getHeight(K2->left), getHeight(K2->right) );
    K1->height = 1+ max( getHeight(K1->left), getHeight(K2) );
    K2 = K1;
}

template <class T>
void AVLTree<T> :: rotateRightRight(Node<T>* &K2)
{
    /*K2 is node passed on, this is the imbalanced node.
     * This function will do a right right rotation (Case 4)
                5
            3       7 = K2
                        9 K1 = K2->right
                            12 = K1->right
    */
    //1) Create a pointer to the node left of the value passed in the function
    Node<T>* K1 = K2->right;
    /*
                            5
                        3       7 = K2
                                  9 K1
K2->right will point here now:(8)   12
    */
    //2) Make unbalanced right pointer point to the () of its ()
    K2->right = K1->left;
    /*
                5
            3       (7)K2
          K1->left = K2 9
                      8   12
    */
    //3) Make the the left ptr of K1 point to K2
    K1->left = K2;
    /*
                5
            3       (9)K2 = K1
        K1-left = 7     12
        K2->right = 8
    */
    //4)The height of k2 will depend if there was a node added or not from k1.
    K2->height = 1+ max( getHeight(K2->left), getHeight(K2->right) );
    //The height of K1 will be the height of its own right + the height of its left or K2
    K1->height = 1+ max( getHeight(K1->right), getHeight(K2) );
    K2 = K1;
}

#endif
