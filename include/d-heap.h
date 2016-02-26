#ifndef __D_HEAP__
#define __D_HEAP__
#include <iostream>
typedef int KeyType;

class D_HEAP{
private:
	KeyType*    tree_;
    size_t      sizeTree_;
	size_t      size_;
	size_t      d_;

	KeyType minChild 	(size_t);
	KeyType min 		(size_t, size_t);
protected:
	void swap 		(size_t, size_t);
	void siftDown 	(size_t);
	void siftUp 		(size_t);
public:
	D_HEAP 	(size_t, size_t);
	D_HEAP 	(const KeyType*, size_t, size_t);
	D_HEAP 	(const D_HEAP&);
	~D_HEAP (void);

	void insert 		(const KeyType&);
	void deleteMinElem 	(void);
	void deleteElem 	(const KeyType&);
	void heapify 		(void);
};
#endif