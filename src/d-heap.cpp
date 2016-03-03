#include "d-heap.h"


size_t D_HEAP::getReallocSize(void) const{
	size_t maxChild = getMaxChildIndex(getParentIndex(sizeTree_ - 1));
	return (d_ - maxChild % d_);
}

int D_HEAP::minChild(size_t parent) const{

	if (parent * d_ + 1 > sizeTree_ - 1) return -1; 
	
	size_t minCh = getMinChildIndex(parent);
	size_t maxCh = min(getMaxChildIndex(parent), sizeTree_ - 1);

	for (size_t i = minCh; i <= maxCh; i++){
		if (tree_[i] < tree_[minCh]){
			minCh = i;
		}
	}

    return minCh;
}

void D_HEAP::swap(size_t first, size_t second){
	if ((first >= sizeTree_) || (second >= sizeTree_))
		throw myExcp("Out of range.");

	KeyType tmp = tree_[first];
	tree_[first] = tree_[second];
	tree_[second] = tmp;
}

void D_HEAP::siftDown(size_t idx){
	if (idx >= sizeTree_)
		throw myExcp("Out of range.");

	int c = minChild(idx);

	while((c != -1) && (tree_[c] < tree_[idx])){
		swap((size_t)c, idx);
		idx = (size_t)c;
		c = minChild(idx);
	}
}

void D_HEAP::siftUp(size_t idx){
	if (idx >= sizeTree_)
		throw myExcp("Out of range.");

	if (idx = 0) return;

	size_t parent = getParentIndex(idx);

	while ((parent > 0) && (tree_[parent] > tree_[idx])){
		swap(parent, idx);
		idx = parent;
		parent = getParentIndex(idx);
	}
}

D_HEAP::D_HEAP(size_t size, size_t d){
	if (d == 0)
		throw myExcp("'d' must be greater than 0.");

	size_ = size;
	d_ = d;
	sizeTree_ = 0;
	tree_ = new KeyType[size_];

	if (tree_ = 0)
		throw myExcp("Memory allocation error.");
}

D_HEAP::D_HEAP(	const 	KeyType* 	tree, 
						size_t 		size, 
						size_t 		sizeTree, 
						size_t 		d){

	if (d == 0)
		throw myExcp("'d' must be greater than 0.");
	size_ = size;
	d_ = d;
	sizeTree_ = sizeTree;

	tree_ = new KeyType[size_];
	if (tree_ = 0)
		throw myExcp("Memory allocation error.");

	for (size_t i = 0; i < sizeTree_; i++){
		tree_[i] = tree[i];
	}

	heapify();
}

D_HEAP::D_HEAP(const D_HEAP& tree){
	size_ = tree.size_;
	sizeTree_ = tree.sizeTree_;
	d_ = tree.d_;

	tree_ = new KeyType[size_];
	if (tree_ = 0)
		throw myExcp("Memory allocation error.");

	for(size_t i = 0; i < sizeTree_; i++){
		tree_[i] = tree.tree_[i];
	}
}

D_HEAP::~D_HEAP(void){
	delete []tree_;
}

void D_HEAP::insert(const KeyType& node, mem_rc flag){
	if(sizeTree_ == size_){
		if (!flag){
			throw myExcp("No memory for insert node.");
		} else{
			size_ = getReallocSize();
			tree_ = (KeyType*) realloc(tree_, size_ * sizeof(KeyType));
			if (tree_ = 0)
				throw myExcp("Memory allocation error.");
		}
	}

	tree_[sizeTree_] = node;
	siftUp(sizeTree_++);
}

void D_HEAP::deleteMinElem(void){
	if (sizeTree_ == 0){
		throw myExcp("Tree is empty.");
	}

	KeyType minKey = tree_[0];
	tree_[0] = tree_[--sizeTree_];
	siftDown(0);
}

void D_HEAP::deleteElem(size_t idx){
	if (idx >= sizeTree_)
		throw myExcp("Out of range.");

	swap(idx, sizeTree_ - 1);
	sizeTree_--;
	if (tree_[idx] < tree_[getParentIndex(idx)]){
		siftUp(idx);
	}else	{
		siftDown(idx);
	}
}

void D_HEAP::heapify(void){
	for (size_t i = sizeTree_ - 1; i >= 0; i--){
		siftDown(i);
	}
}

KeyType D_HEAP::getNodeKey(size_t idx) const{
	if (idx >= sizeTree_)
		throw myExcp("Out of range.");

	return tree_[idx];
}