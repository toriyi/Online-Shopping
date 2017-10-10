#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;
    //std::pair<double, T> const & top() const;
    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

    void print();
private:
    /// Add whatever helper functions you need below
    void trickleUp(int index);
    void trickleDown(int index);


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

//need to also insert new pushed value into the map
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.

    store_.push_back(std::make_pair(priority, item));
    keyToLocation_.insert(std::make_pair(item, store_.size()-1));
    trickleUp(store_.size()-1);

}

//will replace the priority value if the item is found in the map 
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it;
    if(keyToLocation_.find(item) == keyToLocation_.end()){
        return;
    }
    it = keyToLocation_.find(item);
    int place = it->second;
    double prevPri = store_[place].first;


    if(prevPri >= priority){
        store_[place].first = priority;
        trickleUp(place);
    }
}

//gets the top value in the heap duh 
template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete
    return store_[0].second;
}

// Removes the top element
//updates map when there is a swap 
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it;
    // You complete
    std::swap(store_[0], store_[store_.size()-1]);
    it = keyToLocation_.find(store_[0].second);
    it->second = 0;
    store_.pop_back();
    trickleDown(0);
}

// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

//updates the map after there is a swap 
//adds an item to the first free location
//at the bottom of the tree and promotes it up
//while it is less than its parent
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator, PComparator, Hasher>::trickleUp(int index){
  int parent = (index-1)/m_;

  while(parent >= 0 && c_(store_[index].first ,store_[parent].first)){ 
    std::swap(store_[parent], store_[index]);
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it;
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator iter;

    it = keyToLocation_.find(store_[index].second);
    it->second = index;
    iter = keyToLocation_.find(store_[parent].second);
    iter->second = parent;

    index = parent;
    parent = (index-1)/m_;
  }
}

//updates map after there is a swap 
//takes the last node and puts it in the top location
//and recursively swaps it for the smallest child
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator, PComparator, Hasher>::trickleDown(int index){
  int leftChild = (m_*index)+1;
  if(leftChild >= store_.size()){
    return;
  }
  int count = 1;
  int smallChild = leftChild;
  while(count < m_){   
    if(leftChild + count < store_.size()){
      int otherChild = leftChild + count;
      if(c_(store_[otherChild].first,store_[smallChild].first)){
        smallChild = otherChild; 
      }
    }
    count++;
  }
  if(c_(store_[smallChild].first,store_[index].first)){
    std::swap(store_[index], store_[smallChild]);


    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it;
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator iter;

    it = keyToLocation_.find(store_[index].second);
    it->second = index;
    iter = keyToLocation_.find(store_[smallChild].second);
    iter->second = smallChild;
 
    trickleDown(smallChild);
  }
}

//print to test 
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator, PComparator, Hasher>::print(){
    for(int i = 0; i < store_.size(); i++){
     std::cout << "Vector[" << i << "] " << store_[i].first << " " <<  store_[i].second << " " << std::endl;
     std::cout << "Map " << i << std::endl;
    }
    std::cout << std::endl;
}


#endif

