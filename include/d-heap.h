#ifndef __D_HEAP__
#define __D_HEAP__

#include <cstdlib>
#include <iostream>
#include "excp.h"

#define ALLOW_MEMORY_REALLOCATION true
#define PROHIBIT_MEMORY_REALLOCATION false

using namespace std;

typedef int KeyType;
typedef bool mem_rc;


class D_HEAP{
private:
	KeyType*    tree_;
    int      sizeTree_;
	int      size_;
	int      d_;

	int  minKeyIndex 	(int a, int b) const { return (tree_[a] <= tree_[b]) ? a : b; }
    int  min      		(int a, int b) const { return (a < b) ? a : b; }

	int  getMaxChildIndex	(int parent) const { return parent * d_ + d_; }
	int  getMinChildIndex	(int parent) const { return parent * d_ + 1; }
    int  getParentIndex		(int child) const;
	int  getReallocSize		(void) const;
public:

	D_HEAP 	(int, int);
	D_HEAP 	(const KeyType*, int, int, int);
	D_HEAP 	(const D_HEAP&);
	~D_HEAP (void);

	int 	getSizeTree	(void) const { return sizeTree_;}
	KeyType getNodeKey	(int) const;

	int 	minChild 	(int) const;
	void 	swap 		(int, int);
	void 	siftDown 	(int);
	void 	siftUp 		(int);

	void    insert 		    (const KeyType&, mem_rc);
	KeyType deleteMinElem 	(void);
	void    deleteElem 	    (int);
	void    heapify 		(void);

    void    sort    (void);

	friend ostream& operator<< (ostream& out, const D_HEAP& heap){
    	for (int i = 0; i < heap.sizeTree_; i++)
      	out << heap.tree_[i] << "\t";
    	return out;
  	}
};
#endif