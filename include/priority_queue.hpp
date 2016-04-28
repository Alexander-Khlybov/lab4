#pragma once

#include <iostream>
#include "d-heap.hpp"

template<class KeyType>
class PRIORITY_QUEUE{

	D_HEAP<KeyType>* heap_;
public:
    PRIORITY_QUEUE  (int d = 3);
    PRIORITY_QUEUE  (const PRIORITY_QUEUE<KeyType>&);
	~PRIORITY_QUEUE (void) { delete heap_;};

    int                 getSize 	(void) const { return heap_->getSizeTree();}
    D_HEAP<KeyType>     getHeap     (void) const;

    int     operator==  (const PRIORITY_QUEUE<KeyType>&)const;
    int     operator!=  (const PRIORITY_QUEUE<KeyType>&)const;

    int     isEmpty     (void) const;

    void    pop         (void);
    void    push        (const KeyType&);
    KeyType back        (void) const;

    friend std::ostream& operator<< (std::ostream& out, const PRIORITY_QUEUE<KeyType>& queue) {
            out << queue.heap_;
        return out;
    }
};


template<class KeyType>
PRIORITY_QUEUE<KeyType>::PRIORITY_QUEUE(int d) {
    if (d <= 0)
        throw myExcp("D must be > 0");

    heap_ = new D_HEAP<KeyType>(0, 1);
}

template<class KeyType>
PRIORITY_QUEUE<KeyType>::PRIORITY_QUEUE(const PRIORITY_QUEUE& queue) {
    heap_ = new D_HEAP<KeyType>(*queue.heap_);
    if (heap_ == NULL)
        throw myExcp("Memory allocationn error.");
}

template<class KeyType>
D_HEAP<KeyType> PRIORITY_QUEUE<KeyType>::getHeap(void) const {
    D_HEAP<KeyType> heap(*heap_);
    return heap;
}

template<class KeyType>
int PRIORITY_QUEUE<KeyType>::operator== (const PRIORITY_QUEUE<KeyType>& queue) const {

    return *heap_ == *queue.heap_;
}

template<class KeyType>
int PRIORITY_QUEUE<KeyType>::operator!= (const PRIORITY_QUEUE<KeyType>& queue) const {

    return heap_ != queue.heap_;
}

template<class KeyType>
int PRIORITY_QUEUE<KeyType>::isEmpty(void) const {

    return (0 == heap_->getSizeTree()) ? 1 : 0;
}

template<class KeyType>
void PRIORITY_QUEUE<KeyType>::pop(void) {
    if (isEmpty())
        throw myExcp("Priority queue is empty.");
    heap_->deleteMinElem();
}

template<class KeyType>
void PRIORITY_QUEUE<KeyType>::push(const KeyType& key) {
    heap_->insert(key);
}

template<class KeyType>
KeyType PRIORITY_QUEUE<KeyType>::back(void) const {
    if (isEmpty())
        throw myExcp("Priority queue is empty.");
    KeyType tmp = heap_->getNodeKey(0);
    return tmp;
}
