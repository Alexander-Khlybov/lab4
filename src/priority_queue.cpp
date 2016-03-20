#include "priority_queue.h"

PRIORITY_QUEUE::PRIORITY_QUEUE (int d){
	if (d <= 0)
		throw myExcp("D must be > 0");

	heap_ = new D_HEAP(0, 1);
}

PRIORITY_QUEUE::PRIORITY_QUEUE (const PRIORITY_QUEUE& queue){
	heap_ = new D_HEAP(*queue.heap_);
	if (heap_ == NULL)
		throw myExcp("Memory allocationn error.");
}

D_HEAP PRIORITY_QUEUE::getHeap (void) const{
	D_HEAP heap(*heap_);
    return heap;
}

int PRIORITY_QUEUE::operator== (const PRIORITY_QUEUE& queue) const{

    return *heap_ == *queue.heap_;
}

int PRIORITY_QUEUE::operator!= (const PRIORITY_QUEUE& queue) const{

    return heap_ != queue.heap_;
}

int PRIORITY_QUEUE::isEmpty (void) const{

    return (0 == heap_ -> getSizeTree())? 1 : 0;
}

void PRIORITY_QUEUE::pop (void){
	if (isEmpty())
		throw myExcp("Priority queue is empty.");
	heap_ -> deleteMinElem();
}

void PRIORITY_QUEUE::push (const KeyType& key){
	heap_ -> insert(key);
}

KeyType PRIORITY_QUEUE::back (void) const{
	if (isEmpty())
		throw myExcp("Priority queue is empty.");
	KeyType tmp = heap_ -> getNodeKey(0);
    return tmp;
}
