#include "d-heap.h"


int D_HEAP::getParentIndex(int child) const{
    if (child == 0)
        return -1;

    return (child - 1) / d_;
}

int D_HEAP::getReallocSize(void) const{
	int maxChild = getMaxChildIndex(getParentIndex(sizeTree_ - 1));
	return (d_ - maxChild % d_);
}

int D_HEAP::minChild(int parent) const{
	if (parent * d_ + 1 > sizeTree_ - 1) return -1; 
	
	int minCh = getMinChildIndex(parent);
	int maxCh = min(getMaxChildIndex(parent), sizeTree_ - 1);

	for (int i = minCh; i <= maxCh; i++){
		if (tree_[i] < tree_[minCh]){
			minCh = i;
		}
	}
    return minCh;
}

void D_HEAP::swap(int first, int second){
	if ((first >= sizeTree_) || (second >= sizeTree_) || (first < 0) || (second < 0))
		throw myExcp("Out of range.");

	KeyType tmp = tree_[first];
	tree_[first] = tree_[second];
	tree_[second] = tmp;
}

void D_HEAP::siftDown(int idx){
	if ((idx >= sizeTree_) || (idx < 0))
		throw myExcp("Out of range.");

    int c = minChild(idx);
	while((c != -1) && (tree_[c] < tree_[idx])){
		swap((int)c, idx);
		idx = (int)c;
		c = minChild(idx);
	}
}

void D_HEAP::siftUp(int idx){
	if ((idx >= sizeTree_) || (idx < 0))
		throw myExcp("Out of range.");
	if (idx == 0) return;

	int parent = getParentIndex(idx);

	while ((parent > 0) && (tree_[parent] > tree_[idx])){
		swap(parent, idx);
		idx = parent;
		parent = getParentIndex(idx);
	}
}

D_HEAP::D_HEAP(int size, int d){
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

D_HEAP::D_HEAP(const D_HEAP& tree){
	size_ = tree.size_;
	sizeTree_ = tree.sizeTree_;
	d_ = tree.d_;

	tree_ = new KeyType[size_];
	if (tree_ == 0)
		throw myExcp("Memory allocation error.");

	for(int i = 0; i < sizeTree_; i++){
		tree_[i] = tree.tree_[i];
	}
}

D_HEAP::~D_HEAP(void){

	delete []tree_;
}

void D_HEAP::insert(const KeyType& node, mem_rc flag, int size){

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

void D_HEAP::deleteMinElem(void){
	if (sizeTree_ == 0){
		throw myExcp("Heap is empty.");
	}

	tree_[0] = tree_[--sizeTree_];
	siftDown(0);
}

void D_HEAP::deleteElem(int idx){
	if ((idx >= sizeTree_) || (idx < 0))
		throw myExcp("Out of range.");

	swap(idx, sizeTree_ - 1);

	sizeTree_--;

	if (tree_[idx] < tree_[getParentIndex(idx)]){
        cout << 2 << endl;

		siftUp(idx);
	}else	{

		siftDown(idx);
	}
}

void D_HEAP::heapify(void){
	for (int i = sizeTree_ - 1; i >= 0; i--){
		siftDown(i);
	}
}

void D_HEAP::sort(void){
    int tmp = sizeTree_;
    for (int i = sizeTree_ - 1; i > 0; i--) {
        deleteElem(0);
    }
    sizeTree_ = tmp;
}

KeyType D_HEAP::getNodeKey(int idx) const{
	if ((idx >= sizeTree_) || (idx < 0))
			throw myExcp("Out of range.");

	return tree_[idx];
}

int D_HEAP::operator== (const D_HEAP& heap)const{
	if (sizeTree_ != heap.sizeTree_)
		return 0;

	for (int i = 0; i < sizeTree_; i++){
		if(tree_[i] != heap.tree_[i])
			return 0;
	}

	return 1;
}

int D_HEAP::operator!= (const D_HEAP& heap)const{

	return !(*this == heap);
}