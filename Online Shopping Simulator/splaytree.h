#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <cstdlib>
#include <functional>
#include <string>
#include "bst.h"
#include "avlbst.h"

template <typename Key, typename Value, typename Comp = std::less<Key> >
class SplayTree:public BinarySearchTree<Key, Value>{
public:
    SplayTree(const Comp& c = Comp());
    ~SplayTree();
    // If the key is already present, update the value
    //virtual void insert(const std::pair<const Key,Value>& item); 

    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    // Return NULL if the key doesn't exist in the map
    //std::pair<const Key,Value>* find(const Key& key); 
    Node<Key, Value>* find(const Key& key);     
    // Do nothing if the key does not exist
    void erase(const Key& key); 
    size_t size() const;
    bool empty() const;

private:
    Comp c_;

    void sPrint() const ;
    Node<Key, Value>* internalFind(const Key& key) const;
    Node<Key, Value>* successorHelper(Node<Key, Value>* current);
    void splay(Node<Key, Value> *n);
    void rotateRight(Node<Key, Value> *n);
    void rotateLeft(Node<Key, Value> *n);
    bool isLeft(Node<Key, Value> *n);
    bool isRight(Node<Key, Value> *n);
    void nodeSwap(Node<Key, Value> *n, Node<Key, Value> *n2);

};

template <typename Key, typename Value, typename Comp>
SplayTree<Key, Value, Comp>::SplayTree(const Comp& c):c_(c){
    
}

template <typename Key, typename Value, typename Comp>
SplayTree<Key, Value, Comp>::~SplayTree(){

}

//adds the node to the first available space and then brings that node to the top 
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::insert(const std::pair<Key, Value>& keyValuePair)
{
    if(this->mRoot == NULL){
        this->mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        return;
    }
    else{
        Node<Key, Value>* parent = this->mRoot;
        Node<Key, Value>* child = NULL;

        while(parent){
            if(keyValuePair.first == parent->getKey()){
                parent->setValue(keyValuePair.second);
                return;
            }
            if(keyValuePair.first < parent->getKey()){ //look for parent value
                child = parent->getLeft();
                Node<Key, Value>* childFill = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);

                if(child == NULL){ 
                    parent->setLeft(childFill);
                    childFill->setParent(parent);
                    parent= NULL;
                    splay (childFill);
                    continue;                   
                }
                else{
                    parent = child;
                }
            } 
            else{
                child = parent->getRight();
                Node<Key, Value>* childFill = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent);
                
                if(child == NULL){
                    parent->setRight(childFill);
                    childFill->setParent(parent);
                    parent = NULL;
                    splay(childFill);
                    continue;
                }
                else{
                    parent = child;
                }
            } 
        }
    }
}

//finds the successor the the node passed in 
template <typename Key, typename Value, typename Comp>
Node<Key, Value>* SplayTree<Key,Value, Comp>::successorHelper(Node<Key, Value>* current){
    if(current == NULL){
        return NULL;
    }
    if(current->getRight() != NULL){
        Node<Key, Value>* newN = current->getRight();
        while(newN->getLeft() != NULL){
            newN = newN->getLeft();
        }
        return newN;
    }
    else{
        Node<Key, Value>* parent = current->getParent();
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


//boolean function to check if n is a left child 
template <typename Key, typename Value, typename Comp>
bool SplayTree<Key,Value, Comp>::isLeft(Node<Key, Value> *n){
    if(n->getParent() != NULL){
        Node<Key, Value> *parent = n->getParent();
        if(parent->getLeft() != NULL){
            if(parent->getLeft() == n){
                return true;
            }            
        }
    }
    return false;
}
//boolean function to check if n is a right child 
template <typename Key, typename Value, typename Comp>
bool SplayTree<Key,Value, Comp>::isRight(Node<Key, Value> *n){
    if(n->getParent() != NULL){
        Node<Key, Value> *parent = n->getParent();
        if(parent->getRight() != NULL){
            if(parent->getRight() == n){
                return true;
            }           
        }
    }
    return false;
}

//recursively splays the node to the top 
//accounts for zig zig and zig zag cases 
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::splay(Node<Key,Value>* n){
    if(this->mRoot == n){
        return;
    }
    if(n->getParent() == NULL){
        return;
    }
    if(n->getParent()->getParent() == NULL){
        if(n->getParent()->getLeft() == n){
            rotateRight(n->getParent());
            splay(n);
        }
        else {
            rotateLeft(n->getParent());
            splay(n);
        }
        
    }
    else{
        Node<Key, Value> * grandparent = n->getParent()->getParent();
        if(grandparent->getLeft() != NULL){
            if(grandparent->getLeft()->getLeft() == n){
                rotateRight(grandparent);
                rotateRight(n->getParent());
                splay(n);
            }
            else if(grandparent->getLeft()->getRight() == n){
                rotateLeft(n->getParent());
                rotateRight(grandparent);
                splay(n);                
            }
        }
        if(grandparent->getRight() != NULL){
            if(grandparent->getRight()->getRight() == n){
                rotateLeft(grandparent);
                rotateLeft(n->getParent());
                splay(n);               
            }
            else if(grandparent->getRight()->getLeft() == n){
                rotateRight(n->getParent());
                rotateLeft(grandparent);
                splay(n);
                
            }
        }
    }
}

//returns Null bc empty 
template <typename Key, typename Value, typename Comp>
bool SplayTree<Key, Value, Comp>::empty() const{
    return NULL;
}


// Helper function to find a Node with given key, key
template <typename Key, typename Value, typename Comp>
Node<Key, Value>* SplayTree<Key, Value, Comp>::find(const Key& key){
    if(empty()){
        return 0;
    }
    Node<Key, Value>* n = internalFind(key);
    splay(n);
    return this->mRoot;

}

//helper function for find 
template <typename Key, typename Value, typename Comp>
Node<Key, Value>* SplayTree<Key, Value, Comp>::internalFind(const Key& key) const
{
    Node<Key, Value>* curr = this->mRoot;
    while (curr)
    {
        if (curr->getKey() == key)
        {
            return curr;
        }
        else if (c_(key,curr->getKey()))
        {
            curr = curr->getLeft();
        }
        else
        {
            curr = curr->getRight();
        }
    }
    return NULL;
}

//removes the node passed in after splaying to the top 
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::erase(const Key& key)
{
    Node<Key, Value>* nFind = find(key);
    splay(nFind);

    Node<Key, Value>* p = NULL;
    int difference = 0;
    Node<Key, Value>* successor = NULL;

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
        Node<Key, Value>* child = NULL;
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
}






/**
* Rotates n down and to the left
*/
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::rotateLeft (Node<Key, Value> *n)
{
    // TODO

    Node<Key, Value>* parent = n->getRight();    
    Node<Key, Value>* greatgrandparent = n->getParent();     
    if(n->getParent() == NULL){
        BinarySearchTree<Key,Value,Comp>::mRoot = parent;
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
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::rotateRight (Node<Key, Value> *n)
{
    // TODO
  
    Node<Key, Value>* parent = n->getLeft();    
    Node<Key, Value>* greatgrandparent = n->getParent();     
    if(n->getParent() == NULL){
        BinarySearchTree<Key,Value,Comp>::mRoot = parent;
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



//helpful print function to test 
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::sPrint() const {
    this->print();
}

//swaps the node with the successor in this case 
template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
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

    // char temp2 = n1->getBalance();
    // n1->setBalance(n2->getBalance());
    // n2->setBalance(temp2);

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
#endif