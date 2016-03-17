#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#ifndef __D_HEAP__
#include "d-heap.h"
#endif

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

class PRIORITY_QUEUE{

	D_HEAP* heap_;
public:
    PRIORITY_QUEUE  (int d = 1);
    PRIORITY_QUEUE  (const PRIORITY_QUEUE&);
	~PRIORITY_QUEUE (void) { delete heap_;};

    int     getSize 	(void) const { return heap_->getSizeTree();}
    D_HEAP  getHeap     (void) const;

    int     operator==  (const PRIORITY_QUEUE&)const;
    int     operator!=  (const PRIORITY_QUEUE&)const;

    int     isEmpty     (void) const;

    void    pop         (void);
    void    push        (const KeyType&);
    KeyType back        (void) const;

    friend ostream& operator<< (ostream& out, const PRIORITY_QUEUE& queue) {
            out << queue.heap_;
        return out;
    }
};
#endif
