#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);
   
private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */
    //added this
    void insertFix(AVLNode<Key, Value> *p, AVLNode<Key, Value> *n);
    bool isLeft(AVLNode<Key, Value> *n);
    bool isRight(AVLNode<Key, Value> *n);  
    void removeFix(AVLNode<Key, Value> *nFind, int difference);
    AVLNode<Key, Value>* successorHelper(AVLNode<Key, Value>* current);

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------

* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    if(this->mRoot == NULL){
        this->mRoot = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }
    else{
        AVLNode<Key, Value>* parent = static_cast<AVLNode<Key,Value>*>(this->mRoot);
        AVLNode<Key, Value>* child = NULL;

        while(parent){
            //Case for same inputs 
            if(keyValuePair.first == parent->getKey()){
                parent->setValue(keyValuePair.second);
                return;
            }
            //left case
            if(keyValuePair.first < parent->getKey()){ 
                child = parent->getLeft();
                AVLNode<Key, Value>* childFill = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
                if(child == NULL){ 
                    parent->setLeft(childFill);
                    childFill->setParent(parent);
                    if(parent->getBalance() == -1 || parent->getBalance() == 1){
                        parent->setBalance(0);
                    }
                    else{
                        if(parent->getLeft() == childFill){
                            parent->setBalance(-1); 
                        }
                        else{
                            parent->setBalance(1);
                        }
                        insertFix(parent, childFill);
                    }
                    parent= NULL;
                    continue;                   
                }
                else{
                    parent = child;
                }
            } 
            //right case
            else{
                child = parent->getRight();
                AVLNode<Key, Value>* childFill = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
                if(child == NULL){
                    parent->setRight(childFill);
                    childFill->setParent(parent);
                    if(parent->getBalance() == -1 || parent->getBalance() == 1){
                        parent->setBalance(0);
                        break;
                    }
                    else{
                        if(parent->getRight() == childFill){
                            parent->setBalance(1);
                        }
                        else{
                            parent->setBalance(-1);
                        }
                        if(parent->getParent()){
                        }
                        insertFix(parent, childFill);
                    }
                    parent = NULL;
                    continue;
                }
                else{
                    parent = child;
                }
            } 
        }
    }
}


//boolean function to check if n is a left child 
template<typename Key, typename Value>
bool AVLTree<Key,Value>::isLeft(AVLNode<Key, Value> *n){
    if(n->getParent() != NULL){
        AVLNode<Key, Value> *parent = n->getParent();
        if(parent->getLeft() != NULL){
            if(parent->getLeft() == n){
                return true;
            }            
        }
    }
    return false;
}
//boolean function to check if n is a right child 
template<typename Key, typename Value>
bool AVLTree<Key,Value>::isRight(AVLNode<Key, Value> *n){
    if(n->getParent() != NULL){
        AVLNode<Key, Value> *parent = n->getParent();
        if(parent->getRight() != NULL){
            if(parent->getRight() == n){
                return true;
            }           
        }
    }
    return false;
}

//rebalances the tree after insertions are made 
//splits it up whether the insertion is made to the left or to the right
//and for zig zig vs zig zag cases 
template<typename Key, typename Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value> *pChild){
    AVLNode<Key, Value>* grandparent = parent->getParent();
    if(parent == NULL || grandparent == NULL){
        return;
    }
    if(isLeft(parent)){ //left child 
        grandparent->updateBalance(-1);
        if(grandparent->getBalance() == 0){
            return;
        }
        if(grandparent->getBalance() == -1){
            insertFix(grandparent, parent);
        }
        if(grandparent->getBalance() == -2){
            //zig-zig
            if(isLeft(parent) && isLeft(pChild)){
                rotateRight(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            //zig-zag
            else{
                if(isLeft(parent) && isRight(pChild)){ //left then right 
                    rotateLeft(parent);
                    rotateRight(grandparent);
                    if(pChild->getBalance() == -1){
                        parent->setBalance(0);
                        grandparent->setBalance(1); 
                        pChild->setBalance(0);
                    }
                    else if(pChild->getBalance() == 0){
                        parent->setBalance(0);
                        grandparent->setBalance(0); 
                        pChild->setBalance(0);
                    }
                    else if(pChild->getBalance() == 1){
                        parent->setBalance(-1);
                        grandparent->setBalance(0); 
                        pChild->setBalance(0);
                    }
                }
            }
        }
    }
    else{
        grandparent->updateBalance(1);
        if(grandparent->getBalance() == 0){
            return;
        }
        if(grandparent->getBalance() == 1){
            insertFix(grandparent, parent);
        }
        if(grandparent->getBalance() == 2){
            //zig-zig
            if(isRight(parent) && isRight(pChild)){
                rotateLeft(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            //zig-zag
            else{
                if(isRight(parent) && isLeft(pChild)){ //left then right 
                    rotateRight(parent);
                    rotateLeft(grandparent);
                    if(pChild->getBalance() == 1){
                        parent->setBalance(0);
                        grandparent->setBalance(-1); 
                        pChild->setBalance(0);
                    }
                    else if(pChild->getBalance() == 0){
                        parent->setBalance(0);
                        grandparent->setBalance(0); 
                        pChild->setBalance(0);
                    }
                    else if(pChild->getBalance() == -1){
                        parent->setBalance(1);
                        grandparent->setBalance(0);  
                        pChild->setBalance(0);
                    }
                }
            }
        }       
    }
}

//helper function to find the successor 
//right and then all the way left
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::successorHelper(AVLNode<Key, Value>* current){
    if(current == NULL){
        return NULL;
    }
    if(current->getRight() != NULL){
        AVLNode<Key, Value>* newN = current->getRight();
        while(newN->getLeft() != NULL){
            newN = newN->getLeft();
        }
        return newN;
    }
    else{
        AVLNode<Key, Value>* parent = current->getParent();
        while(parent != NULL){
            if(parent->getLeft() == current){
                break;
            }
            else{
                current = parent;
                parent = current->getParent();
            }
        }
        return parent;           
    }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{
    AVLNode<Key, Value>* nFind = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* p = NULL;
    int difference = 0;
    AVLNode<Key, Value>* successor = NULL;

    if(nFind == NULL){
        return;
    }

    // two children
    if(nFind->getLeft() != NULL && nFind->getRight() != NULL){        
        successor = successorHelper(nFind);
        nodeSwap(nFind, successor);
    }

    p = nFind->getParent();
    
    if(p != NULL){
        if (isRight(nFind)){
            difference = -1;
        }
        else {
            difference = 1;
        }
    }
    //one child
    if (nFind->getRight() != NULL || nFind->getLeft() != NULL){
        AVLNode<Key, Value>* child = NULL;
        if (nFind->getRight() != NULL){
            child = nFind->getRight();
        }
        else if (nFind->getLeft() != NULL){
            child = nFind->getLeft();
        }
        if (isLeft(nFind)){
            p->setLeft(child);
            if(child != NULL){
                child->setParent(p);
            }
            delete nFind;
        }
        else if (isRight(nFind)){
            p->setRight(child);
            if(child != NULL){
                child->setParent(p);               
            }
            delete nFind;
        }
        // root
        else{
            this->mRoot = child;
            if(child != NULL){
                child->setParent(p);
            }
            delete nFind;
            return;
        }

    }
    // no children
    else{
        // root
        if (p == NULL) {
            this->mRoot = NULL;
            delete nFind;
            return;
        }
        if (isLeft(nFind)){
            p->setLeft(NULL);
        }
        else{
            p->setRight(NULL);
        }
        delete nFind;
    }
    removeFix(p, difference);
}

//rebalances tree after removal
//account for zig zig and zig zag cases 
//and whether the tree is left or right heavy 
template<typename Key, typename Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key, Value> *nFind, int difference){
    if(nFind == NULL){
        return;
    }
    AVLNode<Key, Value> *parent = nFind->getParent();
    int ndiff = 0;
    if(nFind->getParent() != NULL){
        if(isLeft(nFind)){
            ndiff = 1;
        }
        else{
            ndiff = -1;
        }       
    }
    if((nFind->getBalance() + difference) == -2){
        AVLNode<Key, Value> *childLeft = nFind->getLeft();
        if(childLeft != NULL && (childLeft->getBalance() == -1 || childLeft->getBalance() == 0)){ //zig zig 
            rotateRight(nFind);
            if(childLeft->getBalance() == -1){
                nFind->setBalance(0);
                childLeft->setBalance(0);
                removeFix(parent, ndiff);
            }
            else{
                nFind->setBalance(-1);
                childLeft->setBalance(1);
            }
        }
        else{ //zig zag
            std::cout<<"ELSE  IF NOT -2 ZIG ZAG " << std::endl;
            AVLNode<Key, Value> *grandChild = childLeft->getRight();
            rotateLeft(childLeft);
            rotateRight(nFind);
            if(grandChild->getBalance() == 1){
                nFind->setBalance(0);
                childLeft->setBalance(-1);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == 0){
                nFind->setBalance(0);
                childLeft->setBalance(0);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == -1){
                nFind->setBalance(1);
                childLeft->setBalance(0);
                grandChild->setBalance(0);
            }
            removeFix(parent, ndiff);
        }
    }
    else if((nFind->getBalance() + difference) == 2){
        AVLNode<Key, Value> *childRight = nFind->getRight();
        if(childRight->getBalance() == 1 || childRight->getBalance() == 0){ //zig zig 
            rotateLeft(nFind);
            if(childRight->getBalance() == 1){
                nFind->setBalance(0);
                childRight->setBalance(0);
                removeFix(parent, ndiff);
            }
            else{
                nFind->setBalance(1);
                childRight->setBalance(-1);
            }
        }
        else{ //zig zag
            AVLNode<Key, Value> *grandChild = childRight->getLeft();
            rotateRight(childRight);
            rotateLeft(nFind);
            if(grandChild->getBalance() == -1){
                nFind->setBalance(0);
                childRight->setBalance(1);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == 0){
                nFind->setBalance(0);
                childRight->setBalance(0);
                grandChild->setBalance(0);
            }
            else if(grandChild->getBalance() == 1){
                nFind->setBalance(-1);
                childRight->setBalance(0);
                grandChild->setBalance(0);
            }
            removeFix(parent, ndiff);
        }       
    }
    else if(nFind->getBalance() == 0){
            nFind->updateBalance(difference);
            return;
    }
    else{
        nFind->setBalance(0);  
        removeFix(parent, ndiff);
    }
}


/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    // TODO

    AVLNode<Key, Value>* parent = n->getRight();    
    AVLNode<Key, Value>* greatgrandparent = n->getParent();     
    if(n->getParent() == NULL){
        this->mRoot = parent;
        parent->setParent(NULL);
        if(parent->getLeft() != NULL){
            parent->getLeft()->setParent(n);            
        }
        n->setParent(parent);
        n->setRight(parent->getLeft()); 
        parent->setLeft(n); 
        parent->setParent(greatgrandparent);
    }
    else if(n->getParent() != NULL){
        n->setRight(parent->getLeft());
        n->setParent(parent);
        if(parent->getLeft() != NULL){
            parent->getLeft()->setParent(n);            
        }
        parent->setLeft(n);    
        n->setParent(parent);     
        parent->setParent(greatgrandparent);
        if(greatgrandparent->getRight() == n){
            greatgrandparent->setRight(parent);                
        }
        else{
            greatgrandparent->setLeft(parent);
        }
    }
}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    // TODO
  
    AVLNode<Key, Value>* parent = n->getLeft();    
    AVLNode<Key, Value>* greatgrandparent = n->getParent();     
    if(n->getParent() == NULL){
        this->mRoot = parent;
        parent->setParent(NULL);
        if(parent->getRight() != NULL){
            parent->getRight()->setParent(n);            
        }
        n->setParent(parent);     
        n->setLeft(parent->getRight());     
        parent->setRight(n); 
        parent->setParent(greatgrandparent);
    }
    else if(n->getParent() != NULL){
        n->setLeft(parent->getRight());
        n->setParent(parent);
        if(parent->getRight() != NULL){
            parent->getRight()->setParent(n);            
        }
        parent->setRight(n);  
        n->setParent(parent);           
        parent->setParent(greatgrandparent);
        if(greatgrandparent->getLeft() == n){
            greatgrandparent->setLeft(parent);                
        }
        else{
            greatgrandparent->setRight(parent);
        }
    }
}


/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
