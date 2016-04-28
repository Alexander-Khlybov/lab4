#pragma once

#include <iostream>
#include <cstdlib>
#include "tvector.hpp"
#include "excp.h"

#define ALLOW_MEMORY_REALLOCATION_WYV 2 // with your value
#define ALLOW_MEMORY_REALLOCATION_WCV 1 // with calculated value
#define PROHIBIT_MEMORY_REALLOCATION 0

typedef unsigned short mem_rc;

template<class KeyType>
class D_HEAP{
private:
	KeyType*    tree_;
    int      	sizeTree_;
	int      	size_;
	int      	d_;

	int  minKeyIndex 	(int a, int b) const { return (tree_[a] <= tree_[b]) ? a : b; }
    int  min      		(int a, int b) const { return (a < b) ? a : b; }

	int  getMaxChildIndex	(int parent) const { return parent * d_ + d_; }
	int  getMinChildIndex	(int parent) const { return parent * d_ + 1; }
    int  getParentIndex		(int) const;
	int  minChild 			(int) const;

	int  getReallocSize		(void) const;
public:

	D_HEAP 	(int, int);
	D_HEAP 	(const D_HEAP<KeyType>&);
	~D_HEAP (void);

	int operator==(const D_HEAP<KeyType>&)const;
	int operator!=(const D_HEAP<KeyType>&)const;

	int 	getSizeTree			(void) const { return sizeTree_;}
	KeyType getNodeKey			(int) const;
	int 	getSizeReservedMem	(void) const { return size_ - sizeTree_;}
	int 	getD 				(void) const { return d_;}

	void 	swap 		(int, int);
	void 	siftDown 	(int);
	void 	siftUp 		(int);

	void    insert 		    (const KeyType&, mem_rc flag = ALLOW_MEMORY_REALLOCATION_WCV, int size = 0);
	void	deleteMinElem 	(void);
	void    deleteElem 	    (int);
	void    heapify 		(void);

    void    sort    (void);

    TVector<KeyType>    getTree(void) const;

	friend std::ostream& operator<< (std::ostream& out, const D_HEAP<KeyType>& heap){
    	for (int i = 0; i < heap.sizeTree_; i++)
      		out << heap.tree_[i] << "\t";
    	return out;
  	}
};



template<class KeyType>
int D_HEAP<KeyType>::getParentIndex(int child) const {
    if (child == 0)
        return -1;

    return (child - 1) / d_;
}

template<class KeyType>
int D_HEAP<KeyType>::getReallocSize(void) const {
    int maxChild = getMaxChildIndex(getParentIndex(sizeTree_ - 1));
    return (d_ - maxChild % d_);
}

template<class KeyType>
int D_HEAP<KeyType>::minChild(int parent) const {
    if (parent * d_ + 1 > sizeTree_ - 1) return -1;

    int minCh = getMinChildIndex(parent);
    int maxCh = min(getMaxChildIndex(parent), sizeTree_ - 1);

    for (int i = minCh; i <= maxCh; i++) {
        if (tree_[i] < tree_[minCh]) {
            minCh = i;
        }
    }
    return minCh;
}

template<class KeyType>
void D_HEAP<KeyType>::swap(int first, int second) {
    if ((first >= sizeTree_) || (second >= sizeTree_) || (first < 0) || (second < 0))
        throw myExcp("Out of range.");

    KeyType tmp = tree_[first];
    tree_[first] = tree_[second];
    tree_[second] = tmp;
}

template<class KeyType>
void D_HEAP<KeyType>::siftDown(int idx) {
    if ((idx >= sizeTree_) || (idx < 0))
        throw myExcp("Out of range.");

    int c = minChild(idx);
    while ((c != -1) && (tree_[c] < tree_[idx])) {
        swap((int)c, idx);
        idx = (int)c;
        c = minChild(idx);
    }
}

template<class KeyType>
void D_HEAP<KeyType>::siftUp(int idx) {
    if ((idx >= sizeTree_) || (idx < 0))
        throw myExcp("Out of range.");
    if (idx == 0) return;

    int parent = getParentIndex(idx);

    while ((parent != -1) && (tree_[parent] > tree_[idx])) {
        swap(parent, idx);
        idx = parent;
        parent = getParentIndex(idx);
    }
}

template<class KeyType>
D_HEAP<KeyType>::D_HEAP(int size, int d) {
    if (d <= 0)
        throw myExcp("'d' must be greater than 0.");

    if (size < 0)
        throw myExcp("Size must be >= 0");


    size_ = size;
    d_ = d;
    sizeTree_ = 0;
    tree_ = new KeyType[size_];

    if (tree_ == 0)
        throw myExcp("Memory allocation error.");
}

template<class KeyType>
D_HEAP<KeyType>::D_HEAP(const D_HEAP<KeyType>& tree) {
    size_ = tree.size_;
    sizeTree_ = tree.sizeTree_;
    d_ = tree.d_;

    tree_ = new KeyType[size_];
    if (tree_ == 0)
        throw myExcp("Memory allocation error.");

    for (int i = 0; i < sizeTree_; i++) {
        tree_[i] = tree.tree_[i];
    }
}

template<class KeyType>
D_HEAP<KeyType>::~D_HEAP(void) {

    delete[]tree_;
}

template<class KeyType>
void D_HEAP<KeyType>::insert(const KeyType& node, mem_rc flag, int size) {

    switch (flag) {
    case PROHIBIT_MEMORY_REALLOCATION:
        break;
    case ALLOW_MEMORY_REALLOCATION_WCV:
        if (size_ == sizeTree_) {
            size_ += getReallocSize();
            tree_ = (KeyType*)realloc(tree_, size_ * sizeof(KeyType));
            if (tree_ == 0)
                throw myExcp("Memory allocation error.");
        }
        break;
    case ALLOW_MEMORY_REALLOCATION_WYV:
        if (size < 0)
            throw("Size must be >= 0");
        size_ += size;
        tree_ = (KeyType*)realloc(tree_, size_ * sizeof(KeyType));
        if (tree_ == 0)
            throw myExcp("Memory allocation error.");
        break;
    default:
        throw myExcp("Incorrect flag value");
    }

    if (size_ == sizeTree_)
        throw myExcp("No memory for insert node.");
    sizeTree_++;
    tree_[sizeTree_ - 1] = node;
    siftUp(sizeTree_ - 1);
}

template<class KeyType>
void D_HEAP<KeyType>::deleteMinElem(void) {
    if (sizeTree_ == 0) {
        throw myExcp("Heap is empty.");
    }

    tree_[0] = tree_[--sizeTree_];
    if (sizeTree_ != 0)
        siftDown(0);
}

template<class KeyType>
void D_HEAP<KeyType>::deleteElem(int idx) {
    if ((idx >= sizeTree_) || (idx < 0))
        throw myExcp("Out of range.");

    swap(idx, sizeTree_ - 1);

    sizeTree_--;

    if (tree_[idx] < tree_[getParentIndex(idx)]) {
        cout << 2 << endl;

        siftUp(idx);
    }
    else {

        siftDown(idx);
    }
}

template<class KeyType>
void D_HEAP<KeyType>::heapify(void) {
    for (int i = sizeTree_ - 1; i >= 0; i--) {
        siftDown(i);
    }
}

template<class KeyType>
void D_HEAP<KeyType>::sort(void) {
    int tmp = sizeTree_;
    for (int i = sizeTree_ - 1; i > 0; i--) {
        deleteElem(0);
    }
    sizeTree_ = tmp;
}

template<class KeyType>
TVector<KeyType> D_HEAP<KeyType>::getTree(void) const {
    TVector<KeyType> v(sizeTree_);
    for (int i = 0; i < sizeTree_; i++) {
        v[i] = tree_[i];
    }

    return v;
}

template<class KeyType>
KeyType D_HEAP<KeyType>::getNodeKey(int idx) const {
    if ((idx >= sizeTree_) || (idx < 0))
        throw myExcp("Out of range.");

    return tree_[idx];
}

template<class KeyType>
int D_HEAP<KeyType>::operator== (const D_HEAP<KeyType>& heap)const {
    if (sizeTree_ != heap.sizeTree_)
        return 0;

    for (int i = 0; i < sizeTree_; i++) {
        if (tree_[i] != heap.tree_[i])
            return 0;
    }

    return 1;
}

template<class KeyType>
int D_HEAP<KeyType>::operator!= (const D_HEAP<KeyType>& heap)const {

    return !(*this == heap);
}
