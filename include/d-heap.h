#ifndef __D_HEAP__
#define __D_HEAP__

#include <cstdlib>
#include <iostream>
#include "excp.h"

#define ALLOW_MEMORY_REALLOCATION true
#define PROHIBIT_MEMORY_REALLOCATION false

typedef int KeyType;
typedef bool mem_rc;


class D_HEAP{
private:
	KeyType*    tree_;
    size_t      sizeTree_;
	size_t      size_;
	size_t      d_;

	size_t min 	(size_t a, size_t b) const { return (tree_[a] <= tree_[b]) ? a : b; }

	size_t getMaxChildIndex	(size_t parent) const { return parent * d_ + d_; }
	size_t getMinChildIndex	(size_t parent) const { return parent * d_ + 1; }
    size_t getParentIndex   (size_t child) const  { return (child - 1) / d_; }
	size_t getReallocSize	(void) const;
public:

	D_HEAP 	(size_t, size_t);
	D_HEAP 	(const KeyType*, size_t, size_t, size_t);
	D_HEAP 	(const D_HEAP&);
	~D_HEAP (void);

	size_t getSizeTree	(void) const { return sizeTree_;}
	KeyType getNodeKey	(size_t) const;

	int 	minChild 	(size_t) const;
	void 	swap 		(size_t, size_t);
	void 	siftDown 	(size_t);
	void 	siftUp 		(size_t);

	void insert 		(const KeyType&, mem_rc);
	void deleteMinElem 	(void);
	void deleteElem 	(size_t);
	void heapify 		(void);
};
#endif