#pragma once

#include <iostream>
#include <string>
#include "d-heap.hpp"
#include "avl-tree.hpp"
#include "tables.hpp"

template<class KeyType>
class PRIORITY_QUEUE {
public:
	PRIORITY_QUEUE(void) {}
	PRIORITY_QUEUE(const PRIORITY_QUEUE<KeyType>&) {}
	virtual ~PRIORITY_QUEUE(void) {}

	virtual int getSize(void)const = 0;
	virtual int isEmpty(void) const = 0;
	virtual int isFull(void) const = 0;

	virtual void pop(void) = 0;
	virtual void push(const KeyType&) = 0;
	virtual KeyType back(void) const = 0;
};

template<class KeyType>
class PRIORITY_QUEUE_ON_D_HEAP : public PRIORITY_QUEUE<KeyType>{

	D_HEAP<KeyType>* heap_;
public:
	PRIORITY_QUEUE_ON_D_HEAP(int d = 3);
	PRIORITY_QUEUE_ON_D_HEAP(const PRIORITY_QUEUE_ON_D_HEAP<KeyType>&);
	virtual ~PRIORITY_QUEUE_ON_D_HEAP(void) { delete heap_;}

    virtual int         getSize 	(void) const { return heap_->getSizeTree();}
    D_HEAP<KeyType>     getHeap     (void) const;
    int     isEmpty     (void) const;
	int     isFull		(void) const;

    void    pop         (void);
    void    push        (const KeyType&);
    KeyType back        (void) const;

    friend std::ostream& operator<< (std::ostream& out, const PRIORITY_QUEUE<KeyType>& queue) {
            out << queue.heap_;
        return out;
    }
};

template<class KeyType>
PRIORITY_QUEUE_ON_D_HEAP<KeyType>::PRIORITY_QUEUE_ON_D_HEAP(int d) {
    if (d <= 0)
        throw myExcp("D must be > 0");

    heap_ = new D_HEAP<KeyType>(0, 1);
}

template<class KeyType>
PRIORITY_QUEUE_ON_D_HEAP<KeyType>::PRIORITY_QUEUE_ON_D_HEAP(const PRIORITY_QUEUE_ON_D_HEAP& queue) {
    heap_ = new D_HEAP<KeyType>(*queue.heap_);
    if (heap_ == NULL)
        throw myExcp("Memory allocationn error.");
}

template<class KeyType>
D_HEAP<KeyType> PRIORITY_QUEUE_ON_D_HEAP<KeyType>::getHeap(void) const {
    D_HEAP<KeyType> heap(*heap_);
    return heap;
}

template<class KeyType>
int PRIORITY_QUEUE_ON_D_HEAP<KeyType>::isEmpty(void) const {

    return (0 == heap_->getSizeTree()) ? 1 : 0;
}

template<class KeyType>
int PRIORITY_QUEUE_ON_D_HEAP<KeyType>::isFull(void) const{
	KeyType* tmp;
	try {
		tmp = new KeyType();
	} catch(...) {
		return 1;
	}
	delete tmp;
	return 0;
}

template<class KeyType>
void PRIORITY_QUEUE_ON_D_HEAP<KeyType>::pop(void) {
    if (isEmpty())
        throw myExcp("Priority queue is empty.");
    heap_->deleteMinElem();
}

template<class KeyType>
void PRIORITY_QUEUE_ON_D_HEAP<KeyType>::push(const KeyType& key) {
    heap_->insert(key);
}

template<class KeyType>
KeyType PRIORITY_QUEUE_ON_D_HEAP<KeyType>::back(void) const {
    if (isEmpty())
        throw myExcp("Priority queue is empty.");
    KeyType tmp = heap_->getNodeKey(0);
    return tmp;
}

template<class KeyType>
class PRIORITY_QUEUE_ON_AVL_TREE : public PRIORITY_QUEUE<KeyType> {
	AVL_TREE<KeyType>* tree_;
public:
	PRIORITY_QUEUE_ON_AVL_TREE(void) {
		tree_ = new AVL_TREE<KeyType>();
		if (tree_ == NULL)
			throw exception("Error.");
	}
	PRIORITY_QUEUE_ON_AVL_TREE(const PRIORITY_QUEUE_ON_AVL_TREE<KeyType>& tree) {
		tree_ = new AVL_TREE<KeyType>(*tree.tree_);
		if (tree_ == NULL)
			throw exception("Error.");
	}
	virtual ~PRIORITY_QUEUE_ON_AVL_TREE(void) { delete tree_; }

	virtual int getSize(void)const { return tree_->getSize(); }
	virtual int isEmpty(void) const { return tree_->getSize() == 0; }
	virtual int isFull(void) const;
	AVL_TREE<KeyType> getTree(void)const;

	virtual void pop(void) { tree_->erase(tree_->findMin()->data_); }
	virtual void push(const KeyType& key) { tree_->insert(key); }
	virtual KeyType back(void) const { return tree_->findMin()->data_; }
};

template<class KeyType>
int PRIORITY_QUEUE_ON_AVL_TREE<KeyType>::isFull(void) const{
	KeyType* node = new KeyType();
	if (node == NULL)
		return 1;
	delete node;
	return 0;
}

template<class KeyType>
AVL_TREE<KeyType> PRIORITY_QUEUE_ON_AVL_TREE<KeyType>::getTree(void) const{
	return AVL_TREE<KeyType>(*tree_);
}

template <class KeyType>
class PRIORITY_QUEUE_ON_SORT_TABLE : public PRIORITY_QUEUE<KeyType> {
	SORT_TABLE<KeyType>* table_;
public:
	PRIORITY_QUEUE_ON_SORT_TABLE(size_t sizeOfTable) {
		table_ = new SORT_TABLE<KeyType>(sizeOfTable);
		if (table_ == NULL)
			throw exception("ERROR.");
	}
	PRIORITY_QUEUE_ON_SORT_TABLE(const PRIORITY_QUEUE_ON_SORT_TABLE<KeyType>& table) {
		table_ = new SORT_TABLE<KeyType>(*table.table_);
		if (table_ == NULL)
			throw exception("ERROR.");
	}
	virtual ~PRIORITY_QUEUE_ON_SORT_TABLE(void) { delete table_; }

	virtual int getSize(void)const { return table_->getCount(); }
	virtual int isEmpty(void) const { return table_->isEmpty(); }
	virtual int isFull(void) const { return table_->isFull(); }
	SORT_TABLE<KeyType> getTable(void)const;

	virtual void pop(void) {
		if (isEmpty())
			throw exception("Is empty.");
		table_->reset();
		table_->eraseCurrentRecord();
	}
	virtual void push(const KeyType& key) {
		if (isFull())
			throw exception("Is full.");
		table_->insert(key);
	}
	virtual KeyType back(void) const {
		if (isEmpty())
			throw exception("Is empty.");
		table_->reset();
		return table_->getCurrentRecord()->getKey();
	}
};

template <class KeyType>
class MAKE_PRIORITY_QUEUE {
public:
	static PRIORITY_QUEUE<KeyType> makeQueueBasedOn(const string&, size_t size = 0);
};

template<class KeyType>
PRIORITY_QUEUE<KeyType> MAKE_PRIORITY_QUEUE<KeyType>::makeQueueBasedOn(const string& s, size_t size){
	switch (s) {
	case "D_HEAP":
		return PRIORITY_QUEUE_ON_D_HEAP<KeyType>(size);
	case "AVL_TREE":
		return PRIORITY_QUEUE_ON_AVL_TREE<KeyType>();
	case "SORT_TABLE":
		return PRIORITY_QUEUE_ON_SORT_TABLE<KeyType>(size);
	default:
		throw exception("Priority queue does not created");
	}
}

template<class KeyType>
SORT_TABLE<KeyType> PRIORITY_QUEUE_ON_SORT_TABLE<KeyType>::getTable(void) const{
	return SORT_TABLE<KeyType>(*table_);
}
