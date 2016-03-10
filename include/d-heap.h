#ifndef __D_HEAP__
#define __D_HEAP__

#ifndef _CSTDLIB_
#include <cstdlib>
#endif

#ifndef __TVECTOR_H__
#include "tvector.h"
#endif

#ifndef __EXCP_H__
#include "excp.h"
#endif

#ifndef __TVECTOR_H__
#include <iostream>
using namespace std;
typedef int KeyType;
#endif

#define ALLOW_MEMORY_REALLOCATION_WYV 2 // with your value
#define ALLOW_MEMORY_REALLOCATION_WCV 1 // with calculated value
#define PROHIBIT_MEMORY_REALLOCATION 0

typedef unsigned short mem_rc;

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
	D_HEAP 	(const D_HEAP&);
	~D_HEAP (void);

	int operator==(const D_HEAP&)const;
	int operator!=(const D_HEAP&)const;

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

    TVector    getTree(void) const;

	friend ostream& operator<< (ostream& out, const D_HEAP& heap){
    	for (int i = 0; i < heap.sizeTree_; i++)
      		out << heap.tree_[i] << "\t";
    	return out;
  	}
};
#endif